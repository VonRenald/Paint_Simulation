#pragma once
#include <qopenglwidget.h>
#include <QOpenGLWidget>
#include <QImage>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "Brush.h"



class BrushDisplay : public QOpenGLWidget
{
public:
    BrushDisplay(QWidget* parent = nullptr);
    ~BrushDisplay();

    void setBrush(float* brush,int w, int h);
public slots:
    void changeSize(int size);
    void setCercle();
    void setDecCercle();
    void setPaint();
protected:
    virtual void paintEvent(QPaintEvent* e) override;
private:
    QImage* img = nullptr;
    QPainter painter;
    Brush myBrush;
    int brushType = 0;
    int currentSize=0;
};

