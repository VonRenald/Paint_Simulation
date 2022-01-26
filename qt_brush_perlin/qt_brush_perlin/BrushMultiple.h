#pragma once
#include <stdlib.h> 
#include <time.h>
#include "Brush.h"
#include <stdlib.h> 
class BrushMultiple
{
public:
	BrushMultiple(int width);
	~BrushMultiple();
	float getValue(int x, int y);
	float* getBrush();
	int getWidth();
private:
	float distE(QPoint p1, QPoint p2);
	int linear(int x, int y, int z);
	int m_width;
	float* tab = nullptr;
};

