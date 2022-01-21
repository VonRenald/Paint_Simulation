#ifndef OPENGL_H
#define OPENGL_H

#include <QOpenGLWidget>
#include <QImage>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>

#include <algorithm>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <QInputDialog>
#include <QLineEdit>
#include <QDir>


class OpenGl : public QOpenGLWidget
{
public:
    OpenGl();

    void setColorPen(QColor color);
    void freePath();

    float getRatioXpY();
    QPoint getCanvasSize();

    void newCanvas(int w,int h);
public slots:
    void resetCanvas();
    void setSizeParth(int size);
    void triggerInitPath();
    void updTimer();
    void saveCanvas();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:

    void drawPoint(int x, int y);
    void drawPoint(QPoint p);

    void drawLine(int x1, int y1, int x2, int y2);
    void drawLine(QPoint p1, QPoint p2);

    void drawCercle(int x, int y);

    void initPathCercle(int r);


    bool isPressed;

    int sizeCanvas[2];
    int *path;
    int sizePath;
    bool pathInit = false;

    float ratioXpY;

    QColor colorPen;

    QImage *img;
    QPainter painter;

    std::list<QPoint> lpoints;

};

#endif // OPENGL_H
