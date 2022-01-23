#pragma once
#include <QPushButton>
#include <QtWidgets/QWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>

#include "OpenGl.h"
#include "BrushDisplay.h"
#include "Brush.h"
#include "ColorDispaly.h"



class QtWidgetsVS : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsVS(QWidget* parent = Q_NULLPTR);
protected:
    void resizeEvent(QResizeEvent* event);
private:
    OpenGl *canvas;
    QPushButton* b0;
    QPushButton *b1;
    QPushButton* b2;
    QHBoxLayout* l_brushType;
    QHBoxLayout* mainLeyer;
    QHBoxLayout* l_canvas;
    QVBoxLayout* l_tools;

    QWidget* tool;
    QWidget* notTool;

    QSlider* s_sizeBruch = nullptr;
    BrushDisplay* w_brush_display = nullptr;


    ColorDisplay* test = nullptr;
};
