#include "fenetre.h"
#include "glwidget.h"
#include "helper.h"

#include <QTimer>

Fenetre::Fenetre()
{
    setWindowTitle(tr("Test Dessin"));
    GLWidget *openGl = new GLWidget(&helper,this);
    helper.parent = openGl;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, openGl, &GLWidget::draw);
    timer->start(50);
}
