#-------------------------------------------------
#
# Project created by QtCreator 2018-04-02T15:37:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gui_tbp
TEMPLATE    = app
DEFINES     += QT_DEPRECATED_WARNINGS

SOURCES +=  src/main.cpp\
            src/mainwindow.cpp\
            src/RangeWidget.cpp\
            libtbp/src/segment.cpp\
            libtbp/src/base.cpp

HEADERS += include/mainwindow.h\
           include/RangeWidget.h\
           libtbp/inculde/segment.hpp\
           libtbp/include/base.hpp

FORMS   += forms/mainwindow.ui


INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
