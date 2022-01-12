#include "colorpick.h"

ColorPick::ColorPick(OpenGl *openGl,ColorDisplay *colorDisplay)
{
    canvas = openGl;
    display = colorDisplay;

    h=0;
    s=0;
    v=0;

    img = new QImage(101,101,QImage::Format_RGB32);
    display->setColor(QColor(0,0,0));


//    qInfo() << "0" << 50/60;
    setPalette();


}

void ColorPick::setH(int val)
{
    h = val;
//    qInfo() << "h" << h;
    setPalette();
    update();
}

void ColorPick::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.drawImage(event->rect(),*img,img->rect());
    painter.end();
}

void ColorPick::setPalette()
{
    float r;
    float g;
    float b;
    for(int sp = 0; sp<=100;sp++)
    {
        for(int vp=0; vp<=100; vp ++)
        {
            int angle = h/60;
            float c = (float(vp)/100) * (float(sp)/100);
            float x = c * (1 - fabs(fmod(fmod(float(h) / 60.0, 6), 2) -1));
//            float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
            float m = (float(vp)/100) - c;
//            qInfo("angle %d c %d x %d m %d",angle,c,x,m);


            switch (angle)
            {
                case 0:
                    r = c;
                    g = x;
                    b = 0;
                    break;
                case 1:
                    r = x;
                    g = c;
                    b = 0;
                    break;
                case 2:
                    r = 0;
                    g = c;
                    b = x;
                    break;
                case 3:
                    r = 0;
                    g = x;
                    b = c;
                    break;
                case 4:
                    r = x;
                    g = 0;
                    b = c;
                    break;
                case 5:
                    r = c;
                    g = 0;
                    b = x;
                    break;
            }
            r = (r+m)*255;
            g = (g+m)*255;
            b = (b+m)*255;
//            qInfo("r %d g %d b %d",r,g,b);
            img->setPixelColor(sp,vp,QColor(int(r),int(g),int(b)));
        }
    }
}

void ColorPick::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        int xRelative = e->pos().x() * 100 / this->width();
        int yRelative = e->pos().y() * 100 / this->height();
        QColor color = img->pixelColor(xRelative,yRelative);
        canvas->setColorPen(color);
        display->setColor(color);
//        qInfo() << "pos" << xRelative << yRelative;
    }
}


