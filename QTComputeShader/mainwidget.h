#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include "openglwidget.h"
#include "openglv2.h"
class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();
private:
    //OpenGlV2 * canvas;
    OpenGlWidget *canvas;
};
#endif // MAINWIDGET_H
