#pragma once
#include <QSize>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
class PerlinDS
{
public:
	PerlinDS(int width,int max,int seed = -1);// 3 5 9 17 33 65 129 257 513 
	~PerlinDS();
	int getValue(int x, int y);
private:
	int linear(int x, int y, int z);
	int* tab = nullptr;
	int m_width = 0;
};

