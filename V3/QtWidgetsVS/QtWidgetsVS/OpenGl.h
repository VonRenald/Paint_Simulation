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

#include "GeometryEngine.h"



#include <iostream>
class OpenGl :
    public QOpenGLWidget, protected QOpenGLFunctions
{   Q_OBJECT
public:
    //OpenGl(QWidget* parent = Q_NULLPTR);
    using QOpenGLWidget::QOpenGLWidget;
    ~OpenGl();
    void resizeWigdet(QSize s);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();
    
private:
    QOpenGLShaderProgram program;
    GeometryEngine* geometries = nullptr;

    QOpenGLTexture* texture = nullptr;

    QMatrix4x4 projection;
};



