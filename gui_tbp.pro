#-------------------------------------------------
#
# Project created by QtCreator 2018-04-02T15:37:03
#
#-------------------------------------------------

QT       += core gui
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gui_tbp
TEMPLATE    = app
DEFINES     += QT_DEPRECATED_WARNINGS

SOURCES +=  src/main.cpp\
            src/mainwindow.cpp\
            src/RangeWidget.cpp\
            lib/libtbp/src/segment.cpp\
            lib/libtbp/src/base.cpp

HEADERS += include/mainwindow.h\
           include/RangeWidget.h\
           lib/libtbp/include/segment.hpp\
           lib/libtbp/include/base.hpp\

FORMS   += forms/mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs
INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include
