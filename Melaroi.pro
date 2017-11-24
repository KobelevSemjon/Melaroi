#-------------------------------------------------
#
# Project created by QtCreator 2017-11-01T15:24:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Melaroi
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    imageview.cpp\
    smatrix.cpp \
    simagestatistics.cpp\
    slinearalgebra.cpp\
    sfunctors.cpp \
    sprocessing.cpp \
    ssegmentationmap.cpp

HEADERS  += widget.h \
    content.h \
    imageview.h \
    smatrix.h \
    simagestatistics.h\
    slinearalgebra.h\
    sfunctors.h \
    sprocessing.h \
    ssegmentationmap.h

FORMS    += widget.ui
