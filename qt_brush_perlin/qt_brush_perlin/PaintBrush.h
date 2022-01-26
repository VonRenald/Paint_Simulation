#pragma once
#include "Brush.h"
#include "PerlinDS.h"

#include <stdlib.h> 
class PaintBrush
{
public:
	PaintBrush(int rayon);
	~PaintBrush();
	float getValue(int x, int y);
	float* getBrush();
	int getRayon();
private:
	int linear(int x, int y, int width);

	float* tab = nullptr;
	int m_rayon = 0;
	int m_diametre = 0;
};

