#include "leftpanel.h"

#include <QAction>
#include <QIcon>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "citypanel.h"

LeftPanel::LeftPanel(QWidget *parent)
    : QWidget{parent}
{
    // Search bar initialization and stylizization
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

    // Scroll area initialization and stylizization
    cityPanelList = new QScrollArea(this);

    auto scrollContainer = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollContainer);
    scrollContainer->setLayout(scrollLayout);

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
    scrollLayout->addWidget(cityPanel);
    scrollLayout->setAlignment(Qt::AlignTop);
}
