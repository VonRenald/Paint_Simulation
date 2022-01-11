#include "helper.h"


#include <QPainter>
#include <QPaintEvent>
#include <QWidget>


#include <stdlib.h>
#include <iostream>

Helper::Helper()
{

    background = QBrush(QColor(255,255,255));
    pen = QPen(QColor(0,0,0));
    pen.setWidth(5);
    start=true;

}

void Helper::paint(QPainter *painter, QPaintEvent *event)
{
    if (start)
    {
        painter->fillRect(event->rect(), background);
        start=false;
    }
    painter->setPen(pen);
    painter->drawPoint(rand() %400 +1,rand()%400+1);
}

//void Helper::mousePressEvent(QMouseEvent *)
//{
//    pressed = 1;
//    std::cout << "ok";
//}

//void Helper::mouseReleaseEvent(QMouseEvent *)
//{
//    pressed = 0;
//}

//void Helper::mouseMoveEvent(QMouseEvent *e)
//{
//    std::cout << "test";
//    if(pressed)
//    {
//        QPainter painter;
//        painter.begin(parent);
//        painter.setPen(pen);
//        painter.drawPoint(e->pos().x(),e->pos().x());
//        painter.end();
////        repaint();
//    }
//}
