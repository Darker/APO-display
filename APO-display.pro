#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T18:33:14
#
#-------------------------------------------------

QT       += core gui network

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
QMAKE_CXXFLAGS += -Wno-unused-variable
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-reorder


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
    Platform.cpp \
    GameJakub.cpp \
    GameButton.cpp \
    qt_stuff/SpinnerButton.cpp \
    ShapeRenderingAntialiased.cpp \
    UDPInterface.cpp \
    ShapePixmap.cpp \
    PPMReader.cpp \
    GameInterface.cpp \
    WaitMutex.cpp \
    Rectangle.cpp \
    qt_stuff/mainQtWithLinuxRendering.cpp \
    qt_stuff/QtUDP.cpp \
    ShapeCar.cpp \
    qt_stuff/GameSignalsSlots.cpp \
    GameIntersectionTest.cpp \
    ShapeRectangleBorder.cpp \
    GameMenu.cpp \
    ShapeText.cpp \
    libs_impl.cpp \
    Future.cpp \
    ShapeMenuItem.cpp \
    CooldownCalculator.cpp

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
    Platform.h \
    GameJakub.h \
    GameButton.h \
    qt_stuff/SpinnerButton.h \
    UDPInterface.h \
    ShapePixmap.h \
    threading.h \
    libs/mingw.mutex.h \
    libs/mingw.thread.h \
    libs/stb_image.h \
    libs/stb_truetype.h \
    PPMReader.h \
    GameInterface.h \
    WaitMutex.h \
    Rectangle.h \
    qt_stuff/QtUDP.h \
    ShapeCar.h \
    qt_stuff/GameSignalsSlots.h \
    GameIntersectionTest.h \
    ShapeRectangleBorder.h \
    GameMenu.h \
    ShapeText.h \
    Future.h \
    ShapeMenuItem.h \
    CooldownCalculator.h

FORMS += qt_stuff/MainWindow.ui \
    qt_stuff/SpinnerButton.ui
