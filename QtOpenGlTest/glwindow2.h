#ifndef GLWINDOW2_H
#define GLWINDOW2_H


#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>

#include <list>




class GlWindow2 : public QOpenGLWidget
{
//    Q_OBJECT
public:
    GlWindow2();
public slots:
    void resetAfeterResize();

protected:
    void paintEvent(QPaintEvent *event) ;

private:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    bool press;
    bool reset;

    int x;
    int y;
    int xp;
    int yp;

//    std::list<int> lx;
//    std::list<int> ly;



    QBrush background;
    QPen pen;
    QPainter painter;

};

#endif // GLWINDOW2_H
