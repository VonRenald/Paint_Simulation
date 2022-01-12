#ifndef COLORDISPLAY_H
#define COLORDISPLAY_H

#include <QOpenGLWidget>
#include <QImage>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>


class ColorDisplay : public QOpenGLWidget
{
public:
    ColorDisplay();
    void setColor(QColor color);
protected:
    void paintEvent(QPaintEvent *event);
private:

    QImage *img;
    QPainter painter;
};

#endif // COLORDISPLAY_H
