#include "CanvasPN.h"
#include "qdebug.h"
CanvasPN::CanvasPN(QWidget* parent) : QOpenGLWidget(parent)
{
    //this->setFixedSize(500,500);
    QSize si = QSize(1025, 1025);
    PerlinDS perlin = PerlinDS(si.width(),255);
    
    img = new QImage(si, QImage::Format_RGB32);
    for (int y = 0; y < si.height(); y++)
    {
        for (int x = 0; x < si.width(); x++)
        {
            int col = perlin.getValue(x, y);
            img->setPixelColor(x, y, QColor(col, col, col));
        }
    }



    //QSize si = QSize(512, 512);
    //img = new QImage(si, QImage::Format_RGB32);

    //PerlinNoise perlin = PerlinNoise(621);
    //int minV = perlin.noise(0, 0, 0) * 255;
    //int maxV = minV;
    //int col;

    //int postAv = 0;
    //int avancement = 0;
    //for (int y = 0; y < si.height(); y++)
    //{
    //    for (int x = 0; x < si.width(); x++)
    //    {
    //        double j = (double)y / ((double)si.height() / 10.0);
    //        double i = (double)x / ((double)si.width() / 10.0);
    //        col = perlin.noise(i, j, 0) * 255;
    //        //qDebug() << col;
    //        img->setPixelColor(x, y, QColor(col, col, col));
    //        if (col > maxV)
    //            maxV = col;
    //        if (col < minV)
    //            minV = col;
    //    }
    //    avancement = y / ((float)si.height()) * 100;
    //    if (postAv != avancement)
    //    {
    //        postAv = avancement;
    //        qDebug() << avancement;
    //    }
    //}


    //for (int y = 0; y < si.height(); y++)
    //{
    //    for (int x = 0; x < si.width(); x++)
    //    {
    //        col = img->pixelColor(x, y).red();
    //        col = (col - minV) / ((float)(maxV - minV)) * 255;
    //        img->setPixelColor(x, y, QColor(col, col, col));
    //    }
    //}
}
CanvasPN::~CanvasPN()
{

}
void CanvasPN::paintEvent(QPaintEvent* event)
{
    painter.begin(this);
    painter.drawImage(this->parentWidget()->rect(), *img, img->rect());
    painter.end();
}
