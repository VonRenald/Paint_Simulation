#pragma once
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QMouseEvent>

#include "GeometryEngine.h"
#include "Brush.h"



#include <iostream>
class OpenGl :
    public QOpenGLWidget, protected QOpenGLFunctions
{   Q_OBJECT
public:
    //OpenGl(QWidget* parent = Q_NULLPTR);
    using QOpenGLWidget::QOpenGLWidget;
    ~OpenGl();
    void resizeWigdet(QSize s);
    void setBrush(Brush *brush);
    
public slots:
    void updTimer();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

    void updtTexture();
    
private:

    void drawLine(int x1, int y1, int x2, int y2);
    void drawLine(QPoint p1, QPoint p2);
    void drawPoint(int x, int y);
    void drawPoint(QPoint p);

    void drawBrush(QPoint p);
    QColor addColor(QColor c1, QColor c2, float alpha);


    QOpenGLShaderProgram program;
    GeometryEngine* geometries = nullptr;

    QOpenGLTexture* texture = nullptr;

    QMatrix4x4 projection;

    std::list<QPoint> lpoints;
    bool leftClickPress = false;
    QSize canvasSize;
    QColor color = QColor(0,0,255);
    QImage img;

    Brush* o_brush;

};



