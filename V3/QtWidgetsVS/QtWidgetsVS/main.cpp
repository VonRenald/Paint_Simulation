#include "qtwidgetsvs.h"
#include "OpenGl.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QSurfaceFormat>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QtWidgetsVS w;
    //w.show();
    //OpenGl o;
    //o.show();
    srand(time(NULL));
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);


    //QtWidgetsVS w;
    MainWindow w;
    w.show();
    
    

    return a.exec();
}
