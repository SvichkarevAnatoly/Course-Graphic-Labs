#-------------------------------------------------
#
# Project created by QtCreator 2014-04-02T16:15:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageViewer
TEMPLATE = app


SOURCES += main.cpp\
    canvas/canvas.cpp \
    view-controller/mainwindow.cpp \
    view-controller/sizecontroller.cpp \
    view-controller/doubleslider.cpp \
    view-controller/drawpanel.cpp \
    texture/square.cpp \
    texture/filter/bilinear.cpp \
    texture/filter/filter.cpp \
    texture/filter/mipmapper.cpp\
    texture/triangle.cpp\
    texture/texture.cpp\
    texture/edge.cpp\
    texture/texturedpoint.cpp\

HEADERS  += view-controller/mainwindow.h\
        texture/triangle.h\
        texture/edge.h\
        texture/texturedpoint.h\
        texture/texture.h\
        texture/filter/filter.h\
        texture/filter/bilinear.h\
        texture/filter/mipmapper.h\
        texture/square.h\
        canvas/canvas.h\
        view-controller/drawpanel.h\
        view-controller/sizecontroller.h\
        view-controller/doubleslider.h \
