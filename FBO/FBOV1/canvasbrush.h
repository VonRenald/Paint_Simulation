#ifndef CANVASBRUSH_H
#define CANVASBRUSH_H

#include <QOpenGLWidget>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "brush.h"
#include "paintbrush.h"
#include "brushmultiple.h"

class CanvasBrush :
    public QOpenGLWidget
{
public:
    CanvasBrush(QWidget* parent = nullptr);
    ~CanvasBrush();
public slots:
    void updtExt();
protected:
    void paintEvent(QPaintEvent* event);

private:

    QImage* img;
    QPainter painter;
};


#endif // CANVASBRUSH_H
