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

private:
    QFrame* contentBorder;
    QLabel* headerLabel;
    QVBoxLayout* layout;
};

#endif // RIGHTPANEL_H
