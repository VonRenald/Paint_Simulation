#pragma once
#include <qopenglwidget.h>
#include <QOpenGLWidget>
#include <QImage>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>


class ColorDisplay : public QOpenGLWidget
{
public:
    ColorDisplay(QWidget* parent = nullptr);
    void setColor(QColor color);
protected:
    void paintEvent(QPaintEvent* event);
private:

    QImage* img;
    QPainter painter;
};

