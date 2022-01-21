#pragma once
#include <QPushButton>
#include <QtWidgets/QWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "OpenGl.h"


class QtWidgetsVS : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsVS();
protected:
    void resizeEvent(QResizeEvent* event);
private:
    OpenGl *canvas;
    QPushButton *b1;
    QHBoxLayout* mainLeyer;
    QHBoxLayout* l_canvas;

    QWidget* tool;
    QWidget* notTool;
};
