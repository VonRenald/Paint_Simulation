#ifndef GLWINDOW2_H
#define GLWINDOW2_H


#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QPainter>

#include <list>

#include <QPushButton>
#include <QSlider>





class GlWindow2 : public QOpenGLWidget
{

public:
    GlWindow2();

public slots:
    void resetAfeterResize();
    void upd();

    void setPenBlack();
    void setPenRed();
    void setPenGreen();
    void setPenBlue();

    void setPenSize(int size);

protected:
    void paintEvent(QPaintEvent *event) ;

private:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    bool press;
    bool reset;

    int penSize;

    std::list<int> lx;
    std::list<int> ly;



    QBrush background;
    QPen pen;
    QPainter painter;

    QSlider *S_sizepen;

    QPushButton *B_reset;
    QPushButton *B_blackPen;
    QPushButton *B_bluePen;
    QPushButton *B_redPen;
    QPushButton *B_greenPen;

};

#endif // GLWINDOW2_H
