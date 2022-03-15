#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
    this->setFixedSize(500,500);
//    scene1 = new Scene(this);
//    scene1->setFixedSize(this->size());



//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, scene1, &Scene::extUpdate);
//    timer->start(20);

    w2 = new CanvasBrush(this);
    w2 -> setFixedSize(this->size());

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, w2, &CanvasBrush::updtExt);
    timer->start(3000);

}

MainWindow::~MainWindow()
{
//    delete ui;
    //widget = new QtWidgets(this);

//    mainWidget = new QWidget(this);
    delete scene1;
}

