#include "citypanel.h"

CityPanel::CityPanel(const QString &cityName, double temperature, QWidget *parent)
    : QWidget(parent)
{
    cityLabel = new QLabel(cityName, this);
    tempLabel = new QLabel(QString("%1°C").arg(temperature), this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(cityLabel);
    layout->addWidget(tempLabel);

    setLayout(layout);
    setStyleSheet("background-color: lightgray; border: 1px solid gray; border-radius: 5px; padding: 5px;");
}
