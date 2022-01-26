#include "PerlinDS.h"
#include <math.h> 
#include <cmath>
#include "qdebug.h"

PerlinDS::PerlinDS(int width,int max,int seed)
{
	if (seed == -1)
	{
		srand(time(NULL));
	}
	else
	{
		srand(seed);
	}
	m_width = width;
	tab = (int*)malloc(sizeof(int) * width * width);

	tab[0] = rand() % max;//0;
	tab[linear(0, width - 1, width)] = rand() % max; //0;
	tab[linear(width - 1, width - 1, width)] = rand() % max; //0;
	tab[width - 1] = rand() % max; //0;
	int i = width - 1;
	while (i > 1)
	{
		int id = floor(i / 2.0f);
		for (int x = id; x < width; x += i)
		{
			for (int y = id; y < width; y += i)
			{
				int SW = 0;
				int NW = 0;
				int NE = 0;
				int SE = 0;
				if (x - id >= 0 && x - id < width) {
					if (y - id >= 0 && y - id < width) { SW = tab[linear(x-id,y-id,width)]; }
					if (y + id >= 0 && y + id < width) { NW = tab[linear(x-id,y+id,width)]; }
				}
				if (x + id >= 0 && x + id < width) {
					if (y - id >= 0 && y - id < width) { SE = tab[linear(x+id,y-id,width)]; }
					if (y + id >= 0 && y + id < width) { NE = tab[linear(x+id,y+id,width)]; }
				}

				//qDebug() << i << id;
				int moyenne = floor((SW + NW + NE + SE) / 4.0f);
				int sol = std::abs(moyenne + ((rand() % (2 * id)) - id));
				if (sol > max) { sol = max - 1; }
				tab[linear(x,y,width)] = sol;
			}
		}
		int decalage = 0;
		for (int x = 0; x < width; x += id) {
			decalage = (decalage == 0) ? id: 0;
			for (int y = decalage; y < width; y += i) {
				int somme = 0;
				int n = 0;
				if (x >= id) {
					somme += tab[linear(x - id, y, width)];
					n += 1;
				}
				if (x + id < width) {
					somme += tab[linear(x + id, y, width)];
					n += 1;
				}
				if (y >= id) {
					somme += tab[linear(x, y - id, width)];
					n += 1;
				}
				if (y + id < width) {
					somme += tab[linear(x, y + id, width)];
					n += 1;
				}
				int sol = std::abs(floor(somme / ((float)n)) + ((rand() % (2 * id)) - id));
				if (sol > max) { sol = max - 1; }
				if (x == 0 || y == 0 || x == width - 1 || y == width - 1) {
					tab[linear(x, y, width)] = sol;
				}
				else {
					tab[linear(x, y, width)] = sol;
				}
			}
		}
		i = id;
	}

	//QDebug deb = qDebug();
	//deb << "tab :\n";
	//for (int y = 0; y < width; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		deb << tab[linear(x, y, width)];
	//	}
	//	deb << "\n";
	//}
}
PerlinDS::~PerlinDS()
{
	free(tab);
}
int PerlinDS::linear(int x, int y, int w)
{
	return (x + y * w);
}
int PerlinDS::getValue(int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_width)
	{
		return -1;
	}
	return tab[linear(x, y, m_width)];
}
