#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
    this->setFixedSize(500,500);
    scene1 = new Scene(this);
    scene1->setFixedSize(this->size());

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene1, &Scene::extUpdate);
    timer->start(0);

//    QTimer *timer2 = new QTimer(this);
//    connect(timer2, &QTimer::timeout, scene1, &Scene::extUpdate);
//    timer2->start(0);

//    QTimer *timer3 = new QTimer(this);
//    connect(timer3, &QTimer::timeout, scene1, &Scene::extUpdate);
//    timer3->start(0);

//    QTimer *timer4 = new QTimer(this);
//    connect(timer4, &QTimer::timeout, scene1, &Scene::extUpdate);
//    timer4->start(0);

//    QTimer *timer5 = new QTimer(this);
//    connect(timer5, &QTimer::timeout, scene1, &Scene::extUpdate);
//    timer5->start(0);


}

MainWindow::~MainWindow()
{
//    delete ui;
    //widget = new QtWidgets(this);

//    mainWidget = new QWidget(this);
    delete scene1;
}

