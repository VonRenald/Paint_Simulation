#include "colorshow.h"

ColorShow::ColorShow()
{
    img = new QImage(1,1,QImage::Format_RGB32);
}

void ColorShow::setColor(QColor color)
{
    img->setPixelColor(0,0,color);
}


