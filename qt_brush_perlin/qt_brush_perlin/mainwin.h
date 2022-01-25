#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwin.h"
#include "Canvas.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWinClass ui;
};
