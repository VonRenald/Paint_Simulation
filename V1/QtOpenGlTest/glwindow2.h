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
#include <QLabel>





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

    void updPenRed(int red);
    void updPenGreen(int green);
    void updPenBlue(int blue);

protected:
    void paintEvent(QPaintEvent *event) ;

private:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void updPenColor();

    bool press;
    bool reset;

    int penSize;

    int R;
    int G;
    int B;

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

    QSlider *S_R;
    QSlider *S_G;
    QSlider *S_B;

    QLabel *L_R;
    QLabel *L_G;
    QLabel *L_B;

};

#endif // GLWINDOW2_H
