#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T14:28:18
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = webkit
TEMPLATE = app

DESTDIR += ../Bin

SOURCES += main.cpp\
        mainwindow.cpp \
    faceform.cpp

HEADERS  += mainwindow.h \
    faceform.h

FORMS    += mainwindow.ui \
    faceform.ui

RESOURCES += \
    images.qrc
