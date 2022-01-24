#include "qtwidgetsvs.h"




QtWidgetsVS::QtWidgetsVS(QWidget *parent) : QWidget(parent)
{

    //QMenu* Fichier = menuBar()->addMenu("&Fichier");


    

    tool = new QWidget(this);
    notTool = new QWidget(this);

    canvas = new OpenGl(tool);
    
    s_sizeBruch = new QSlider(Qt::Horizontal, tool);
    s_sizeBruch->setRange(0, 25);
    w_brush_display = new BrushDisplay(tool);
    canvas->setBrush(w_brush_display->getBrush());


    mainLeyer = new QHBoxLayout(this);

    int toolSize = 75;
    tool->setMaximumWidth(toolSize+20);

    l_tools = new QVBoxLayout(tool);

    l_brushType = new QHBoxLayout(tool);
    b0 = new QPushButton("0", tool);
    b1 = new QPushButton("1", tool);
    b2 = new QPushButton("2", tool);
    l_brushType->addWidget(b0);
    l_brushType->addWidget(b1);
    l_brushType->addWidget(b2);

    l_Brush = new QVBoxLayout(tool);
    l_Brush->addLayout(l_brushType);
    l_Brush->addWidget(s_sizeBruch);
    l_Brush->addWidget(w_brush_display);

    l_Color = new QVBoxLayout(tool);
    colorDisplay = new ColorDisplay(tool);
    colorPick = new ColorPick(colorDisplay, canvas, tool);
    s_color = new QSlider(Qt::Horizontal, tool);
    colorPick->setFixedSize(toolSize, toolSize);
    colorPick->setMinimumSize(toolSize, toolSize);
    colorDisplay->setFixedSize(toolSize / 2, toolSize / 2);
    colorDisplay->setMinimumSize(toolSize / 2, toolSize / 2);
    l_Color->addWidget(s_color);
    l_Color->addWidget(colorPick);
    l_Color->addWidget(colorDisplay);

    //l_tools->addWidget(colorPick);
    //l_tools->addWidget(colorDisplay);

    l_tools->addLayout(l_Color);
    l_tools->addLayout(l_Brush);
    //l_tools->addLayout(l_brushType);
    //l_tools->addWidget(s_sizeBruch);
    //l_tools->addWidget(w_brush_display);
    w_brush_display->setFixedSize(toolSize, toolSize);
    //qDebug() <<"w_brush_display size"<< w_brush_display->size();

    


    l_canvas = new QHBoxLayout(notTool);
    l_canvas->addWidget(canvas);
    

    mainLeyer->addWidget(tool);
    mainLeyer->addWidget(notTool);

    connect(s_sizeBruch, &QSlider::valueChanged, w_brush_display, &BrushDisplay::changeSize);
    connect(b0, &QPushButton::pressed, w_brush_display, &BrushDisplay::setCercle);
    connect(b1, &QPushButton::pressed, w_brush_display, &BrushDisplay::setDecCercle);
    connect(b2, &QPushButton::pressed, w_brush_display, &BrushDisplay::setPaint);

    connect(s_color, &QSlider::sliderMoved, colorPick, &ColorPick::setH);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, canvas, &OpenGl::updTimer);
    timer->start(50);

    //o_brush = new Brush();
    //o_brush->initBrushCercle(5);
    //w_brush_display = new BrushDisplay(this);
    //w_brush_display->setMinimumSize(this->size());
    //w_brush_display->setBrush(o_brush->get_brush(), 11, 11);
    

}

void QtWidgetsVS::resizeEvent(QResizeEvent* event)
{

    openGlResize();
    //canvas->resizeWigdet(notTool->size());
}

void QtWidgetsVS::openGlResize()
{
    float r = canvas->getRationXpY();
    int x, y;
    float wx = notTool->geometry().size().width();
    float wy = notTool->geometry().size().height();
    QSize can = canvas->getCanvasSize();
    if (wx / can.width() < wy / can.height())
    {
        x = wx;
        y = x / r;
    }
    else
    {
        y = wy;
        x = y * r;
    }

    canvas->setFixedSize(x, y);
}

void QtWidgetsVS::newCanvas(int w, int h)
{
    canvas->NewTexture(w, h);
    openGlResize();
}
void QtWidgetsVS::saveTexture()
{
    canvas->saveTexture();
}
