QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brush.cpp \
    brushmultiple.cpp \
    canvasbrush.cpp \
    fbo.cpp \
    main.cpp \
    mainwindow.cpp \
    paintbrush.cpp \
    perlinds.cpp \
    plan.cpp \
    scene.cpp \
    scene_2.cpp

HEADERS += \
    brush.h \
    brushmultiple.h \
    canvasbrush.h \
    fbo.h \
    mainwindow.h \
    paintbrush.h \
    perlinds.h \
    plan.h \
    scene.h \
    scene_2.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
