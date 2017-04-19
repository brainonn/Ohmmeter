#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T19:49:07
#
#-------------------------------------------------

QT       += core gui serialport
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Ohmmeter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deviceform.cpp \
    qcustomplot.cpp \
    ohmmeter.cpp \
    kineticsdata.cpp \
    timerhandler.cpp

HEADERS  += mainwindow.h \
    deviceform.h \
    qcustomplot.h \
    ohmmeter.h \
    kineticsdata.h \
    timerhandler.h

FORMS    += mainwindow.ui \
    deviceform.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
