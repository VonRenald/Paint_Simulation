#ifndef SCENE_2_H
#define SCENE_2_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "plan.h"
#include "scene.h"
#include <QMouseEvent>
#include <QOpenGLFramebufferObject>

class Scene_2 : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    //Scene(QWidget* parent = Q_NULLPTR);
    using QOpenGLWidget::QOpenGLWidget;
    ~Scene_2();
protected:
    void initializeGL() override;
    void initShaders();
    void initTextures();
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:

    Plan* plan = nullptr;
    QOpenGLShaderProgram program;
    QImage img;
    QOpenGLTexture* texture = nullptr;
    QMatrix4x4 projection;
    Scene *scene1 = nullptr;
    QOpenGLFramebufferObject *fbo = nullptr;
};

#endif // SCENE_2_H
