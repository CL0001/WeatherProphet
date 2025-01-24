#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class RightPanel : public QWidget
{
    Q_OBJECT
public:
    explicit RightPanel(QWidget *parent = nullptr);
    void displayDefaultView();
    void displayCityView();

public slots:
    void loadSelectedCityData(const QMap<QString, QVariant> selectedCityData);

private:
    // old and working
    QFrame* contentBorder;
    QLabel* headerLabel;
    QVBoxLayout* layout;
    QMap<QString, QVariant> currentCityData;
};

#endif // RIGHTPANEL_H
