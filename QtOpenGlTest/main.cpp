
#include "glwindow2.h"
#include "window.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    GlWindow2 *f = new GlWindow2();
    f->show();


//    Window w;
//    w.show();

    return a.exec();
}

//https://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html
