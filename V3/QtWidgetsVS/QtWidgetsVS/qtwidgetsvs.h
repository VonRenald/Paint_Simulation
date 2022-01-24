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

#include <QTimer>

#include "OpenGl.h"
#include "BrushDisplay.h"
#include "Brush.h"
#include "ColorDispaly.h"
#include "ColorPick.h"


class QtWidgetsVS : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsVS(QWidget* parent = Q_NULLPTR);
    void newCanvas(int w, int h);
    void saveTexture();
protected:
    void resizeEvent(QResizeEvent* event);
private:

    void openGlResize();

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

    QVBoxLayout* l_Brush = nullptr;
    QSlider* s_sizeBruch = nullptr;
    BrushDisplay* w_brush_display = nullptr;

    QVBoxLayout* l_Color;
    ColorDisplay* colorDisplay = nullptr;
    ColorPick* colorPick = nullptr;
    QSlider* s_color = nullptr;
};
