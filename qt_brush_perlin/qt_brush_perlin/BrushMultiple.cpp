#include "BrushMultiple.h"
#include <QDebug>
BrushMultiple::BrushMultiple(int width)
{
	srand(time(NULL));
	m_width = width;
	tab = (float*)malloc(sizeof(float) * width * width);
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tab[linear(x, y, width)] = 0;
		}
	}
	int nb = rand()%4 + 2;
	int maxRayon = width / 3.0f - 1;
	int minRayon = width / 4.0f;
	int pi = -width, pj = -width,i,j;
	if (minRayon == 0)
	{
		tab[linear(0, 0, width)] = 1;
	}
	else
	for (int e = 0; e < nb; e++)
	{
		int r = (maxRayon == minRayon) ?
			rand() % (minRayon)+minRayon :
			rand() % (maxRayon - minRayon) + minRayon;


		Brush brush = Brush(r);

		int rayon = brush.getRayon();
		int diametre = 2 * rayon + 1;
		
		i = rand() % (width - diametre);
		j = rand() % (width - diametre);
		while (distE(QPoint(i, j), QPoint(pi, pj)) < width / 5)
		{
			i = rand() % (width - diametre);
			j = rand() % (width - diametre);
		}
		pi = i;
		pj = i;
		for (int y = 0; y < diametre; y++)
		{
			for (int x = 0; x < diametre; x++)
			{
				//qDebug() << x+i << y+i;
				float valTab = tab[linear(x + i, y + j, width)];
				float valBrush = brush.getValue(x, y);
				float toset = (valTab + valBrush > 1) ? 1 : valTab + valBrush;//(valTab > valBrush) ? valTab : valBrush;
				
				tab[linear(x + i, y + j, width)] = toset;
			}
		}

	}

	
}
BrushMultiple::~BrushMultiple()
{
	free(tab);
}
float BrushMultiple::getValue(int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_width)
		return -1;
	return tab[linear(x, y, m_width)];
}
float* BrushMultiple::getBrush()
{
	return tab;
}
int BrushMultiple::getWidth()
{
	return m_width;
}
int BrushMultiple::linear(int x, int y, int z)
{
	return x + y * z;
}
float BrushMultiple::distE(QPoint p1, QPoint p2)
{
	return sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y()));
}
