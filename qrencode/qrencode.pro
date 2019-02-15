#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T18:02:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qrencode
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS HAVE_CONFIG_H

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    qrwidget.cpp \
    dialog.cpp \
    main.cpp \
    qr/bitstream.c \
    qr/mask.c \
    qr/mmask.c \
    qr/mqrspec.c \
    qr/qrencode.c \
    qr/qrinput.c \
    qr/qrspec.c \
    qr/rsecc.c \
    qr/split.c

HEADERS += \
    qr/bitstream.h \
    qr/config.h \
    qr/mask.h \
    qr/mmask.h \
    qr/mqrspec.h \
    qr/qrencode.h \
    qr/qrencode_inner.h \
    qr/qrinput.h \
    qr/qrspec.h \
    qr/rsecc.h \
    qr/split.h \
    dialog.h \
    qrwidget.h

FORMS += \
        dialog.ui

#LIBS += E:\work\4.sheep\software\qrencode\qrencode\qrencode.lib

DISTFILES += \
    qr/ReadMe.txt
