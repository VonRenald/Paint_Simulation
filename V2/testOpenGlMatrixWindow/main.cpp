#include "window.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;

//    float a = (y2-y1)/(x2-x1)
//    float b = y2 -(a * x2)
//    y = ax+b

    w.show();
    return a.exec();
}


