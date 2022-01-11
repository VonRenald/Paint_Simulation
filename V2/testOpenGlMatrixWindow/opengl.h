#ifndef OPENGL_H
#define OPENGL_H

#include <QOpenGLWidget>
#include <QImage>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>


class OpenGl : public QOpenGLWidget
{
public:
    OpenGl();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:

    bool isPressed;

    int sizeCanvas[2];

    QImage *img;
    QPainter painter;

};

#endif // OPENGL_H
