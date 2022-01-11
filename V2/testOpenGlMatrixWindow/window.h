#ifndef WINDOW_H
#define WINDOW_H

#include "opengl.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class Window : public QWidget
{
public:
    Window();
private:

    void resizeEvent(QResizeEvent *event);

    int toolWidth;

    QPushButton *b1;
    QPushButton *b2;

    QHBoxLayout *l_outilsEcran;
    QVBoxLayout *l_outils;

    QOpenGLWidget *opengl;
};

#endif // WINDOW_H
