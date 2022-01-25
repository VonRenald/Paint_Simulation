#pragma once
#include <QOpenGLWidget>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "PerlinNoise.h"
#include "PerlinDS.h"
class Canvas :
    public QOpenGLWidget
{
public:
    Canvas(QWidget* parent = nullptr);
    ~Canvas();
protected:
    void paintEvent(QPaintEvent* event);
private:

    QImage* img;
    QPainter painter;
};

