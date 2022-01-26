#pragma once
#include <QOpenGLWidget>>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "Brush.h"
#include "PaintBrush.h"
#include "BrushMultiple.h"
class CanvasBrush :
    public QOpenGLWidget
{
public:
    CanvasBrush(QWidget* parent = nullptr);
    ~CanvasBrush();
protected:
    void paintEvent(QPaintEvent* event);
    
private:

    QImage* img;
    QPainter painter;
};

