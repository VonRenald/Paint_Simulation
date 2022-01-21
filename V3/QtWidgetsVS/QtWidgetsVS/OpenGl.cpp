#include "OpenGl.h"
#include <QDebug>

OpenGl::~OpenGl()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

static const char* vertexshadersource =
"#ifdef GL_ES\n"
"// Set default precision to medium\n"
"precision mediump int;\n"
"precision mediump float;\n"
"#endif\n"
"uniform mat4 mvp_matrix;\n"
"attribute vec4 a_position;\n"
"attribute vec2 a_texcoord;\n"
"varying vec2 v_texcoord;\n"
"void main()\n"
"{\n"
"    // Calculate vertex position in screen space\n"
"    gl_Position = mvp_matrix * a_position;\n"
"    // Pass texture coordinate to fragment shader\n"
"    // Value will be automatically interpolated to fragments inside polygon faces\n"
"    v_texcoord = a_texcoord;\n"
"}\0";

static const char* fragmentshadersource =
"#ifdef GL_ES\n"
"// Set default precision to medium\n"
"precision mediump int;\n"
"precision mediump float;\n"
"#endif\n"
"uniform sampler2D texture;\n"
"varying vec2 v_texcoord;\n"
"void main()\n"
"{   gl_FragColor = texture2D(texture, v_texcoord); }\0";
//! [0];

void OpenGl::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5, 0.5, 0.5, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    geometries = new GeometryEngine;
}

void OpenGl::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexshadersource))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentshadersource))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
    qInfo("-----------------------------------ok-----------------------------------");
}
void OpenGl::initTextures()
{
    qInfo("-----------------------------------ok2-----------------------------------");
    QImage img = QImage(255, 255, QImage::Format_RGB32);
    for (int y = 0; y < 255; y++)
    {
        for (int x = 0; x < 255; x++)
        {
            img.setPixelColor(x, y, QColor(x, y, 0));
            //            img->setPixelColor(x,y,QColor(x%256,y%256,255));
        }
    }
    // Load cube.png image
    texture = new QOpenGLTexture(img);
    qInfo("-----------------------------------ok3-----------------------------------");
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
    qInfo("-----------------------------------ok4-----------------------------------");
}

void OpenGl::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void OpenGl::paintGL()
{
    qInfo("-----------------------------------ok5-----------------------------------");
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    //! [6]
        // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -4.0);
    //matrix.rotate(rotation);
    qInfo("-----------------------------------ok5.5-----------------------------------");
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
    //! [6]

        // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    qInfo("-----------------------------------ok5.6-----------------------------------");
    geometries->drawCubeGeometry(&program);

    qInfo("-----------------------------------ok6-----------------------------------");
}

void OpenGl::resizeWigdet(QSize si)
{
    qInfo("resized2");
    this->resizeGL(this->size().width(),this->size().height());
    //this->setFixedSize(si);
    update();
}

//static const char* vertexshadersource =
//"#version 330 core\n"
//"layout (location = 0) in vec3 apos;\n"
//"void main()\n"
//"{\n"
//"   gl_position = vec4(apos.x, apos.y, apos.z, 1.0);\n"
//"}\0";
//
//static const char* fragmentshadersource =
//"#version 330 core\n"
//"out vec4 fragcolor;\n"
//"void main()\n"
//"{\n"
//"   fragcolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
