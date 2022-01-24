#pragma once
#include <qmainwindow.h>
#include <QMenuBar>
#include <Qmenu>
#include <QInputDialog>

#include "qtwidgetsvs.h"

class MainWindow :
    public QMainWindow
{
public:
    MainWindow();
    ~MainWindow();
public slots:
    void creatNewCanvas();
    void saveTexture();
protected:
    void resizeEvent(QResizeEvent* event);
private:
    QtWidgetsVS *widget;
};

