#pragma once
#include <qopenglwidget.h>
#include "ColorDispaly.h"
#include "OpenGl.h"

#include <QOpenGLWidget>
#include <QImage>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>

#include <stdlib.h>
#include <cmath>
class ColorPick :
    public QOpenGLWidget
{
public:
    ColorPick(ColorDisplay* colorDisplay, OpenGl* canvas, QWidget* parent = nullptr);
public slots:
    void setH(int val);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* e);
private:
    void setPalette();

    int h;
    int s;
    int v;

    ColorDisplay* display;
    OpenGl* o_canvas;
    QImage* img;
    QPainter painter;
};

