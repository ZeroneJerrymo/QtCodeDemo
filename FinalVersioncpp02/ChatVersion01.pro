#-------------------------------------------------
#
# Project created by QtCreator 2015-06-29T10:45:28
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatVersion01
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    clientinfo.cpp \
    ymzwidget.cpp \
    friendpart.cpp \
    readxml.cpp \
    clientcode.cpp \
    groupinfo.cpp \
    clickrightbutton.cpp \
    writexml.cpp \
    movefriendtonewgroup.cpp \
    face.cpp \
    tcpclient.cpp \
    tcpserver.cpp \
    sysbutton.cpp \
    set.cpp \
    wywidget.cpp \
    wytcpserver.cpp \
    wytcpclient.cpp \
    wyface.cpp \
    yingyong.cpp \
    snake.cpp \
    yoajiang.cpp \
    antiforget.cpp \
    help.cpp \
    filepackage.cpp \
    fileshareserver.cpp \
    fileshareclient.cpp

HEADERS  += widget.h \
    clientinfo.h \
    ymzwidget.h \
    friendpart.h \
    readxml.h \
    clientcode.h \
    groupinfo.h \
    clickrightbutton.h \
    writexml.h \
    movefriendtonewgroup.h \
    face.h \
    tcpserver.h \
    tcpclient.h \
    sysbutton.h \
    set.h \
    wywidget.h \
    wytcpserver.h \
    wytcpclient.h \
    wyface.h \
    yingyong.h \
    snake.h \
    yoajiang.h \
    antiforget.h \
    help.h \
    filepackage.h \
    fileshareserver.h \
    fileshareclient.h

FORMS    += \
    ymzwidget.ui \
    lilintao.ui \
    changegroup.ui \
    clickrightbutton.ui \
    movefriendtonewgroup.ui \
    tcpserver.ui \
    tcpclient.ui \
    face.ui \
    set.ui \
    wywidget.ui \
    wytcpserver.ui \
    wytcpclient.ui \
    wyface.ui \
    yingyong.ui \
    snake.ui \
    yoajiang.ui \
    antiforget.ui \
    fileshareserver.ui \
    fileshareclient.ui \
    help.ui



QT += network

OTHER_FILES +=

RC_FILE +=myico.rc
