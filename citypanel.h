#ifndef CITYPANEL_H
#define CITYPANEL_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class CityPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CityPanel(const QString &cityName, double temperature, QWidget *parent = nullptr);

private:
    QLabel *cityLabel;
    QLabel *tempLabel;
};

#endif // CITYPANEL_H
