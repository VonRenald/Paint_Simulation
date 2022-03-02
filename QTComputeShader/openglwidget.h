#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "openglengine.h"

class OpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{   Q_OBJECT
public:
//    OpenGlWidget();
    using QOpenGLWidget::QOpenGLWidget;
    ~OpenGlWidget();
    void NewTexture(int w, int h);
    void resizeWigdet(QSize s);
    void printWGC();
protected:
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    void initializeGL() override;
    void initShaders();
    void initTextures();

    QOpenGLShaderProgram program;
    OpenGlEngine* geometries = nullptr;
    QOpenGLTexture* texture = nullptr;
    QMatrix4x4 projection;

    QSize canvasSize;
    QImage img;
};

#endif // OPENGLWIDGET_H
