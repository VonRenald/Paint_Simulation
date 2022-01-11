#include "window.h"
#include <QDebug>
Window::Window()
{



        this->setMinimumSize(380,300);
//        qInfo() << this->geometry().size();
        opengl = new OpenGl();

        toolWidth = 75;

        b1 = new QPushButton("1",this);
        b1->setMaximumWidth(toolWidth);
        b2 = new QPushButton("2",this);
        b2->setMaximumWidth(toolWidth);

        l_outilsEcran = new QHBoxLayout(this);
        l_outils = new QVBoxLayout(this);


        l_outils->addWidget(b1);
        l_outils->addWidget(b2);

        l_outilsEcran->addLayout(l_outils);
        l_outilsEcran->addWidget(opengl);

//        this->setLayout(layout);
}

void Window::resizeEvent(QResizeEvent *event)
{
//    qInfo() << "resized" << this->geometry().size();
    opengl->setMinimumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
    opengl->setMaximumSize(this->geometry().size().width()-toolWidth - 50,this->geometry().size().height()-20);
}
