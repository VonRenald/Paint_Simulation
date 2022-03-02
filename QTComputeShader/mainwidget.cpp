#include "mainwidget.h"
#include "QDebug"
#include "openglengine.h"


mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(500,500);
    canvas = new OpenGlWidget(this);
//    canvas = new OpenGlV2(this);
//    canvas->init();
    canvas->setFixedSize(500, 500);

//    QTimer* timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, canvas, &OpenGlV2::updateF);
//    timer->start(10);

//    canvas->printWGC();
//    OpenGlEngine test;
//    test.printWorkGroupsCapabilities();
}

mainWidget::~mainWidget()
{
}

