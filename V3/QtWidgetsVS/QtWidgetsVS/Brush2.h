#pragma once
#include <stdlib.h> 
#include <QPoint>
class Brush2
{
public:
    Brush2(int rayon);
    ~Brush2();
    float getValue(int x,int y);
    float* getBrush();
    int getRayon();
    void freeTab();
private:
    float f(float x);
    void BrushDecCercle(int rayon, float* tab);
    float distE(QPoint p1, QPoint p2);
    int linear(int x, int y, int z);
    float* brush = nullptr;
    int m_rayon;
};

