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
            img->setPixelColor(x,y,QColor(x,y,0));
        }
    }

    isPressed = false;
//    qInfo() << "call updt";
    update();

}

void OpenGl::paintEvent(QPaintEvent *event)
{
//    qInfo() << "paint evnt";
    painter.begin(this);

    painter.drawImage(event->rect(),*img,img->rect());

    painter.end();

}

void OpenGl::mouseMoveEvent(QMouseEvent *e)
{
    if (isPressed)
    {
        int xRelative = e->pos().x() * sizeCanvas[0] / this->width();
        int yRelative = e->pos().y() * sizeCanvas[1] / this->height();
        img->setPixelColor(xRelative,yRelative,QColor(255,255,255));
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
        img->setPixelColor(xRelative,yRelative,QColor(255,255,255));

        update();
    }
}

void OpenGl::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && isPressed)
    {
        isPressed = false;
    }
}



