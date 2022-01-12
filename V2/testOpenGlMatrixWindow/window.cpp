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

        b1 = new QPushButton("1",this);
        b1->setMaximumWidth(toolWidth);
        b2 = new QPushButton("2",this);
        b2->setMaximumWidth(toolWidth);

        l_outilsEcran = new QHBoxLayout(this);
        l_outils = new QVBoxLayout(this);
        l_color = new QVBoxLayout(this);

        s_colorSlider = new QSlider(Qt::Horizontal,this);
        s_colorSlider->setRange(0,359);
        s_colorSlider->setMaximumWidth(toolWidth);

        l_color->addWidget(s_colorSlider);
        l_color->addWidget(colorPick);
        l_color->addWidget(colorDisplay);

        l_outils->addWidget(b1);
        l_outils->addWidget(b2);
        l_outils->addLayout(l_color);

        l_outilsEcran->addLayout(l_outils);
        l_outilsEcran->addWidget(opengl);

        connect(s_colorSlider,&QSlider::sliderMoved,colorPick,&ColorPick::setH);

//        this->setLayout(layout);
}

void Window::resizeEvent(QResizeEvent *event)
{
//    qInfo() << "resized" << this->geometry().size();
    opengl->setMinimumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
    opengl->setMaximumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
}
