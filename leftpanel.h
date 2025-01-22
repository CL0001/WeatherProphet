#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>

class LeftPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LeftPanel(QWidget *parent = nullptr);

signals:

public slots:
    void onSearchTriggered();

private:
    QMap<QString, QMap<QString, QVariant>> cityWeatherData;
    QNetworkAccessManager networkManager;
    QLineEdit* searchBar;
    QScrollArea* cityPanelList;
    QVBoxLayout* scrollLayout;

    void fetchCityWeatherData(const QString city);
    void fetchAllCityWeatherData();
    void addCityPanel(const QString& city, const QVariant &temperature);
};

#endif // LEFTPANEL_H
