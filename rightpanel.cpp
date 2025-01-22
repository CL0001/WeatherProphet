#include "rightpanel.h"

RightPanel::RightPanel(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(
        "QWidget {"
        "   background: rgb(34, 34, 34);"
        "   border: 2px solid white;"
        "   border-radius: 10px;"
        "}"
    );

    QLabel* titleLabel = new QLabel("Weather Prophet", this);
    titleLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 24px;"
        "   color: white;"
        "   qproperty-alignment: AlignCenter;"
        "}"
    );

    titleLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    setLayout(layout);
}

void RightPanel::displayDefaultView()
{
    headerLabel->setText("Weather Prophet");
    headerLabel->show();
}
