#ifndef SCENE1_H
#define SCENE1_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
class Scene1 : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    using QOpenGLWidget::QOpenGLWidget;
    ~Scene1();
protected:
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    void initializeGL() override;
};

#endif // SCENE1_H
