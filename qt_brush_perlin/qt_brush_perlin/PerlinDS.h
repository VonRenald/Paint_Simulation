#pragma once

#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
class PerlinDS
{
public:
	/// <summary>
	/// initialize un tableau de0int
	/// width/width de bruit de perlin par
	/// par la methode du diamant carré avec des valeur
	/// entre 0 et max 
	/// </summary>
	/// <param name="width">width = 2^^n +1</param>
	/// <param name="max">max > 0</param>
	/// <param name="seed">random si non remplie</param>
	PerlinDS(int width,int max,int seed = -1);// 3 5 9 17 33 65 129 257 513 
	~PerlinDS();
	/// <summary>
	/// retourne la valeur du tableau de perlin a
	/// la coordonnée x y
	/// </summary>
	/// <param name="x">x<=0 && x<width</param>
	/// <param name="y">y<=0 && y<width</param>
	/// <returns>0<=return<=max</returns>
	float getValue(int x, int y);
	int getValueRaw(int x, int y);
	float getValueMaxNormal(int x, int y);
private:
	int linear(int x, int y, int z);
	int* tab = nullptr;
	int m_width = 0;
	int m_max = 0;
	int m_maxValuePresent = 0;
};

