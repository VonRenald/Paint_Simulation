#include "qtwidgetsvs.h"
#include "OpenGl.h"
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
    
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);


    QtWidgetsVS w;
    w.show();
    //OpenGl window;
    //window.show();

    return a.exec();
}
