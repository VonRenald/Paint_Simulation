#ifndef WINDOW_H
#define WINDOW_H

#include "glwindow2.h"

#include <QWidget>
#include <QPushButton>

class Window : public QWidget
{
public:
    Window();

private:
    QPushButton *bout;
    GlWindow2 *opengl;
};

#endif // WINDOW_H
