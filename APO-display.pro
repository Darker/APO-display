#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T18:33:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = APO-display
TEMPLATE = app
CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _QT_COMPILE
QMAKE_CXXFLAGS += -Wunused-parameter

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
       Color.cpp \
    Game.cpp \
    Shape.cpp \
    ShapeRendering.cpp \
    Pentagram.cpp \
    display_magic.cpp \
    DisplayRenderer.cpp \
    mainLinux.cpp \
    qt_stuff/mainQt.cpp \
    qt_stuff/MainWindow.cpp \
    qt_stuff/PaintWidget.cpp \
    qt_stuff/Plotter.cpp \
    Circle.cpp \
    Base.cpp

HEADERS += \
    Color.h \
    Game.h \
    Shape.h \
    defines.h \
    Pentagram.h \
    ShapeRendering.h \
    display_magic.h \
    DisplayRenderer.h \
    mainFunctions.h \
    qt_stuff/MainWindow.h \
    qt_stuff/PaintWidget.h \
    qt_stuff/Plotter.h \
    qt_stuff/QtVirtualDisplay.h \
    Circle.h \
    Base.h

FORMS += qt_stuff/MainWindow.ui
