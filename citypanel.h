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

    QString getCityName();

signals:
    void removeRequested(const QString &cityName);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QLabel* dataLabel;
    QLabel* removeLabel;
    QString cityName;
};

#endif // CITYPANEL_H
