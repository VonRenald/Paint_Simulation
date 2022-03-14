#include "scene.h"

#include <QDebug>


//Scene::Scene(QWidget *parent) : QOpenGLWidget(parent)
//{
//    //plan = new Pan()
//}
Scene::~Scene()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete plan;
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
"uniform vec2 Coor2;\n"
"uniform vec2 Coor3;\n"
"uniform vec2 Coor4;\n"
"uniform vec2 Coor5;\n"
"uniform vec2 Coor6;\n"
"uniform vec2 Coor7;\n"
"uniform vec2 Coor8;\n"
"uniform vec2 allP[60];\n"
"varying vec2 v_texcoord;\n"
"uniform float texW;\n"
"uniform float winW;\n"
"uniform float brush[255];\n"
"uniform float ray;\n"

"float drawLine (vec2 p1, vec2 p2, vec2 uv, float a)\n"
"{\n"
"   float r = 0.;\n"
"   float one_px = 1. / texW; //not really one px\n"

//"   // get dist between points\n"
"   float d = distance(p1, p2);\n"

//"   // get dist between current pixel and p1\n"
"   float duv = distance(p1, uv);\n"

//"   //if point is on line, according to dist, it should match current uv \n"
"   r = 1.-floor(1.-(a*one_px)+distance (mix(p1, p2, clamp(duv/d, 0., 1.)),  uv));\n"

"   return r;\n"
"}\n"


"void main()\n"
"{\n"
"   float cx = floor((v_texcoord.x*texW)+0.5f);\n"
"   float cy = floor(((1.0f-v_texcoord.y)*texW)+0.5f);\n"
//shader V1
//"   vec2 c = vec2(cx,cy);//cx + cy * texW;\n"

//"   float lines = 0.;\n"
////"lines += drawLine(Coor,Coor2,c,1.0f);"
////"   for (int i =0;i<25;i+=1)\n"
//"   {\n"
//"        vec2 p = vec2(int(mod(float(i),5.0f)),i/5);//vec2(i%5,i/5);//.xy / texW.xy;\n"
//"        lines += drawLine(vec2(Coor.x,Coor.y),vec2(255,255),c,1.0f);//drawLine(Coor+p,Coor2+p,c,1.);//*brush[i];\n"
//"   }\n"
//"   vec4 color = texture2D(texture, v_texcoord);\n"

//"   color.r = lines;//color.r + 0.0f*lines;\n"
//"   color.r = (color.r>1.0f)? 1.0f:color.r;\n"
//"   color.g = color.g + 1.0f*lines;\n"
//"   color.g = (color.g>1.0f)? 1.0f:color.g;\n"
//"   color.b = color.b + 1.0f*lines;\n"
//"   color.b = (color.b>1.0f)? 1.0f:color.b;\n"
//"   gl_FragColor = vec4(lines,0.,0.,1.);\n"
//"   if (mod(cx,10.)==0.)\n"
//"       gl_FragColor = vec4(1.,1.,1.,1.);\n"
//""
//shader V2
//"   bool  b = false;\n"
//"   vec2 monPoint = vec2(0,0);"
//"   for (int i=0;i<30;i++)\n"
//"   {\n"
//"       bool etap = (cx==allP[i].x && cy==allP[i].y);\n"
//"       if (etap)\n"
//"       {\n"
//"           monPoint = allP[i];\n"
//"       }\n"
//"       b = b || etap;//b || false;//(cx == allP[i].x && cy == allP[i].y);\n "
//"   }\n"
//"   if(b){\n"
//"       int difX = int(cx-(monPoint.x-ray));\n"
//"       int difY = int(cy-(monPoint.y-ray));\n"
//"       int diam = 2*int(ray)+1;\n"
//"       int indexB = difX+difY*diam;\n"
//"       vec4 color = texture2D(texture, v_texcoord);\n"
//"       color.r = color.r + 0.0f*brush[indexB];\n"
//"       color.g = color.g + 1.0f*brush[indexB];\n"
//"       color.b = color.b + 1.0f*brush[indexB];\n"
//"       gl_FragColor = color;\n"
//shader V3
"   bool b = false;\n"
"   vec4 color = texture2D(texture, v_texcoord);\n"
"   int diam = 2*int(ray)+1;\n"
"   for (int i=0;i<60;i++)\n"
"   {\n"
"       bool etap = (cx >= allP[i].x - ray && cx <= allP[i].x+ray && cy >= allP[i].y-ray && cy <= allP[i].y+ray);\n"
"       if (etap)\n"
"       {\n"
//"           color = vec4(1.,0.,0.,1.);"
"           int difX = int(cx-(allP[i].x-ray));\n"
"           int difY = int(cy-(allP[i].y-ray));\n"
"           int indexB = difX+difY*diam;\n"
"           color.r = color.r + 1.0f*brush[indexB]*0.1;\n"
"           color.g = color.g + 1.0f*brush[indexB]*0.1;\n"
"           color.b = color.b + 1.0f*brush[indexB]*0.1;\n"
"       }\n"
"       b = b || etap;\n"
"   }\n"
"   gl_FragColor = color;\n"
//shaderV0
//"   if( cx >= Coor.x-ray && cx <= Coor.x+ray && cy >= Coor.y-ray && cy <= Coor.y+ray){\n"
//"       int difX = int(cx-(Coor.x-ray));\n"
//"       int difY = int(cy-(Coor.y-ray));\n"
//"       int diam = 2*int(ray)+1;\n"
//"       int indexB = difX+difY*diam;\n"
//"       vec4 color = texture2D(texture, v_texcoord);\n"
//"       color.r = color.r + 0.0f*brush[indexB];\n"
//"       color.g = color.g + 1.0f*brush[indexB];\n"
//"       color.b = color.b + 1.0f*brush[indexB];\n"
//"       gl_FragColor = color;\n


