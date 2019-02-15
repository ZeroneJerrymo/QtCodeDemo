#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T16:24:40
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatBubble
TEMPLATE = app

HEADERS += \
    chatbubble.h \
    chatwindow.h \
    myapp.h

SOURCES += \
    main.cpp \
    chatbubble.cpp \
    chatwindow.cpp \
    myapp.cpp

RESOURCES += \
    images.qrc

DESTDIR         = $$PWD/bin
MOC_DIR         = $$PWD/build
OBJECTS_DIR     = $$PWD/build
UI_DIR          = $$PWD/build
RCC_DIR         = $$PWD/build

FORMS += \
    chatwindow.ui

RC_FILE         += app.rc
