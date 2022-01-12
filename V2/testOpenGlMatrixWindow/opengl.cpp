#include "opengl.h"

OpenGl::OpenGl()
{
//    qInfo() << "open init";

    sizeCanvas[0] = 255; // x
    sizeCanvas[1] = 255; // y

    img = new QImage(sizeCanvas[0],sizeCanvas[0],QImage::Format_RGB32);

    for(int y = 0;y<255;y++)
    {
        for(int x=0;x<255;x++)
        {
            img->setPixelColor(x,y,QColor(255,255,255));
        }
    }
//    drawLine(10,20,10,10);

    isPressed = false;
    colorPen = QColor(0,0,0);
//    qInfo() << "call updt";
    update();

}

void OpenGl::paintEvent(QPaintEvent *event)
{
//    qInfo() << "paint evnt";
    painter.begin(this);

    painter.drawImage(event->rect(),*img,img->rect());


    bool stop = false;
    while (lpoints.size()>=2 && !stop)
    {
        QPoint p1 = lpoints.front();
        lpoints.pop_front();
        QPoint p2 = lpoints.front();


        if(p2.isNull())
        {
            lpoints.pop_front();
            stop = true;
        }
        else
        {
            drawLine(p1,p2);
        }
    }

    painter.end();

}

void OpenGl::mouseMoveEvent(QMouseEvent *e)
{
    if (isPressed)
    {
        int xRelative = e->pos().x() * sizeCanvas[0] / this->width();
        int yRelative = e->pos().y() * sizeCanvas[1] / this->height();
//        img->setPixelColor(xRelative,yRelative,QColor(255,255,255));

        lpoints.push_back(QPoint(xRelative,yRelative));
        update();
    }
//    qInfo() << "move" << e->pos() << xRelative;
}

void OpenGl::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isPressed = true;
        int xRelative = e->pos().x() * sizeCanvas[0] / this->width();
        int yRelative = e->pos().y() * sizeCanvas[1] / this->height();
//        img->setPixelColor(xRelative,yRelative,QColor(255,255,255));

        lpoints.push_back(QPoint(xRelative,yRelative));

        update();
    }
}

void OpenGl::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && isPressed)
    {
        isPressed = false;
        lpoints.push_back(QPoint());
    }
}

void OpenGl::drawLine(int x1, int y1, int x2, int y2)
{
        //float a = float(y2-y1)/float(x2-x1);
        float a = float(y2-y1);
        float ap = float(x2-x1);
        a = (ap==0)? 0:a/ap;
//        qInfo("a %f",a);
//        qInfo("y2 %d y1 %d (y2-y1) %d",y2,y1,(y2-y1));
//        qInfo("x2 %d x1 %d (x2-x1) %d",x2,x1,(x2-x1));
//        qInfo("(y2-y1)/(x2-x1) %f",float(y2-y1)/float(x2-x1));
        float b = y2 -(a * x2);

        for (int x = std::min(x1,x2); x <= std::max(x1,x2);x++)
        {
            int y = a*x+b;
//            qInfo() << "x" << x << "y" << y;
            img->setPixelColor(x,y,colorPen);
        }

        for (int y = std::min(y1,y2); y <= std::max(y1,y2);y++)
        {
            int x = (a==0)? x1:(float(y)-b)/a;
//            qInfo() << "x" << x << "y" << y;
            img->setPixelColor(x,y,colorPen);
        }

    //    y = ax+b
    //     y-b = ax
        // (y-b)/a = x

}

void OpenGl::drawLine(QPoint p1, QPoint p2)
{
    drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}

void OpenGl::setColorPen(QColor color)
{
    colorPen = color;
//    qInfo() << "color changed";
}


