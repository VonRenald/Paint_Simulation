#ifndef HELPER_H
#define HELPER_H

#include "glwidget.h"

#include <QBrush>
#include <QOpenGLWidget>
#include <QFont>
#include <QPen>
#include <QWidget>

class Helper
{
public:
    Helper();

    GLWidget *parent;

    void paint(QPainter *painter, QPaintEvent *event);
    bool start;
//    void draw(QMouseEvent *e);
    bool pressed;

protected:
//    void mousePressEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *e);
private:
    QBrush background;
    QPen pen;





};

#endif // HELPER_H
