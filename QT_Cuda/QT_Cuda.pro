#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11

## You can make your code fail to compile if it uses deprecated APIs.
## In order to do so, uncomment the following line.
##DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += \
#    main.cpp \
#    mainwindow.cpp

#HEADERS += \
#    mainwindow.h

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    vectorAddition.cu
QT       += core
QT       -= gui
TARGET = TestCUDA
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
# Define output directories
DESTDIR = release
OBJECTS_DIR = release/obj
CUDA_OBJECTS_DIR = release/cuda
# Source files
SOURCES += main.cpp
# This makes the .cu files appear in your project
OTHER_FILES +=  vectorAddition.cu
# CUDA settings <-- may change depending on your system
CUDA_SOURCES += vectorAddition.cu
#CUDA_SDK = "C:/ProgramData/NVIDIA Corporation/NVIDIA GPU Computing SDK 4.2/C"   # Path to cuda SDK install
CUDA_DIR = "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.6"           # Path to cuda toolkit install
SYSTEM_NAME = win32         # Depending on your system either 'Win32', 'x64', or 'Win64'
SYSTEM_TYPE = 32            # '32' or '64', depending on your system
CUDA_ARCH = sm_11           # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
NVCC_OPTIONS = --use_fast_math
# include paths
INCLUDEPATH += $$CUDA_DIR/include
#$$CUDA_SDK/common/inc/\
#$$CUDA_SDK/../shared/inc/
# library directories
QMAKE_LIBDIR += $$CUDA_DIR/lib/$$SYSTEM_NAME
#$$CUDA_SDK/common/lib/$$SYSTEM_NAME \
#$$CUDA_SDK/../shared/lib/$$SYSTEM_NAME
# The following library conflicts with something in Cuda
QMAKE_LFLAGS_RELEASE = /NODEFAULTLIB:msvcrt.lib
QMAKE_LFLAGS_DEBUG   = /NODEFAULTLIB:msvcrtd.lib
# Add the necessary libraries
CUDA_LIBS = cuda cudart
# The following makes sure all path names (which often include spaces) are put between quotation marks
CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')
NVCC_LIBS = $$join(CUDA_LIBS,' -l','-l', '')
LIBS += $$join(CUDA_LIBS,'.lib ', '', '.lib')
# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
# Debug mode
cuda_d.input = CUDA_SOURCES
cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
cuda_d.commands = $$CUDA_DIR/bin/nvcc.exe -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda_d.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
# Release mode
cuda.input = CUDA_SOURCES
cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
cuda.commands = $$CUDA_DIR/bin/nvcc.exe $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda
}
