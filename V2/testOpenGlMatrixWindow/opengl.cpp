#include "opengl.h"

OpenGl::OpenGl()
{
//    qInfo() << "open init";

    sizeCanvas[0] = 255; // x
    sizeCanvas[1] = 255; // y

    img = new QImage(sizeCanvas[0],sizeCanvas[0],QImage::Format_RGB32);

    for(int y = 0;y<sizeCanvas[1];y++)
    {
        for(int x=0;x<sizeCanvas[0];x++)
        {
            img->setPixelColor(x,y,QColor(255,255,255));
        }
    }
//    drawLine(10,20,10,10);

    isPressed = false;
    colorPen = QColor(0,0,0);
//    qInfo() << "call updt";
    update();

    sizePath = 0;
    initPathCercle(sizePath);

}

void OpenGl::paintEvent(QPaintEvent *event)
{
//    qInfo() << "paint evnt";
    painter.begin(this);

    painter.drawImage(event->rect(),*img,img->rect());


    bool stop = false;
    while (lpoints.size()>=2 && !stop)
    {
        QPoint p1 = lpoints.front();
        lpoints.pop_front();
        QPoint p2 = lpoints.front();


        if(p2.isNull())
        {
            lpoints.pop_front();
            stop = true;
        }
        else
        {
            drawLine(p1,p2);
        }
    }

    painter.end();

}

void OpenGl::mouseMoveEvent(QMouseEvent *e)
{
    if (isPressed)
    {
        int xRelative = e->pos().x() * sizeCanvas[0] / this->width();
        int yRelative = e->pos().y() * sizeCanvas[1] / this->height();
//        img->setPixelColor(xRelative,yRelative,QColor(255,255,255));

        lpoints.push_back(QPoint(xRelative,yRelative));
        update();
    }
//    qInfo() << "move" << e->pos() << xRelative;
}

void OpenGl::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isPressed = true;
        int xRelative = e->pos().x() * sizeCanvas[0] / this->width();
        int yRelative = e->pos().y() * sizeCanvas[1] / this->height();
//        img->setPixelColor(xRelative,yRelative,QColor(255,255,255));

        lpoints.push_back(QPoint(xRelative,yRelative));

        update();
    }
}

void OpenGl::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && isPressed)
    {
        isPressed = false;
        lpoints.push_back(QPoint());
    }
    update();
}

void OpenGl::drawLine(int x1, int y1, int x2, int y2)
{
        //float a = float(y2-y1)/float(x2-x1);
        float a = float(y2-y1);
        float ap = float(x2-x1);
        a = (ap==0)? 0:a/ap;
//        qInfo("a %f",a);
//        qInfo("y2 %d y1 %d (y2-y1) %d",y2,y1,(y2-y1));
//        qInfo("x2 %d x1 %d (x2-x1) %d",x2,x1,(x2-x1));
//        qInfo("(y2-y1)/(x2-x1) %f",float(y2-y1)/float(x2-x1));
        float b = y2 -(a * x2);

        for (int x = std::min(x1,x2); x <= std::max(x1,x2);x++)
        {
            int y = a*x+b;
//            qInfo() << "x" << x << "y" << y;
            drawCercle(x,y,5);
//            img->setPixelColor(x,y,colorPen);
        }

        for (int y = std::min(y1,y2); y <= std::max(y1,y2);y++)
        {
            int x = (a==0)? x1:(float(y)-b)/a;
//            qInfo() << "x" << x << "y" << y;
            drawCercle(x,y,5);
//            img->setPixelColor(x,y,colorPen);
        }

    //    y = ax+b
    //     y-b = ax
        // (y-b)/a = x

}

void OpenGl::drawLine(QPoint p1, QPoint p2)
{
    drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}

void OpenGl::setColorPen(QColor color)
{
    colorPen = color;
//    qInfo() << "color changed";
}

void OpenGl::resetCanvas()
{
    for(int y = 0;y<sizeCanvas[1];y++)
    {
        for(int x=0;x<sizeCanvas[0];x++)
        {
            img->setPixelColor(x,y,QColor(255,255,255));
        }
    }
    update();
}

void OpenGl::drawCercle(int x, int y, int r)
{

    int offset = sizePath;
    int d = sizePath *2 +1;
    for(int i=0;i<d;i++)
    {
        for(int j=0;j<d;j++)
        {
//            qInfo() << "offset" << ((x+i-offset >=0 && x+i-offset < sizeCanvas[0]) && (y+j-offset >= 0 && y+j-offset < sizeCanvas[1]));
            if(((x+i-offset >=0 && x+i-offset < sizeCanvas[0]) && (y+j-offset >= 0 && y+j-offset < sizeCanvas[1])))
            {
//                qInfo() << "ok";
                if(path[i+j*d] == 1)
                    img->setPixelColor(x+i-offset,y+j-offset,colorPen);
            }

        }
    }


}

void OpenGl::initPathCercle(int r)
{
    int d = 2*r+1;
    if(pathInit)
    {
        free(path);
        pathInit = false;
    }
    path = (int*) malloc(sizeof(int)*d*d);
    int sav[d][d];
    for(int j=0;j<d;j++)
    {
        for(int i=0;i<d;i++)
        {
            path[i+d*j] = 0;
            sav[j][i] = 0;
        }
    }

    int plus[3][3] = {  {0,1,0},
                        {1,1,1},
                        {0,1,0}};
    int croix[3][3] = { {1,1,1},
                        {1,1,1},
                        {1,1,1}};

    path[r+d*r] = 1;
    for(int rp = 0; rp<r; rp++)
    {
        for(int y=0;y<d;y++)
        {
            for(int x=0;x<d;x++)
            {
                if (path[x+d*y] == 1)
                {
                    for(int j=0;j<3;j++)
                    {
                        for(int i=0;i<3;i++)
                        {
                            if(((x+i-1 >=0 && x+i-1 < d) && (y+j-1 >= 0 && y+j-1 < d)))
                            {
                                if(rp%2==0)
                                {
                                    if(plus[j][i] == 1)
                                    {
                                        sav[y+j-1][x+i-1] = 1;
                                    }
                                }
                                else
                                {
                                    if(croix[j][i] == 1)
                                    {
                                        sav[y+j-1][x+i-1] = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int y=0;y<d;y++)
        {
            for(int x=0;x<d;x++)
            {
                path[x+d*y] = sav[y][x];
            }
        }

    }

//    for(int y=0;y<d;y++)
//    {
//        for(int x=0;x<d;x++)
//        {
//            printf("%d ",path[x+d*y]);
//        }
//        printf("\n");
//    }

}

void OpenGl::freePath()
{

    if(pathInit)
    {
        free(path);
        pathInit = false;
    }

}

void OpenGl::setSizeParth(int size)
{
    sizePath = size;
}
void OpenGl::triggerInitPath()
{
    initPathCercle(sizePath);
}

