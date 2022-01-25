#include "mainwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
    this->setFixedSize(500,500);
    Canvas *w = new Canvas(this);
}
