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

}

MainWindow::~MainWindow()
{
//    delete ui;
    //widget = new QtWidgets(this);

//    mainWidget = new QWidget(this);
    delete scene1;
}

