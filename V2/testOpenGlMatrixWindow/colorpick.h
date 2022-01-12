#ifndef COLORPICK_H
#define COLORPICK_H

#include "opengl.h"
#include "colordisplay.h"

#include <QOpenGLWidget>
#include <QImage>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>

#include <stdlib.h>
#include <cmath>

class ColorPick : public QOpenGLWidget
{
public:
    ColorPick(OpenGl *openGl,ColorDisplay *colorDisplay);
public slots:
    void setH(int val);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    void setPalette();

    int h;
    int s;
    int v;

    OpenGl *canvas;
    ColorDisplay *display;

    QImage *img;
    QPainter painter;
};

#endif // COLORPICK_H
