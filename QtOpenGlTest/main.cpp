
#include "glwindow2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Fenetre w;
//    w.show();
    GlWindow2 *f = new GlWindow2();

    f->show();
    return a.exec();
}

//https://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html
