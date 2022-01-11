#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class Helper;

class GLWidget : public QOpenGLWidget
{

public:
    GLWidget(Helper *helper, QWidget *parent);

    bool pressed;

public slots:
    void draw();

protected:
    void paintEvent(QPaintEvent *event) ;

//    void mousePressEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *e);

private:
        Helper *helper;

};

#endif // GLWIDGET_H
