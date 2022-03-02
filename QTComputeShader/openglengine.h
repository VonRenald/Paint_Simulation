#ifndef OPENGLENGINE_H
#define OPENGLENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>

#include <QVector2D>
#include <QVector3D>

class OpenGlEngine : private QOpenGLExtraFunctions// protected QOpenGLFunctions,
{
public:
    OpenGlEngine();
    virtual ~OpenGlEngine();

    void drawCubeGeometry(QOpenGLShaderProgram* program);
    void printWorkGroupsCapabilities();
private:
    void initCubeGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // OPENGLENGINE_H
