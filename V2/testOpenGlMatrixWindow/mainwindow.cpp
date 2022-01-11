#include "mainwindow.h"
#include <QDebug>
//qInfo() << "penSize";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    this->setMinimumSize(800,800);
    qInfo() << this->geometry().size();
//    opengl = new QOpenGLWidget(this);
    //opengl->setMinimumSize(this->geometry().size());

//    QPushButton *b1 = new QPushButton("1",this);
//    QPushButton *b2 = new QPushButton("2",this);

//    QHBoxLayout *layout = new QHBoxLayout;

//    layout->addWidget(b1);
//    layout->addWidget(b2);

//    this->setLayout(layout);

}

MainWindow::~MainWindow()
{
}


