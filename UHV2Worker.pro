#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T15:59:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport
CONFIG += -std=c++11
TARGET = UHV2Worker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    binaryprotocol.cpp \
    UHV2Worker/uhv2worker.cpp \
    UHV2Worker/serialportinfovalidation.cpp \
    UHV2Worker/serialportinforequest.cpp \
    UHV2Worker/uhv2workerdirectstatetransition.cpp \
    UHV2Worker/serialportconnectionestablishment.cpp \
    UHV2Worker/solitarymessagetransmission.cpp \
    UHV2Worker/interactionset.cpp

HEADERS  += mainwindow.h \
    binaryprotocol.h \
    straystuffs.h \
    anqtdebug.h \
    UHV2Worker/uhv2worker.h \
    UHV2Worker/serialportinfovalidation.h \
    UHV2Worker/serialportinforequest.h \
    UHV2Worker/uhv2workerdirectstatetransition.h \
    UHV2Worker/serialportconnectionestablishment.h \
    UHV2Worker/solitarymessagetransmission.h \
    UHV2Worker/interactionset.h

FORMS    += mainwindow.ui
