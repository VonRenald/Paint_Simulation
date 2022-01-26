#pragma once
#include <stdlib.h> 
#include <QPoint>
class Brush
{
public:
    Brush(int rayon);
    ~Brush();
    float getValue(int x,int y);
    float* getBrush();
    int getRayon();
private:
    float f(float x);
    void BrushDecCercle(int rayon, float* tab);
    float distE(QPoint p1, QPoint p2);
    int linear(int x, int y, int z);
    float* brush = nullptr;
    int m_rayon;
};

