#ifndef OPENGLV2_H
#define OPENGLV2_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include "openglengine.h"

#include <QVector2D>
#include <QVector3D>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

class OpenGlV2 : public QOpenGLWidget, protected QOpenGLFunctions
{   Q_OBJECT
public:
//    OpenGlWidget();
    using QOpenGLWidget::QOpenGLWidget;
    ~OpenGlV2();
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

#endif // OPENGLV2_H
