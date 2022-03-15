#include "canvasbrush.h"

#include <qdebug.h>

#define RAY 25
CanvasBrush::CanvasBrush(QWidget* parent) : QOpenGLWidget(parent)
{
    //this->setFixedSize(500,500);

    int rayon = RAY;
    int diametre = 2 * rayon + 1;
    QSize si = QSize(diametre, diametre);
    //Brush bru = Brush(rayon);
    //PerlinDS bru = PerlinDS(si.width(), 16);
    PaintBrush bru = PaintBrush(rayon);
    //BrushMultiple bru = BrushMultiple(diametre);

    img = new QImage(si, QImage::Format_RGB32);
    for (int y = 0; y < si.height(); y++)
    {
        for (int x = 0; x < si.width(); x++)
        {
            int col = bru.getValue(x, y) *255;
            QColor color;

            color = QColor(col, col, col);
            img->setPixelColor(x, y, color);
        }
    }


}
CanvasBrush::~CanvasBrush()
{

}
void CanvasBrush::paintEvent(QPaintEvent* event)
{
    painter.begin(this);
    painter.drawImage(this->rect(), *img, img->rect());
    painter.end();
}
void CanvasBrush::updtExt()
{
    int rayon = RAY;
    int diametre = 2 * rayon + 1;
    QSize si = QSize(diametre, diametre);
    //Brush bru = Brush(rayon);
    //PerlinDS bru = PerlinDS(si.width(), 16);
    PaintBrush bru = PaintBrush(rayon);
    //BrushMultiple bru = BrushMultiple(diametre);

    img = new QImage(si, QImage::Format_RGB32);
    for (int y = 0; y < si.height(); y++)
    {
        for (int x = 0; x < si.width(); x++)
        {
            int col = bru.getValue(x, y) *255;
            QColor color;

            color = QColor(col, col, col);
            img->setPixelColor(x, y, color);
        }
    }
    update();
}

