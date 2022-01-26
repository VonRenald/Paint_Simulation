#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "ui_mainwin.h"
#include "CanvasPN.h"
#include "CanvasBrush.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = Q_NULLPTR);
protected:
    void resizeEvent(QResizeEvent* event);
private:
    Ui::MainWinClass ui;
    CanvasPN* w1 =nullptr;
    CanvasBrush* w2 =nullptr;
    
    QPushButton* b0 = nullptr;
    QPushButton* b1 = nullptr;
    QPushButton* b2 = nullptr;
    QGridLayout* layout = nullptr;
    QHBoxLayout* layoutH;

    QWidget* affichage = nullptr;
};
