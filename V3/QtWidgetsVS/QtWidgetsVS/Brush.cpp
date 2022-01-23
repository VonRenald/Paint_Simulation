#include "Brush.h"
#include "PerlinNoise.h"

#include <qdebug.h>
#include <stdlib.h>
#include <math.h>

Brush::Brush()
{

}
Brush::~Brush()
{
	free(tab_brush);
    
}
void Brush::initBrushDecCercle(int rayon)
{
    int diametre = 2 * rayon + 1;
    if (tab_brush_set)
    {
        free(tab_brush);
        tab_brush_set = false;
    }
    tab_brush = (float*)malloc(sizeof(float) * diametre * diametre);
    //QDebug deb = qDebug();

    float seuil = distE(QPoint(rayon, rayon), QPoint(rayon, 0)) +0.25f ;
    //deb << "seuil :" << seuil << "\n";

    for (int j = 0; j < diametre; j++)
    {
        for (int i = 0; i < diametre; i++)
        {
            float normal = 1 - distE(QPoint(rayon, rayon), QPoint(i, j)) / seuil;
            tab_brush[i + j * diametre] = (normal<0)? 0:normal;
            //deb << tab_brush[i + j * diametre];
        }
        //deb << "\n";
    }
    if (rayon == 0)
    {
        tab_brush[0] = 1.0f;
    }
    m_size = QSize(diametre, diametre);
    tab_brush_set = true;
}

void Brush::BrushDecCercle(int rayon, float* tab)
{
    int diametre = 2 * rayon + 1;
    float seuil = distE(QPoint(rayon, rayon), QPoint(rayon, 0)) + 0.25f;

    for (int j = 0; j < diametre; j++)
    {
        for (int i = 0; i < diametre; i++)
        {
            float normal = 1 - distE(QPoint(rayon, rayon), QPoint(i, j)) / seuil;
            tab[i + j * diametre] = (normal < 0) ? 0 : normal;
        }

    }
    if (rayon == 0)
    {
        tab[0] = 1.0f;
    }
}

void Brush::initBrushPaint(int rayon, int nbTache, float normalForce, int seed)
{   
    
    //QDebug deb = qDebug();
    //deb << "\n" << "--------start--------\n";
    int diametre = rayon * 2 + 1;
    if (tab_brush_set)
    {
        free(tab_brush);
        tab_brush_set = false;
    }
    //deb << "malloc\n";
    tab_brush = (float*)malloc(sizeof(float) * diametre * diametre);
    tab_brush_set = true;
    //deb << "init tab\n";
    for (int j = 0; j < diametre; j++)
    {
        for (int i = 0; i < diametre; i++)
        {
            tab_brush[i + j * diametre] = 0;
        }
    }
    float* tache = nullptr;

    //deb << "boucle tache\n";
    for (int e = 0; e < nbTache; e++)
    {
        //deb << "rand + init tach nb" << e << "\n";
        int dt = (2 * rayon) / 3;
        if (dt == 0)
            dt = 1;
        int ut = rayon / 3;
        int r_tache = (rand() % dt) + ut;
        if (r_tache < 0)
            r_tache = 0;
        int d_tache = r_tache + r_tache + 1;
        tache = (float*)malloc(sizeof(float) * d_tache * d_tache);

        //deb << "BrushDecCercle\n";
        BrushDecCercle(r_tache, tache);
        for (int j = 0; j < 2 * r_tache + 1; j++)
        {
            for (int i = 0; i < 2 * r_tache + 1; i++)
            {
                
                int tp = (tache[i + j * (2 * r_tache + 1)] > 0) ? 1 : 0;
                //deb << tp;
            }
            //deb << "\n";
        }

        //deb << "boucle tache\n";
        //deb << "(rayon - 2 * r_tache) - r_tache" << (rayon - 2 * r_tache) + r_tache << "\n";
        int offset = diametre - d_tache;
        if (offset == 0)
            offset = 1;
        int p1 = ((rand() % offset));
        int p2 = ((rand() % offset));
        QPoint p_tache = QPoint(p1, p2);
        //deb << "point tache" << p_tache << "\n";
        float normal = ((rand() % 70) + 30) / 100.0f;
        for (int j = 0; j < d_tache; j++)
        {
            for (int i = 0; i < d_tache; i++)
            {
                int x = i + p_tache.x();
                int y = j + p_tache.y();
                
                tab_brush[x + y * diametre] += tache[i + j * d_tache] * normal;
                if (tab_brush[i + j * diametre] > 1)
                    tab_brush[i + j * diametre] = 1;
                if (tab_brush[i + j * diametre] < 0)
                    tab_brush[i + j * diametre] = 0;
            }
        }
        
        free(tache);
    }
    int w = diametre, h = diametre;
    PerlinNoise perlin(rand());
    float maxi = 0.0f;
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            double y = (double)j / ((double)h);
            double x = (double)i / ((double)w);
            tab_brush[i + j * w] = tab_brush[i + j * w] * perlin.noise(x, y, 2048);
            maxi = (tab_brush[i + j * w] > maxi) ? tab_brush[i + j * w] : maxi;
        }
    }
    //normalize
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            if (tab_brush[i + j * w] > 0.25)
                tab_brush[i + j * w] = (tab_brush[i + j * w]-0.25) / (maxi-0.25);
            else
                tab_brush[i + j * w] = 0;
        }
    }

    //deb << "fin\n";
    m_size = QSize(diametre, diametre);

}

float Brush::distE(QPoint p1, QPoint p2)
{

    return sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y()));
}
void Brush::initBrushCercle(int rayon)
{
    int diametre = 2 * rayon + 1;
    if (tab_brush_set)
    {
        free(tab_brush);
        tab_brush_set = false;
    }
    tab_brush = (float*)malloc(sizeof(float) * diametre * diametre);
    //QDebug deb = qDebug();

    float seuil = distE(QPoint(rayon, rayon), QPoint(rayon, 0)) + 0.25f;
    //deb << "seuil :" << seuil <<"\n";
    for (int j = 0; j < diametre; j++)
    {
        for (int i = 0; i < diametre; i++)
        {
            
            tab_brush[i + j * diametre] = (distE(QPoint(rayon, rayon), QPoint(i, j)) <= seuil) ? 1 : 0;
            //deb << tab_brush[i + j * diametre];
        }
        //deb << "\n";
    }
    
    m_size = QSize(diametre, diametre);
    tab_brush_set = true;
}
float* Brush::get_brush()
{
    return tab_brush;
}
QSize Brush::get_Size()
{
    return m_size;
}
void Brush::testPerlin()
{
    PerlinNoise perlin(rand());
    if (tab_brush_set)
    {
        free(tab_brush);
        tab_brush_set = false;
    }
    int w = 512, h = 512;
    tab_brush = (float*)malloc(sizeof(float) * w * h);
    tab_brush_set = true;
    
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            double y = (double)j / ((double)h);
            double x = (double)i / ((double)w);
            tab_brush[i + j * w] = perlin.noise(x, y, 2048);
        }
    }
    m_size = QSize(w, h);
    tab_brush_set = true;
}
