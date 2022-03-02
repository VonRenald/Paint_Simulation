#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "plan.h"

#include <QMouseEvent>

class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    //Scene(QWidget* parent = Q_NULLPTR);
    using QOpenGLWidget::QOpenGLWidget;
    ~Scene();
protected:
    void initializeGL() override;
    void initShaders();
    void initTextures();
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent* e) override;
private:

    Plan* plan = nullptr;
    QOpenGLShaderProgram program;
    QImage img;
    QOpenGLTexture* texture = nullptr;
    QMatrix4x4 projection;

    QPoint p = QPoint(0,0);

    GLfloat brush[25] = {
                    0.0f,0.5f,0.5f,0.5f,0.0f,
                    0.5f,0.8f,1.0f,0.8f,0.5f,
                    0.5f,1.0f,1.0f,1.0f,0.5f,
                    0.5f,0.8f,1.0f,0.8f,0.5f,
                    0.0f,0.5f,0.5f,0.5f,0.0f
                        };
};

#endif // SCENE_H
