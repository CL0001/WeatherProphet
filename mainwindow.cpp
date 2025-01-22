#include "mainwindow.h"

#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(69, 69, 69));
    palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
    palette.setColor(QPalette::Base, QColor(69, 69, 69));
    palette.setColor(QPalette::Text, QColor(255, 255, 255));
    palette.setColor(QPalette::Button, QColor(69, 69, 69));
    palette.setColor(QPalette::ButtonText, QColor(255, 255, 255));

    setPalette(palette);

    QSplitter* splitter = new QSplitter(this);
    splitter->setStyleSheet("background: rgb(69, 69, 69);");

    leftPanel = new LeftPanel(splitter);
    rightPanel = new RightPanel(splitter);

    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);

    setCentralWidget(splitter);

    resize(1000, 600);
    setMinimumSize(600, 400);
}

MainWindow::~MainWindow() {}
