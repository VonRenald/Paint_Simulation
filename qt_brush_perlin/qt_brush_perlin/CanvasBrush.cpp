#include "CanvasBrush.h"
#include <qdebug.h>
CanvasBrush::CanvasBrush(QWidget* parent) : QOpenGLWidget(parent)
{
    //this->setFixedSize(500,500);
    
    int rayon = 512;
    int diametre = 2 * rayon + 1;
    QSize si = QSize(diametre, diametre);
    //Brush bru = Brush(rayon);
    //PerlinDS bru = PerlinDS(si.width(), 255);
    //PaintBrush bru = PaintBrush(rayon);
    BrushMultiple bru = BrushMultiple(diametre);

    img = new QImage(si, QImage::Format_RGB32);
    for (int y = 0; y < si.height(); y++)
    {
        for (int x = 0; x < si.width(); x++)
        {
            int col = bru.getValue(x, y) *255;
            QColor color;
            //if (col < 10)
            //{
            //    color = QColor(34, 66, 124);
            //}
            //else
            //{
            //    if (col < 50)
            //    {
            //        color = QColor(236, 213, 133);
            //    }
            //    else
            //    {
            //        if (col < 180)
            //        {
            //            color = QColor(67, 197, 67);
            //        }
            //        else
            //        {
            //            if (col < 230)
            //            {
            //                color = QColor(160, 160, 160);
            //            }
            //            else
            //            {
            //                color = QColor(255, 255, 255);
            //            }
            //            
            //        }
            //    }
            //}
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
    painter.drawImage(this->parentWidget()->rect(), *img, img->rect());
    painter.end();
}

