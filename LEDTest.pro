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

macx {
    #CONFIG(debug, debug|release) {
DEFINES += _MAC_BUILD_
    #}
}

message($$QMAKESPEC)

linux-g++ {
    message(Linux)
    LIBS += -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread -lm
}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui



