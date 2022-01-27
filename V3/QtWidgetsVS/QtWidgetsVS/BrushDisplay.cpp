#include "BrushDisplay.h"
#include <qdebug.h>

BrushDisplay::BrushDisplay(QWidget *parent) : QOpenGLWidget(parent)
{
	changeSize(0);

}


BrushDisplay::~BrushDisplay()
{
}

void BrushDisplay::setBrush(float* brush, int w, int h)
{
	//qInfo("brush set------------------------------------------------------------");
	//QDebug deb = qDebug();
	//deb << "BrushDisplay\n";
	img = new QImage(w, h, QImage::Format_RGB32);
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			float p = brush[i + j * w];
			
			img->setPixelColor(i, j, QColor((int) 255 * p, (int)255 * p, (int)255 * p));
			//deb << img->pixelColor(i,j).red()/255;
		}
		//deb << "\n";
	}

	update();
	//qInfo("brush set---------");
}
Brush* BrushDisplay::getBrush()
{
	return &myBrush;
	//return nullptr;
}

void BrushDisplay::paintEvent(QPaintEvent* event)
{
	painter.begin(this);
	painter.drawImage(this->rect(), *img, img->rect());
	painter.end();

}
void BrushDisplay::setCercle()
{
	brushType = 0;
	changeSize(currentSize);
}
void BrushDisplay::setDecCercle()
{
	brushType = 1;
	changeSize(currentSize);
}
void BrushDisplay::setPaint()
{
	brushType = 2;
	changeSize(currentSize);
}
void BrushDisplay::changeSize(int size)
{
	currentSize = size;
	switch (brushType)
	{
	case 0:
		myBrush.initBrushCercle(size);
		break;
	case 1:
		myBrush.initBrushDecCercle(size);
		break;
	case 2:
		//myBrush.initBrushPaint(size, (rand() % 6 + 1), 0, 0);
		myBrush.initMultyBrush(size);
		break;
	}
	//
	//
	
	//myBrush.testPerlin();
	setBrush(myBrush.get_brush(), myBrush.get_Size().width(), myBrush.get_Size().height());
}