#include "colordisplay.h"

ColorDisplay::ColorDisplay()
{
    img = new QImage(1,1,QImage::Format_RGB32);
}
void ColorDisplay::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.drawImage(event->rect(),*img,img->rect());
    painter.end();
}

void ColorDisplay::setColor(QColor color)
{
    img->setPixelColor(0,0,color);
    update();
}
