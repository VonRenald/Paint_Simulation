#include "window.h"
#include <QDebug>
#include <QTimer>

Window::Window()
{



        this->setMinimumSize(380,300);
//        qInfo() << this->geometry().size();
        test = new QWidget();
        opengl = new OpenGl();
        colorDisplay = new ColorDisplay();
        colorPick = new ColorPick(opengl,colorDisplay);
        opengl->setParent(test);
//        l_canvasLayout = new QVBoxLayout(test);
//        l_canvasLayout->addWidget(opengl);
//        Qt::AlignCenter

        toolWidth = 75;

        colorPick->setMaximumSize(toolWidth,toolWidth);
        colorDisplay->setMaximumSize(toolWidth/2,toolWidth/2);

        b_reset = new QPushButton("reset",this);
        b_reset->setMaximumWidth(toolWidth);

        b_save = new QPushButton("save",this);
        b_save->setMaximumWidth(toolWidth);

        b_newCnavas = new QPushButton("new canvas",this);
        b_newCnavas->setMaximumWidth(toolWidth);
//        b2 = new QPushButton("2",this);
//        b2->setMaximumWidth(toolWidth);

        s_size = new QSlider(Qt::Horizontal,this);
        s_size->setRange(0,30);
        s_size->setMaximumWidth(toolWidth);

        l_outilsEcran = new QHBoxLayout(this);
        l_outils = new QVBoxLayout(this);
        l_color = new QVBoxLayout(this);

        s_colorSlider = new QSlider(Qt::Horizontal,this);
        s_colorSlider->setRange(0,359);
        s_colorSlider->setMaximumWidth(toolWidth);

        l_color->addWidget(s_colorSlider);
        l_color->addWidget(colorPick);
        l_color->addWidget(colorDisplay);

        l_outils->addWidget(b_newCnavas);
        l_outils->addWidget(b_save);
        l_outils->addWidget(b_reset);
        l_outils->addWidget(s_size);
        l_outils->addLayout(l_color);

        l_outilsEcran->addLayout(l_outils);
        l_outilsEcran->addWidget(test);

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, opengl, &OpenGl::updTimer);
        timer->start(50);

        connect(s_colorSlider,&QSlider::sliderMoved,colorPick,&ColorPick::setH);
        connect(b_newCnavas,&QPushButton::pressed,this,&Window::creatNewCanvas);
        connect(b_reset,&QPushButton::pressed,opengl,&OpenGl::resetCanvas);
        connect(s_size,&QSlider::sliderMoved,opengl,&OpenGl::setSizeParth);
        connect(s_size,&QSlider::sliderReleased,opengl,&OpenGl::triggerInitPath);
        connect(b_save,&QPushButton::pressed,opengl,&OpenGl::saveCanvas);
        //saveCanvas

}



void Window::resizeEvent(QResizeEvent *event)
{
//    qInfo() << "resized" << this->geometry().size();
//    float r = opengl->getRatioXpY();
//    int x,y;

////    qInfo() << r << x << y;
////    if (r >=1){

////        x = this->geometry().size().width()-toolWidth-50;
////        y = x/r;
////    }
////    else
////    {
////        y = this->geometry().size().height()-50;
////        x = y * r;
//////        y = this->geometry().size().height()-toolWidth;
//////        x = y * r;

////    }
//    opengl->setMinimumSize(x,y);
//    opengl->setMaximumSize(x,y);
//    opengl->setMinimumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
//    opengl->setMaximumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
    openGlResize();
}

void Window::closeEvent (QCloseEvent *event)
{
    opengl->freePath();
}

void Window::creatNewCanvas()
{
    bool ok;
    int w,h;
    w = QInputDialog::getInt(this, tr("new canvas"),
                                   tr("X size:"), 255, 1, 2147483647, 1, &ok);
    if(ok){
        h = QInputDialog::getInt(this, tr("new canvas"),
                                       tr("Y size:"), 255, 1, 2147483647, 1, &ok);
        if(ok)
        {
            opengl->newCanvas(w,h);
            openGlResize();
//            float r = opengl->getRatioXpY();
//            float xw = this->geometry().size().width()-toolWidth - 50;
//            float yw = this->geometry().size().height()-20;
//            int x,y;
//            if(xw >= yw * r) //xw est plus grand que nécessaire
//            { // on ce fixe sur y
//                x = xw;
//                y = x/r;
//            }
//            else
//            {
////                if(yw >= xw / r) yw est assez grand
////                {

////                }
//                y = yw;
//                x = y/r;
//            }
////            int x,y;
////            if (r >=1){

////                x = this->geometry().size().width()-toolWidth-50;
////                y = x/r;
////            }
////            else
////            {
////                y = this->geometry().size().height()-50;
////                x = y * r;
////        //        y = this->geometry().size().height()-toolWidth;
////        //        x = y * r;

////            }
//            opengl->setMinimumSize(x,y);
//            opengl->setMaximumSize(x,y);
////            opengl->setMinimumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
////            opengl->setMaximumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
        }
    }
}
void Window::openGlResize() // x/y=r  x=r*y x/r=y
{
    qInfo("Test %d %d Fenetre %d %d",test->geometry().size().width(),test->geometry().size().height()
          , this->geometry().size().width(),this->geometry().size().height());
    float r = opengl->getRatioXpY();
    int x,y;
    float wx = test->geometry().size().width();
    float wy = test->geometry().size().height();
    QPoint canvas = opengl->getCanvasSize();
    if(wx/canvas.x() < wy/canvas.y())
    {
        x = wx;
        y = x/r;
    }
    else
    {
        y = wy;
        x = y*r;
    }



    opengl->setMinimumSize(x,y);
    opengl->setMaximumSize(x,y);
//    opengl->setMinimumSize(test->geometry().size().width(),test->geometry().size().height());
//    opengl->setMaximumSize(test->geometry().size().width(),test->geometry().size().height());
}
