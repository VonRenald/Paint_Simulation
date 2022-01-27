#include "PaintBrush.h"
#include "QDebug"
PaintBrush::PaintBrush(int rayon)
{
	m_rayon = rayon;
	m_diametre = 2 * rayon + 1;
	int p = 0;
	while (2 << p < m_diametre)
	{
		p++;
	}
	p = (2 << p)+1;
	PerlinDS perlin = PerlinDS(p, (p/2)+1);
	qDebug() << "perlinok";
	//Brush brush = Brush(rayon);
	BrushMultiple brush = BrushMultiple(m_diametre);
	qDebug() << "brushok";
	tab = (float*)malloc(sizeof(float) * m_diametre * m_diametre);

	for (int y = 0; y < m_diametre; y++) {
		for (int x = 0; x < m_diametre; x++)
		{
			float vp = perlin.getValueMaxNormal(x, y);
			float vb = brush.getValue(x, y);
			float val2tav = (vp * vb) ;
			//qDebug() << vp << vb << val2tav*255;
			tab[linear(x, y, m_diametre)] = val2tav;
		}
	}
}
PaintBrush::~PaintBrush()
{
	free(tab);
	free(tab_resize);
}
float PaintBrush::getValue(int x, int y)
{
	if (x < 0 || x >= m_diametre || y < 0 || y >= m_diametre)
		return -1;
	else
		return tab[linear(x, y, m_diametre)];
}
float* PaintBrush::getBrush()
{
	return tab;
}
int PaintBrush::getRayon()
{
	return m_rayon;
}
int PaintBrush::linear(int x, int y, int width)
{
	return (x + y * width);
}
void PaintBrush::init_risize_brush(int rayon)
{
	if (rayon > m_rayon)
	{
		qDebug() << "rayon trop grand";
		exit(1);
	}
	m_rayon_resize = rayon;
	int diametre = 2 * rayon + 1;
	tab_resize = (float*)malloc(sizeof(float) * diametre * diametre);
}
