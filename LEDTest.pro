#-------------------------------------------------
#
# Project created by QtCreator 2015-11-20T17:04:39
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LEDTest
TEMPLATE = app

INCLUDEPATH += /usr/local/include
# Mac OS X specific settings
macx {
    #CONFIG(debug, debug|release) {
DEFINES += _MAC_BUILD_
    #}
}

message($$QMAKESPEC)
# part for building for raspberry pi
linux-rasp-pi-g++ {
    DEFINES += _LINUX_RASP_PI_
    #message(Linux)
    LIBS += -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread -lm
}

SOURCES += main.cpp\
        mainwindow.cpp \
    ledblinkerthread.cpp

HEADERS  += mainwindow.h \
    ledblinkerthread.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    Resources/styleSheet.qss \
    launcher.sh



