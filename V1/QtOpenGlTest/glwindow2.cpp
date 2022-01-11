#include "glwindow2.h"
#include <QDebug>
#include <QTimer>


GlWindow2::GlWindow2()
{
    qInfo() << "--START--";

    setMinimumSize(500,500);
    setAutoFillBackground(false);

    press = false;
    background = QBrush(QColor(255,255,255));
    R = 0;
    G = 0;
    B = 0;
    pen = QPen(QColor(R,G,B));
    penSize = 1;



    reset = true;


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GlWindow2::upd);
    timer->start(50);


    B_reset = new QPushButton("reset",this);
    connect(B_reset,&QPushButton::clicked,this,&GlWindow2::resetAfeterResize);

    B_blackPen = new QPushButton("black pen",this);
//    B_bluePen = new QPushButton("blue pen",this);
//    B_redPen = new QPushButton("red pen",this);
//    B_greenPen = new QPushButton("green pen",this);

    B_blackPen->move(0,50);
//    B_redPen->move(0,75);
//    B_greenPen->move(0,100);
//    B_bluePen->move(0,125);

    connect(B_blackPen,&QPushButton::clicked,this,&GlWindow2::setPenBlack);
//    connect(B_redPen,&QPushButton::clicked,this,&GlWindow2::setPenRed);
//    connect(B_greenPen,&QPushButton::clicked,this,&GlWindow2::setPenGreen);
//    connect(B_bluePen,&QPushButton::clicked,this,&GlWindow2::setPenBlue);

    S_R = new QSlider(Qt::Horizontal,this);
    S_R->setRange(0,255);
    S_R->setGeometry(1,75,72,25);
    connect(S_R,&QSlider::valueChanged,this,&GlWindow2::updPenRed);
    S_G = new QSlider(Qt::Horizontal,this);
    S_G->setRange(0,255);
    S_G->setGeometry(1,100,72,25);
    connect(S_G,&QSlider::valueChanged,this,&GlWindow2::updPenGreen);
    S_B = new QSlider(Qt::Horizontal,this);
    S_B->setRange(0,255);
    S_B->setGeometry(1,125,72,25);
    connect(S_B,&QSlider::valueChanged,this,&GlWindow2::updPenBlue);

    S_sizepen = new QSlider(Qt::Horizontal,this);
    S_sizepen->setRange(1,50);
    S_sizepen->setGeometry(1,150,72,25);


    connect(S_sizepen,&QSlider::valueChanged,this,&GlWindow2::setPenSize);
    connect(this,&QOpenGLWidget::resized,this,&GlWindow2::resetAfeterResize);
}

void GlWindow2::upd()
{
    update();
//    qInfo() << "update";
}

void GlWindow2::mouseMoveEvent(QMouseEvent *e)
{
//    qInfo() << "pos :" << e->pos().x() << e->pos().y();


    lx.push_back(e->pos().x());
    ly.push_back(e->pos().y());


}

void GlWindow2::paintEvent(QPaintEvent *event)
{
//    qInfo() << "ok";
    painter.begin(this);
    pen.setWidth(penSize);
    painter.setPen(pen);
    if (reset)
    {
        painter.fillRect(event->rect(), background);
        reset = false;

    }
//    painter.drawPoint(x,y);
//    if(press && xp != -1)
//    {
//        painter.drawLine(x,y,xp,yp);
//    }
    bool stop = false;
    while (lx.size()>=2 && !stop){
        int x1 = lx.front();
        lx.pop_front();
        int x2 = lx.front();

        int y1 = ly.front();
        ly.pop_front();
        int y2 = ly.front();

        if(x2 == -1)
        {
            lx.pop_front();
            ly.pop_front();
            stop = true;
        }else
        {
            painter.drawLine(x1,y1,x2,y2);
        }



    }

    painter.end();
}

void GlWindow2::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && !press)
        {
            press = true;
            lx.push_back(e->pos().x());
            ly.push_back(e->pos().y());

        }
}

void GlWindow2::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && press)
        {
            press = false;
            lx.push_back(-1);
            ly.push_back(-1);

        }
}

void GlWindow2::resetAfeterResize()
{
    qInfo() << "resize";
    reset = true;
    update();
}

void GlWindow2::setPenBlack()
{
    pen = QPen(QColor(0,0,0));
}

void GlWindow2::setPenRed()
{
    pen = QPen(QColor(255,0,0));
}

void GlWindow2::setPenGreen()
{
    pen = QPen(QColor(0,255,0));
}

void GlWindow2::setPenBlue()
{
    pen = QPen(QColor(0,0,255));
}

void GlWindow2::setPenSize(int size)
{
    qInfo() << "penSize";
    penSize = size;
}

void GlWindow2::updPenColor()
{
    pen = QPen(QColor(R,G,B));
}

void GlWindow2::updPenRed(int red)
{
    R = red;
    updPenColor();
}

void GlWindow2::updPenGreen(int green)
{
    G = green;
    updPenColor();
}

void GlWindow2::updPenBlue(int blue)
{
    B = blue;
    updPenColor();
}
