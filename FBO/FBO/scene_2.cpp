#include "scene_2.h"

#include <QDebug>


//Scene::Scene(QWidget *parent) : QOpenGLWidget(parent)
//{
//    //plan = new Pan()
//}
Scene_2::~Scene_2()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete plan;
    delete scene1;
    delete fbo;
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
        "    //gl_Position = a_position;\n"
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
"uniform float xCoor;\n"
"uniform float yCoor;\n"
"uniform vec2 Coor;\n"
"varying vec2 v_texcoord;\n"
"uniform float texW;\n"
"uniform float winW;\n"
"uniform float brush[25];\n"
"uniform float ray;\n"
"void main()\n"
"{\n"
"   gl_FragColor = texture2D(texture, v_texcoord);\n"
"}\0";
void Scene_2::initializeGL()
{
    //qDebug() << "initializeGL";
    initializeOpenGLFunctions();

    glClearColor(0.0, 0.0, 1, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    plan = new Plan;

    fbo =new QOpenGLFramebufferObject(500,500);
    //scene1->glBindFramebuffer(scene1,fbo);
}
void Scene_2::initShaders()
{
    //qDebug() << "initShaders";
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
}
void Scene_2::initTextures()
{
    //qDebug() << "initTextures";
    img = QImage(255, 255, QImage::Format_RGB32);
    for (int y = 0; y < 255; y++)
    {
        for (int x = 0; x < 255; x++)
        {
            img.setPixelColor(x, y, QColor(255, 0, 0));
            //            img->setPixelColor(x,y,QColor(x%256,y%256,255));
        }
    }
    texture = new QOpenGLTexture(img);
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
void Scene_2::resizeGL(int w, int h)
{
    //qDebug() << "resizeGL" << w << h;

    // Reset projection
    projection.setToIdentity();
    // Set ortho projection
    projection.ortho(-1,1,-1,1,-10,10);
    //update();
}
void Scene_2::paintGL()
{
    scene1 = new Scene(this);
    scene1->initExt();
    fbo->bind();

//    scene1->print();
//    scene1->initExt();
//    scene1->update();
    fbo->release();
    img = fbo->toImage();
    texture = new QOpenGLTexture(img);
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    //qDebug() << "paintGL";
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -4);
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);


    // Draw cube geometry
    plan->drawPlanGeometry(&program);

}

