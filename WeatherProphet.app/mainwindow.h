#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "leftpanel.h"
#include "rightpanel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    LeftPanel* leftPanel;
    RightPanel* rightPanel;
};

#endif // MAINWINDOW_H