//"   bool  b = false;\n"
//"   for (int i=0;i<30;i++)\n"
//"   {\n"
//"       b = b || (cx==allP[i].x && cy==allP[i].y);//b || false;//(cx == allP[i].x && cy == allP[i].y);\n "
//"   }\n"
//"   if(b){\n"
//"       gl_FragColor = vec4(1.,0.,0.,1.);\n"
//"   }else {\n"
//"       gl_FragColor = texture2D(texture, v_texcoord);\n"
//"   }\n"
"}\0";
void Scene::initializeGL()
{
    qDebug() << "initializeGL";
    initializeOpenGLFunctions();

    glClearColor(0.2, 0.2, 0.2, 1);

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
}
void Scene::initShaders()
{
    qDebug() << "initShaders";
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
void Scene::initTextures()
{
    qDebug() << "initTextures";
    img = QImage(255, 255, QImage::Format_RGB32);
    for (int y = 0; y < 255; y++)
    {
        for (int x = 0; x < 255; x++)
        {
            img.setPixelColor(x, y, QColor(0, 255, 0));
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
void Scene::resizeGL(int w, int h)
{
//    qDebug() << "resizeGL" << w << h;

    // Reset projection
    projection.setToIdentity();
    // Set ortho projection
    projection.ortho(-1,1,-1,1,-10,10);
    //update();
}
void Scene::paintGL()
{
    step ++;
//    int i=0;
//    while (!lpoints.empty()  && i < 10){//&& i < 10
//        p_1 = lpoints.front();
//        lpoints.pop_front();
//        i++;
//        qDebug() << "paintGL" << i;
        // Clear color and depth buffer
        fbo->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture->bind();

        // Calculate model view transformation
    //    qDebug() << "2" << lpoints.size();
        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -4);
        QPoint coor = p_1*255/500;
        QPoint coor2 = p_2*255/500;
        QPoint coor3 = p_3*255/500;
        QPoint coor4 = p_4*255/500;
        QPoint coor5 = p_5*255/500;
        QPoint coor6 = p_6*255/500;
        QPoint coor7 = p_7*255/500;
        QPoint coor8 = p_8*255/500;
        // Set modelview-projection matrix
        program.setUniformValue("mvp_matrix", projection * matrix);
        // Use texture unit 0 which contains cube.png
        program.setUniformValue("texture", 0);
        program.setUniformValue("xCoor",p_1.x()/500.0f);
        program.setUniformValue("yCoor",1.0f-(p_1.y()/500.0f));
        program.setUniformValue("Coor",coor);
        program.setUniformValue("Coor2",coor2);
        program.setUniformValue("Coor3",coor3);
        program.setUniformValue("Coor4",coor4);
        program.setUniformValue("Coor5",coor5);
        program.setUniformValue("Coor6",coor6);
        program.setUniformValue("Coor7",coor7);
        program.setUniformValue("Coor8",coor8);
        program.setUniformValueArray("allP",p2p,60);
        program.setUniformValue("texW", 255.0f);
        program.setUniformValue("winW", 500.0f);
        program.setUniformValueArray("brush",brush,25,1);
        program.setUniformValue("ray",2.0f);
        //program.setAttributeValue("Coor");

        // Draw cube geometry
        plan->drawPlanGeometry(&program);
        //GLuint textureid = fbo -> texture();
        fbo->release();
    //    plan->drawPlanGeometry(&program);
        QImage img2 = fbo -> toImage();
//        img2.save("rendertotexture.jpg");
        texture = new QOpenGLTexture(img2.mirrored());
        texture->setMinificationFilter(QOpenGLTexture::Nearest);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::Repeat);

//    }
//    qDebug() << "aa";
    plan->drawPlanGeometry(&program);
}
void Scene::mousePressEvent(QMouseEvent *e)
{
    lpointsToAdd.push_back(e->pos());
}
void Scene::mouseReleaseEvent(QMouseEvent *e)
{
//    qDebug() << lpointsToAdd;

//    QPoint p1 = lpointsToAdd.front();
//    lpointsToAdd.pop_front();
    QPoint p2 = e->pos();

    lpoints.push_back(p2);
//    addPointLine(p1,p2);

}
void Scene::mouseMoveEvent(QMouseEvent* e)
{
//    qDebug() << "mouse" << e->pos();

    lpointsToAdd.push_back(e->pos());

    if (lpointsToAdd.size() >= 2)
    {
        QPoint p1 = lpointsToAdd.front();
        lpointsToAdd.pop_front();
        QPoint p2 = lpointsToAdd.front();

        //lpoints.push_back(p1);
        addPointLine(p1,p2);
        //lpoints.push_back(p2);

    }


}
void Scene::print(int value)
{
    qDebug() << "ok" << value;
    //glBindFramebuffer(FRAMEBUFFER,fbo);
}
void Scene::initExt()
{
    initializeGL();
    //resizeGL(500,500);
}
void Scene::addPointLine(QPoint p1, QPoint p2)
{
    int dx = abs(p1.x()-p2.x());
    int dy = abs(p1.y()-p2.y());
    int nb = int(sqrt(dx*dx+dy*dy));

    float yPas = float(p2.y() - p1.y())/nb;
    float xPas = float(p2.x() - p1.x())/nb;
    //qDebug() << p1 << p2;
    //qDebug() << xPas << yPas;
    QVector2D p = QVector2D(p1);
    QPoint p2add;

    for(int i=0; i<nb+1;i++)
    {
        p = QVector2D(p.x()+xPas,p.y()+yPas);
        p2add = QPoint(p.x(),p.y());
        //qDebug() << i << p << p2add;
        lpoints.push_back(p2add);
    }
    //------------------------------------------------------------------

////    qDebug() << "p1 p2" << p1 << p2;
//    int ydiff = p2.y() - p1.y();
//    int xdiff = p2.x() - p1.x();
////    qDebug() << p2.x()-p1.x();
//    float slope = (p2.x()-p1.x()==0)?(p2.y()-p1.y()):float(p2.y()-p1.y())/float(p2.x()-p1.x());
////    qDebug() << "slope" << slope;
//    int dx = abs(p1.x()-p2.x());
//    int dy = abs(p1.y()-p2.y());
//    int nb = int(sqrt(dx*dx+dy*dy));
////    qDebug() << "nb" << nb;
//    for (int i = 0; i<nb+1;i++)
//    {
//        int y = (slope==0)?0:ydiff*(i/float(nb));
//        int x = (slope==0)?xdiff*(i/float(nb)):y/slope;
//        lpoints.push_back(QPoint(p1.x()+x,p1.y()+y));
////        qDebug() << i << x << y;
//    }




    //------------------------------------------------------------------
//    float a = float(p2.y()-p1.y());
//    float ap = float(p2.x()-p1.x());
//    a = (ap==0)? 0:a/ap;
//    float b = p2.y() -(a * p2.x());
//    QPoint addp;
//    for (int x = std::min(p1.x(),p2.x()); x <= std::max(p1.x(),p2.x());x++)
//    {
//        int y = a*x+b;
//        addp = QPoint(x,y);
//        if (std::find(lpoints.begin(),lpoints.end(),addp) == lpoints.end())
//            lpoints.push_back(addp);
//        //qDebug() << "add" << x << y;
//    }

//    for (int y = std::min(p1.y(),p2.y()); y <= std::max(p1.y(),p2.y());y++)
//    {
//        int x = (a==0)? p1.x():(float(y)-b)/a;
//        addp = QPoint(x,y);
//        if (std::find(lpoints.begin(),lpoints.end(),addp) == lpoints.end())
//            lpoints.push_back(addp);
//        //qDebug() << "add" << x << y;
//    }
}
void Scene::extUpdate()
{
//    qDebug() << lpoints;
    while (lpointsToAdd.size() >= 2)
    {
        QPoint p1 = lpointsToAdd.front();
        lpointsToAdd.pop_front();
        QPoint p2 = lpointsToAdd.front();

        //lpoints.push_back(p1);
        addPointLine(p1,p2);
        //lpoints.push_back(p2);

    }
    if(!lpoints.empty())
    {



        for(int i=0; i<60;i++)
        {
            if(!lpoints.empty())
            {
                QPoint p = lpoints.front()*255/500;
                p2p[i] = QVector2D(int(p.x()),int(p.y()));

//                qDebug() << i << p2p[i];
                lpoints.pop_front();
            }
            else
            {
                p2p[i] = QVector2D (0,0);
            }
        }
        qDebug() << "updt";
        update();


    }


}
