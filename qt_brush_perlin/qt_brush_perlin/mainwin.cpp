#include "mainwin.h"
#include <QDebug>
MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
{
    //this->setFixedSize(500, 500);
    affichage = new QWidget(this);
    //affichage->setFixedSize(this->size());
    //ui.setupUi(this);
    
    //w1 = new CanvasPN(this);
    w2 = new CanvasBrush(this);

    ////layout = new QGridLayout;
    //layoutH = new QHBoxLayout;
    //layoutH->addWidget(w1);
    //layoutH->addWidget(w2);

    //affichage->setLayout(layoutH);

}
void MainWin::resizeEvent(QResizeEvent* event)
{
    qDebug() << "resized";
    w2->setFixedSize(event->size());
}