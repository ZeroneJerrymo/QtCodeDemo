
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRCode
TEMPLATE = app
DEFINES *= HAVE_CONFIG_H
INCLUDEPATH += qrencode-3.4.4/
INCLUDEPATH += lpng-1.6.2.1/ \
    zlib-1.2.8/

SOURCES += main.cpp\
    qrcodewidget.cpp \
    qrenc.c \
    qrencode-3.4.4/bitstream.c \
    qrencode-3.4.4/mask.c \
    qrencode-3.4.4/mmask.c \
    qrencode-3.4.4/mqrspec.c \
    qrencode-3.4.4/qrencode.c \
    qrencode-3.4.4/qrinput.c \
    qrencode-3.4.4/qrspec.c \
    qrencode-3.4.4/rscode.c \
    qrencode-3.4.4/split.c \
    qimageviewer.cpp

HEADERS  += \
    qrencode-3.4.4/split.h \
    qrencode-3.4.4/rscode.h \
    qrencode-3.4.4/qrspec.h \
    qrencode-3.4.4/qrinput.h \
    qrencode-3.4.4/qrencode_inner.h \
    qrencode-3.4.4/qrencode.h \
    qrencode-3.4.4/mqrspec.h \
    qrencode-3.4.4/mmask.h \
    qrencode-3.4.4/mask.h \
    qrencode-3.4.4/bitstream.h \
    qrcodewidget.h \
    lpng-1.6.2.1/png.h \
    lpng-1.6.2.1/pngconf.h \
    lpng-1.6.2.1/pngdebug.h \
    lpng-1.6.2.1/pnginfo.h \
    lpng-1.6.2.1/pnglibconf.h \
    lpng-1.6.2.1/pngpriv.h \
    lpng-1.6.2.1/pngstruct.h \
    zlib-1.2.8/crc32.h \
    zlib-1.2.8/deflate.h \
    zlib-1.2.8/gzguts.h \
    zlib-1.2.8/inffast.h \
    zlib-1.2.8/inffixed.h \
    zlib-1.2.8/inflate.h \
    zlib-1.2.8/inftrees.h \
    zlib-1.2.8/trees.h \
    zlib-1.2.8/zconf.h \
    zlib-1.2.8/zlib.h \
    zlib-1.2.8/zutil.h \
    qrencode-3.4.4/config.h \
    qrencode-3.4.4/getopt.h \
    qimageviewer.h

FORMS    += qrcode.ui

RESOURCES += \
    qrencode.qrc
