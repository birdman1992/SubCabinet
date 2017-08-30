#-------------------------------------------------
#
# Project created by QtCreator 2017-08-30T13:50:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCabinet
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    controldevice.cpp \
    Qextserial/qextserialport.cpp \
    Qextserial/qextserialport_unix.cpp \
    Hid/qhid.cpp \
    Hid/hid.c \
    devicesimulate.cpp

HEADERS  += mainwidget.h \
    controldevice.h \
    Qextserial/qextserialport.h \
    Qextserial/qextserialport_p.h \
    Qextserial/qextserialport_global.h \
    Hid/qhid.h \
    Hid/hid.h \
    devicesimulate.h

FORMS    += mainwidget.ui \
    devicesimulate.ui

DISTFILES += \
    Qextserial/LICENSE

RESOURCES += \
    img.qrc
