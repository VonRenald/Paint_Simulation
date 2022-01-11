
#include "glwindow2.h"
#include "window.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    GlWindow2 *f = new GlWindow2();
    f->show();


    return a.exec();
}


