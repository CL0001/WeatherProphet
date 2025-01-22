#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "leftpanel.h"  // Include your LeftPanel class header

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    LeftPanel *leftPanel;  // Declare LeftPanel pointer
};

#endif // MAINWINDOW_H
