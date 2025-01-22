#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>  // or other layout types

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);  // Create a new widget for central layout
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);  // Create a layout for central widget
    leftPanel = new LeftPanel(centralWidget);  // Create LeftPanel inside the layout
    layout->addWidget(leftPanel);  // Add LeftPanel to the layout

    setCentralWidget(centralWidget);  // Set the central widget with the layout
}


MainWindow::~MainWindow() {}
