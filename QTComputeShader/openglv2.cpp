#include "openglv2.h"
#include "QDebug"

//OpenGlWidget::OpenGlWidget()
//{

//}
OpenGlV2::~OpenGlV2()
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
//"#version 430\n"
//"layout (local_size_x = 16, local_size_y = 16) in;\n"
//"layout (rgba32f, binding = 0) uniform image2D img_output;\n"
//"void main() {\n"
//  // Aucun tableau de donnée n'étant passé au moment de la création de la texture,
//  // c'est le compute shader qui va dessiner à l'intérieur de l'image associé
//  // à la texture.
//  // gl_LocalInvocationID.xy * gl_WorkGroupID.xy == gl_GlobalInvocationID
//"  ivec2 coords = ivec2(gl_GlobalInvocationID);\n"
//  // Pour mettre en evidence. Les groupes de travail locaux on dessine un damier."
//"  vec4 pixel;\n"
//"  if ( ((gl_WorkGroupID.x & 1u) != 1u) != ((gl_WorkGroupID.y & 1u) == 1u)) {\n"
//"    pixel = vec4(1.0,.5,.0,1.0);\n"
//"  }\n"
//"  else {\n"
//"    pixel = vec4(.0,.5,1.0,1.0);\n"
//"  }\n"
//"  imageStore(img_output, coords, pixel);\n"
//"}\0";

static const char* fragmentshadersource =
"#ifdef GL_ES\n"
"// Set default precision to medium\n"
"precision mediump int;\n"
"precision mediump float;\n"
"#endif\n"
"uniform sampler2D texture;\n"
"varying vec2 v_texcoord;\n"
"void main()\n"
"{   //gl_FragColor = texture2D(texture, v_texcoord);\n "
"gl_FragColor = vec4(1.0f*v_texcoord.x,0,1.0f*v_texcoord.y,1.0f);"
"//if (v_texcoord.x > 0.5f) {gl_FragColor = vec4(1.0f,0.0f,1.0f,1.0f);}\n "
"//else {gl_FragColor = texture2D(texture, v_texcoord);}\n"
"//gl_FragColor = vec4(1.0f,0.0f,1.0f,1.0f);//vec4(255*v_texcoord[0],0,255*v_texcoord[1],1);\n"
"}\0";


void OpenGlV2::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5, 0.5, 0.5, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    geometries = new OpenGlEngine;
}
void OpenGlV2::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexshadersource))
        close();
//    if (!program.addShaderFromSourceCode(QOpenGLShader::Compute, vertexshadersource))
//        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentshadersource))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
    //qInfo("-----------------------------------ok-----------------------------------");
}
void OpenGlV2::NewTexture(int w, int h)
{
    canvasSize = QSize(w, h);
    img = QImage(canvasSize.width(), canvasSize.height(), QImage::Format_RGB32);
    for (int y = 0; y < canvasSize.height(); y++)
    {
        for (int x = 0; x < canvasSize.width(); x++)
        {
            img.setPixelColor(x, y, QColor(x, 0, 0));
            //            img->setPixelColor(x,y,QColor(x%256,y%256,255));
        }
    }

    update();
}
void OpenGlV2::initTextures()
{
    NewTexture(255, 255);

    // Load cube.png image
    texture = new QOpenGLTexture(img);
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
void OpenGlV2::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    //qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    //const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    //projection.perspective(fov, aspect, zNear, zFar);
    projection.ortho(-1,1,-1,1,-10,10);
}
void OpenGlV2::paintGL()
{
    //qInfo("-----------------------------------ok5-----------------------------------");
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    //! [6]
        // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -4);
    //matrix.rotate(rotation);
    //qInfo("-----------------------------------ok5.5-----------------------------------");
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
    //! [6]

        // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    //qInfo("-----------------------------------ok5.6-----------------------------------");
    geometries->drawCubeGeometry(&program);

    //qInfo("-----------------------------------ok6-----------------------------------");
}
void OpenGlV2::resizeWigdet(QSize si)
{

    this->resizeGL(this->size().width(),this->size().height());
    //this->setFixedSize(si);
    update();
}
void OpenGlV2::printWGC()
{
    geometries->printWorkGroupsCapabilities();
}
