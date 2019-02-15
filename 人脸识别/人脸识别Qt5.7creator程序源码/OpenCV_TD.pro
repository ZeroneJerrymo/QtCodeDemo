#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T15:11:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV_TD
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addpeople.cpp \
    file.cpp

HEADERS  += mainwindow.h \
    addpeople.h \
    file.h \
    currtime.h \
    gbk.h

FORMS    += mainwindow.ui \
    addpeople.ui

INCLUDEPATH +=-LC:\opencv\include\opencv\
               C:\opencv\include\opencv2\
               C:\opencv\include
LIBS += C:\opencv\lib\libopencv_imgproc249.dll.a\
        C:\opencv\lib\libopencv_calib3d249.dll.a\
        C:\opencv\lib\libopencv_contrib249.dll.a\
        C:\opencv\lib\libopencv_core249.dll.a\
        C:\opencv\lib\libopencv_features2d249.dll.a\
        C:\opencv\lib\libopencv_flann249.dll.a\
        C:\opencv\lib\libopencv_gpu249.dll.a\
        C:\opencv\lib\libopencv_highgui249.dll.a\
        C:\opencv\lib\libopencv_legacy249.dll.a\
        C:\opencv\lib\libopencv_ml249.dll.a\
        C:\opencv\lib\libopencv_nonfree249.dll.a\
        C:\opencv\lib\libopencv_objdetect249.dll.a\
        C:\opencv\lib\libopencv_ocl249.dll.a\
        C:\opencv\lib\libopencv_photo249.dll.a\
        C:\opencv\lib\libopencv_stitching249.dll.a\
        C:\opencv\lib\libopencv_superres249.dll.a\
        C:\opencv\lib\libopencv_video249.dll.a\
        C:\opencv\lib\libopencv_videostab249.dll.a

RESOURCES += \
    pic/resource.qrc

DISTFILES +=

RC_FILE = \
  app.rc
