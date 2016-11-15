#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T23:14:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    edge.cpp \
    node.cpp \
    floydwarshall.cpp

HEADERS  += mainwindow.h \
    graph.h \
    node.h \
    edge.h \
    floydwarshall.h

FORMS    += mainwindow.ui \
    floydwarshall.ui
    std=c++11
