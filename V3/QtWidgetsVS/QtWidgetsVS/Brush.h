#pragma once
#include <stdlib.h>
#include <QObject>
#include <QSize>
#include <QPoint>

#include "BrushMultiple.h"

class Brush : public QObject
{

public:
	Brush();
	~Brush();
	float* get_brush();
	void initBrushCercle(int rayon);
	void initBrushDecCercle(int rayon);
	void initBrushPaint(int width,int nbTache,float normalForce,int seed);
	void BrushDecCercle(int rayon, float* tab);
	QSize get_Size();
	void testPerlin();
	void initMultyBrush(int rayon);
private:
	
	float distE(QPoint p1, QPoint p2);

	QSize m_size;
	float* tab_brush = nullptr ;
	bool tab_brush_set = false;
};

