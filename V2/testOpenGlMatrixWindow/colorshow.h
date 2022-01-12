#ifndef COLORSHOW_H
#define COLORSHOW_H


#include <QOpenGLWidget>
#include <QImage>
#include <QBrush>
#include <QPen>
#include <QPainter>

class ColorShow : public QOpenGLWidget
{
public:
    ColorShow();
    void setColor(QColor color);
protected:
//    void paintEvent(QPaintEvent *event);
private:

    QImage *img;
    QPainter painter;
};

#endif // COLORSHOW_H
