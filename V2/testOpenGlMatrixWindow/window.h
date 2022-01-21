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

#include <QCloseEvent>
#include <QInputDialog>
#include <QDir>

class Window : public QWidget
{
public:
    Window();
public slots:
    void creatNewCanvas();
private:
    void resizeEvent(QResizeEvent *event);
    void closeEvent (QCloseEvent *event);

    void openGlResize();

    int toolWidth;

    QPushButton *b_reset;
    QPushButton *b_newCnavas;
    QPushButton *b_save;
    QPushButton *b2;
    QSlider *s_size;

    QHBoxLayout *l_outilsEcran;
    QVBoxLayout *l_outils;

    OpenGl *opengl;

    ColorDisplay *colorDisplay;
    ColorPick * colorPick;
    QSlider *s_colorSlider;
    QVBoxLayout *l_color;

    QWidget *test;
    QVBoxLayout *l_canvasLayout;
};

#endif // WINDOW_H
