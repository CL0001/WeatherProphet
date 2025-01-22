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
    // Search bar setup
    searchBar = new QLineEdit(this);
    QAction* searchAction = new QAction(QIcon(QPixmap(":/assets/icons/magnifying-glass.png")), "search", this);
    searchBar->addAction(searchAction, QLineEdit::TrailingPosition);

    // Scroll area setup
    cityPanelList = new QScrollArea(this);
    auto scrollContainer = new QWidget(this);
    scrollLayout = new QVBoxLayout(scrollContainer);
    scrollContainer->setLayout(scrollLayout);
    cityPanelList->setWidget(scrollContainer);
    cityPanelList->setWidgetResizable(true);

    // Main layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(searchBar);
    layout->addWidget(cityPanelList);
    setLayout(layout);

    // Connect search action
    connect(searchAction, &QAction::triggered, this, &LeftPanel::onSearchTriggered);

    // fetchAllCityWeatherData();
}

void LeftPanel::onSearchTriggered()
{
    QString city = searchBar->text().trimmed();

    if (!city.isEmpty() && !cityWeatherData.contains(city)) {
        fetchCityWeatherData(city);
    } else {
        qWarning() << "City already added or invalid.";
    }

    searchBar->clear();
}

void LeftPanel::fetchCityWeatherData(const QString city)
{
    QUrl apiUrl(QString("http://localhost:8000/city/%1").arg(city));
    QNetworkRequest request(apiUrl);

    QNetworkReply *reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

            if (jsonDoc.isObject())
            {
                QJsonObject jsonObj = jsonDoc.object();
                QMap<QString, QVariant> cityWeather;

                for (const QString &key : jsonObj.keys())
                {
                    cityWeather[key] = jsonObj.value(key).toVariant();
                }

                cityWeatherData[city] = cityWeather;

                QVariant temperature = cityWeather["temp"];
                addCityPanel(city, temperature);

                qInfo() << "Weather data for city" << city << "is" << temperature.toDouble() << "C";
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
    for (const QString &city : cityWeatherData.keys())
    {
        fetchCityWeatherData(city);
    }
}

void LeftPanel::addCityPanel(const QString &city, const QVariant &temperature)
{
    CityPanel* cityPanel = new CityPanel(city, temperature.toDouble(), this);
    scrollLayout->addWidget(cityPanel);
}
