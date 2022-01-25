#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "ui_mainwin.h"
#include "CanvasPN.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWinClass ui;
    CanvasPN* w1 =nullptr;
    CanvasPN* w2 =nullptr;
    QPushButton* b0;
    QPushButton* b1;
    QPushButton* b2;
    QGridLayout* layout = nullptr;
    QHBoxLayout* layoutH;

    QWidget* affichage = nullptr;
};
