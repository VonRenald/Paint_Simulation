#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opengl.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QOpenGLWidget *opengl;


};
#endif // MAINWINDOW_H
