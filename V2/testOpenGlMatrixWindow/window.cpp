#include "window.h"
#include <QDebug>

Window::Window()
{



        this->setMinimumSize(380,300);
//        qInfo() << this->geometry().size();
        opengl = new OpenGl();
        colorDisplay = new ColorDisplay();
        colorPick = new ColorPick(opengl,colorDisplay);


        toolWidth = 75;

        colorPick->setMaximumSize(toolWidth,toolWidth);
        colorDisplay->setMaximumSize(toolWidth/2,toolWidth/2);

        b_reset = new QPushButton("reset",this);
        b_reset->setMaximumWidth(toolWidth);
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

        l_outils->addWidget(b_reset);
        l_outils->addWidget(s_size);
        l_outils->addLayout(l_color);

        l_outilsEcran->addLayout(l_outils);
        l_outilsEcran->addWidget(opengl);

        connect(s_colorSlider,&QSlider::sliderMoved,colorPick,&ColorPick::setH);
        connect(b_reset,&QPushButton::pressed,opengl,&OpenGl::resetCanvas);
        connect(s_size,&QSlider::sliderMoved,opengl,&OpenGl::setSizeParth);
        connect(s_size,&QSlider::sliderReleased,opengl,&OpenGl::triggerInitPath);

}

void Window::resizeEvent(QResizeEvent *event)
{
//    qInfo() << "resized" << this->geometry().size();
    opengl->setMinimumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
    opengl->setMaximumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
}

void Window::closeEvent (QCloseEvent *event)
{
    opengl->freePath();
}
