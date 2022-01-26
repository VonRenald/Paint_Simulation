#include "CanvasBrush.h"
#include <qdebug.h>
CanvasBrush::CanvasBrush(QWidget* parent) : QOpenGLWidget(parent)
{
    //this->setFixedSize(500,500);
    
    int rayon = 512;
    int diametre = 2 * rayon + 1;
    QSize si = QSize(diametre, diametre);
    //Brush bru = Brush(rayon);
    //PerlinDS perlin = PerlinDS(si.width(), 255);
    PaintBrush bru = PaintBrush(rayon);

    img = new QImage(si, QImage::Format_RGB32);
    for (int y = 0; y < si.height(); y++)
    {
        for (int x = 0; x < si.width(); x++)
        {
            int col = bru.getValue(x, y) * 255;
            img->setPixelColor(x, y, QColor(col, col, col));
        }
    }


}
CanvasBrush::~CanvasBrush()
{

}
void CanvasBrush::paintEvent(QPaintEvent* event)
{
    painter.begin(this);
    painter.drawImage(this->parentWidget()->rect(), *img, img->rect());
    painter.end();
}

