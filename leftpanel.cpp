#include "leftpanel.h"
#include "citypanel.h"

#include <QAction>
#include <QIcon>
#include <QPixmap>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QSizePolicy>

LeftPanel::LeftPanel(QWidget *parent)
    : QWidget{parent}
{
    // Search bar initialization
    searchBar = new QLineEdit(this);
    QAction* searchAction = new QAction(QIcon(QPixmap(":/assets/icons/magnifying-glass.png")), "search", this);
    searchBar->addAction(searchAction, QLineEdit::TrailingPosition);

    searchBar->setStyleSheet(
        "QLineEdit {"
        "   background-color: rgb(34, 34, 34);"
        "   border: 2px solid white;"
        "   border-radius: 10px;"
        "   color: white;"
        "   padding: 10px;"
        "}"
    );

    // Scroll area initialization
    cityPanelList = new QScrollArea(this);

    auto scrollContainer = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollContainer);
    scrollContainer->setLayout(scrollLayout);

    scrollContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    cityPanelList->setWidget(scrollContainer);
    cityPanelList->setWidgetResizable(true);
    cityPanelList->setStyleSheet(
        "QScrollArea {"
        "   background: rgb(34, 34, 34);"
        "   border: 2px solid white;"
        "   border-radius: 10px;"
        "}"
    );

    scrollContainer->setStyleSheet("background: transparent;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(searchBar);
    layout->addWidget(cityPanelList);
    setLayout(layout);

    // Linking signals and slots
    connect(searchAction, &QAction::triggered, this, &LeftPanel::onSearchTriggered);
}

void LeftPanel::onSearchTriggered()
{
    QString city = searchBar->text().trimmed();

    if (!city.isEmpty() && !cityWeatherData.contains(city))
    {
        fetchCityWeatherData(city);
    }
    else
    {
        qWarning() << "City already added or invalid.";
    }

    searchBar->clear();
}

void LeftPanel::removeCityPanel(const QString& city)
{
    for (int i = 0; i < scrollLayout->count(); i++)
    {
        QWidget* widget = scrollLayout->itemAt(i)->widget();
        CityPanel* cityPanel = qobject_cast<CityPanel*>(widget);

        if (cityPanel && cityPanel->getCityName() == city)
        {
            scrollLayout->removeWidget(cityPanel);
            cityPanel->deleteLater();
            cityWeatherData.remove(city);
            break;
        }
    }
}

void LeftPanel::selectCityPanel(const QString &city)
{
    for (int i = 0; i < scrollLayout->count(); i++)
    {
        QWidget* widget = scrollLayout->itemAt(i)->widget();
        CityPanel* cityPanel = qobject_cast<CityPanel*>(widget);

        if (cityPanel && cityPanel->getCityName() == city)
        {
            cityPanel->selectPanel();

            for (int j = 0; j < scrollLayout->count(); j++)
            {
                QWidget* otherWidget = scrollLayout->itemAt(j)->widget();
                CityPanel* otherCityPanel = qobject_cast<CityPanel*>(otherWidget);

                if (otherCityPanel && otherCityPanel != cityPanel)
                {
                    otherCityPanel->unselectPanel();
                }
            }
            emit citySelected(cityWeatherData[city]);
            break;
        }
    }
}

void LeftPanel::fetchCityWeatherData(const QString city)
{
    QUrl apiUrl(QString("http://localhost:8000/city/%1").arg(city));
    QNetworkRequest request(apiUrl);

    QNetworkReply* reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, [=](){
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

            if (jsonDoc.isObject())
            {
                QJsonObject jsonObj = jsonDoc.object();
                QMap<QString, QVariant> cityWeather;

                for (const QString& key : jsonObj.keys())
                {
                    cityWeather[key] = jsonObj.value(key).toVariant();
                }

                cityWeatherData[city] = cityWeather;

                QVariant temperature = cityWeather["temp"];
                addCityPanel(city, temperature);

                qDebug() << "Weather data for city" << city << "is" << temperature.toDouble() << "C";
            }
            else
            {
                qWarning() << "Invalid JSON response for city:" << city;
            }
        }
        else
        {
            qWarning() << "HTTP request error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void LeftPanel::fetchAllCityWeatherData()
{
    for (const QString& city : cityWeatherData.keys())
    {
        fetchCityWeatherData(city);
    }
}

void LeftPanel::addCityPanel(const QString &city, const QVariant &temperature)
{
    CityPanel* cityPanel = new CityPanel(city, temperature.toDouble(), this);

    connect(cityPanel, &CityPanel::removeRequest, this, &LeftPanel::removeCityPanel);
    connect(cityPanel, &CityPanel::selectRequest, this, &LeftPanel::selectCityPanel);

    scrollLayout->addWidget(cityPanel);
    scrollLayout->setAlignment(Qt::AlignTop);
}
