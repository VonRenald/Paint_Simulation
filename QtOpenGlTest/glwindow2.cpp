#include "glwindow2.h"
#include<QDebug>

GlWindow2::GlWindow2()
{
    qInfo() << "--START--";

//    setFixedSize(400,440);
    setAutoFillBackground(false);

    press = false;
    background = QBrush(QColor(255,255,255));
    pen = QPen(QColor(100,100,100));
    pen.setWidth(1);


    painter.setPen(pen);

    x=0;
    y=0;
    xp=-1;
    yp=-1;

    reset = true;

//    QObject::connect(this,SIGNAL(resized()), this, SLOT(resetAfeterResize()));
}

void GlWindow2::mouseMoveEvent(QMouseEvent *e)
{
//    qInfo() << "pos :" << e->pos().x() << e->pos().y();
    if(xp == -1)
    {
        x=e->pos().x();
        y=e->pos().y();
        xp=x;
        yp=y;
    }
    else
    {
        xp = x;
        yp = y;
        x=e->pos().x();
        y=e->pos().y();
    }

    update();

}

void GlWindow2::paintEvent(QPaintEvent *event)
{
//    qInfo() << "ok";
    painter.begin(this);
    if (reset)
    {
        painter.fillRect(event->rect(), background);
        reset = false;
    }
//    painter.drawPoint(x,y);
    if(press && xp != -1)
    {
        painter.drawLine(x,y,xp,yp);
    }

    painter.end();
}

void GlWindow2::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && !press)
        {
            press = true;

        }
}

void GlWindow2::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && press)
        {
            press = false;
            xp = -1;
            yp = -1;

        }
}

void GlWindow2::resetAfeterResize()
{
    qInfo() << "resize";
    reset = true;
    update();
}
