#include "qtwidgetsvs.h"




QtWidgetsVS::QtWidgetsVS()
{
    
    this->setMinimumSize(375, 300);

    tool = new QWidget(this);
    notTool = new QWidget(this);

    canvas = new OpenGl(notTool);
    b1 = new QPushButton("b", tool);
    mainLeyer = new QHBoxLayout(this);

    int toolSize = 75;
    tool->setMaximumWidth(toolSize);

    l_canvas = new QHBoxLayout(notTool);
    l_canvas->addWidget(canvas);
    

    mainLeyer->addWidget(tool);
    mainLeyer->addWidget(notTool);

    /*canvas->setFixedSize(300, 300);*/
    //canvas->resize(300, 300);

}

void QtWidgetsVS::resizeEvent(QResizeEvent* event)
{
    qInfo("resized");
    canvas->resizeWigdet(notTool->size());
}
