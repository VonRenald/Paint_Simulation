#ifndef WINDOW_H
#define WINDOW_H

#include "opengl.h"
#include "colorpick.h"
#include "colordisplay.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>

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

    OpenGl *opengl;

    ColorDisplay *colorDisplay;
    ColorPick * colorPick;
    QSlider *s_colorSlider;
    QVBoxLayout *l_color;
};

#endif // WINDOW_H
