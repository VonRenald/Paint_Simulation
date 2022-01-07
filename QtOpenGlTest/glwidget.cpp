#include "glwidget.h"
#include "helper.h"

#include <QPainter>
#include <QTime>

GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QOpenGLWidget(parent), helper(helper)
{

    setFixedSize(400,440);
    setAutoFillBackground(false);

}

void GLWidget::draw()
{
    update();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    helper->paint(&painter, event);
    painter.end();
}


