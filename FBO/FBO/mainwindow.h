#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "scene.h"
#include "scene_2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    //void resizeEvent(QResizeEvent* event);
private:
    //Ui::MainWindow *ui;
    Scene* scene1 = nullptr;
    QWidget* mainWidget = nullptr;
};
#endif // MAINWINDOW_H