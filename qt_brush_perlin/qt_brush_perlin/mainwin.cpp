#include "mainwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(500, 500);
    affichage = new QWidget(this);
    affichage->setFixedSize(this->size());
    //ui.setupUi(this);
    
    w1 = new CanvasPN(affichage);
    w2 = new CanvasPN(affichage);

    layout = new QGridLayout;
    //layoutH = new QHBoxLayout;
    layout->addWidget(w1,0,0);
    layout->addWidget(w2,0,1);

    affichage->setLayout(layout);

}
