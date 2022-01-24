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
    //qInfo("-----------------------------------ok-----------------------------------");
}
void OpenGl::initTextures()
{
    //qInfo("-----------------------------------ok2-----------------------------------");
    canvasSize = QSize(255, 255);
    img = QImage(canvasSize.width(), canvasSize.height(), QImage::Format_RGB32);
    for (int y = 0; y < canvasSize.height(); y++)
    {
        for (int x = 0; x < canvasSize.width(); x++)
        {
            img.setPixelColor(x, y, QColor(x, y, 0));
            //            img->setPixelColor(x,y,QColor(x%256,y%256,255));
        }
    }
    // Load cube.png image
    texture = new QOpenGLTexture(img);
    //qInfo("-----------------------------------ok3-----------------------------------");
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
    //qInfo("-----------------------------------ok4-----------------------------------");
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
    //projection.perspective(fov, aspect, zNear, zFar);
    projection.ortho(-1,1,-1,1,-10,10);
}

void OpenGl::paintGL()
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

void OpenGl::resizeWigdet(QSize si)
{
    qInfo("resized2");
    this->resizeGL(this->size().width(),this->size().height());
    //this->setFixedSize(si);
    update();
}

void OpenGl::updtTexture()
{

    bool stop = false;
    while (lpoints.size() >= 2 && !stop)
    {
        QPoint p1 = lpoints.front();
        lpoints.pop_front();
        QPoint p2 = lpoints.front();


        if (p2.isNull())
        {
            lpoints.pop_front();
            drawPoint(p1);
            stop = true;
        }
        else
        {
            drawLine(p1, p2);
        }
    }

    texture = new QOpenGLTexture(img);
    //qInfo("-----------------------------------ok3-----------------------------------");
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void OpenGl::mousePressEvent(QMouseEvent* e)
{
    
    if (e->button() == Qt::LeftButton)
    {
        //qDebug() << "pressed";
        leftClickPress = true;
        //qDebug() << "pressed Left";
        int xRelative = e->pos().x() * canvasSize.width() / this->width();
        int yRelative = canvasSize.height() - (e->pos().y() * canvasSize.height() / this->height());
        
        lpoints.push_back(QPoint(xRelative, yRelative));


    }
}

void OpenGl::mouseReleaseEvent(QMouseEvent* e)
{
    
    if (e->button() == Qt::LeftButton && leftClickPress)
    {
        //qDebug() << "released";
        leftClickPress = false;
        lpoints.push_back(QPoint());
    }

}

void OpenGl::mouseMoveEvent(QMouseEvent* e)
{

    if (leftClickPress)
    {
        
        int xRelative = e->pos().x() * canvasSize.width() / this->width();
        int yRelative = canvasSize.height() - (e->pos().y() * canvasSize.height() / this->height());
        
        
        

        lpoints.push_back(QPoint(xRelative, yRelative));
        //qDebug() << "drag" << xRelative << yRelative;
        

    }
}

void OpenGl::drawLine(int x1, int y1, int x2, int y2)
{

    float a = float(y2 - y1);
    float ap = float(x2 - x1);
    a = (ap == 0) ? 0 : a / ap;

    float b = y2 - (a * x2);

    for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++)
    {
        int y = a * x + b;

        drawBrush(QPoint(x,y));
        //img.setPixelColor(x, y, QColor(0, 0, 255));

    }

    for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
    {
        int x = (a == 0) ? x1 : (float(y) - b) / a;
        drawBrush(QPoint(x, y));
        //img.setPixelColor(x, y, QColor(0, 0, 255));

    }


}
void OpenGl::drawLine(QPoint p1, QPoint p2)
{
    drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}
void OpenGl::drawPoint(int x, int y)
{
    drawBrush(QPoint(x, y));
    //img.setPixelColor(x, y, QColor(0, 0, 255));
}
void OpenGl::drawPoint(QPoint p)
{
    drawPoint(p.x(), p.y());
    //drawBrush(p);
}
void OpenGl::updTimer()
{
    updtTexture();
    update();
}
void OpenGl::setBrush(Brush* brush)
{
    o_brush = brush;
}
void OpenGl::drawBrush(QPoint p)
{
    //qDebug() << "draw1";
    QSize sizeBrush = o_brush->get_Size();
    float* m_brush = o_brush->get_brush();
    QSize rayon = QSize((sizeBrush.width() - 1) / 2, (sizeBrush.height() - 1) / 2);
    QPoint global_loc;
    //qDebug() << "draw2";
    for (int j = 0; j < sizeBrush.height(); j++)
    {
        for (int i = 0; i < sizeBrush.width(); i++)
        {
            //qDebug() << "draw3";
            global_loc = QPoint(p.x() - rayon.width() + i, p.y() - rayon.height() + j);
            //qDebug() << global_loc;
            if (global_loc.x() >= 0 and global_loc.x() < canvasSize.width() and
                global_loc.y() >= 0 and global_loc.y() < canvasSize.height())
            {
                QColor pixel = img.pixelColor(global_loc.x(), global_loc.y());
                img.setPixelColor(global_loc.x(), global_loc.y(), addColor(pixel,color, m_brush[i + j * sizeBrush.width()]));
                //qDebug() << "draw4";
            }
        }
    }

}

QColor OpenGl::addColor(QColor c1, QColor c2, float alpha)
{
    int red = c1.red() - (c1.red() * alpha)  + (c2.red() * alpha);
    red = (red > 255) ? 255 : red;
    int green = c1.green() - (c1.green() * alpha) + (c2.green() * alpha);
    green = (green > 255) ? 255 : green;
    int blue = c1.blue() - (c1.blue() * alpha) + (c2.blue() * alpha);
    blue = (blue > 255) ? 255 : blue;
    return QColor(red, green, blue);
}

