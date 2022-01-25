#pragma once
#include <QOpenGLWidget>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "PerlinNoise.h"
#include "PerlinDS.h"
class CanvasPN :
    public QOpenGLWidget
{
public:
    CanvasPN(QWidget* parent = nullptr);
    ~CanvasPN();
protected:
    void paintEvent(QPaintEvent* event);
private:

    QImage* img;
    QPainter painter;
};

