#-------------------------------------------------
#
# Project created by QtCreator 2019-06-14T20:20:42
#
#-------------------------------------------------

QT       += core gui serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vkreadtool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        data/datahandle.cpp \
        db/dbmanager.cpp \
        main.cpp \
        sp/splisten.cpp \
        ui/base/progressring.cpp \
        ui/base/progressvertical.cpp \
        ui/channalwgt.cpp \
        ui/historywgt.cpp \
        ui/mainwindow.cpp \
        ui/realtimestatewgt.cpp \
        user/usermanager.cpp

HEADERS += \
        common/common.h \
        data/datahandle.h \
        db/dbmanager.h \
        sp/splisten.h \
        ui/base/progressring.h \
        ui/base/progressvertical.h \
        ui/channalwgt.h \
        ui/historywgt.h \
        ui/mainwindow.h \
        ui/realtimestatewgt.h \
        user/usermanager.h

FORMS += \
        ui/channalwgt.ui \
        ui/historywgt.ui \
        ui/mainwindow.ui \
        ui/realtimestatewgt.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
