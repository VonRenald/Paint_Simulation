#pragma once
#include <qmainwindow.h>
#include <QMenuBar>
#include <Qmenu>


#include "qtwidgetsvs.h"

class MainWindow :
    public QMainWindow
{
public:
    MainWindow();
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent* event);
private:
    QtWidgetsVS *widget;
};

