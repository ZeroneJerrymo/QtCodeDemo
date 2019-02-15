#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T15:38:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Opencv
TEMPLATE = app

#INCLUDEPATH and LIBS depend on opencv's path where is installed in your computer
win32{
    INCLUDEPATH += "D:\\Program Files (x86)\\opencv\\build\\include"
    LIBS += -L"D:\\Program Files (x86)\\opencv\\build\\x86\\vc12\\lib"

    CONFIG(debug, debug|release){
        LIBS += -lopencv_core2413d       \
                 -lopencv_highgui2413d   \
                 -lopencv_imgproc2413d   \
                 -lopencv_video2413d     \
                 -lopencv_objdetect2413d
    }else{
        LIBS += -lopencv_core2413       \
                -lopencv_highgui2413    \
                -lopencv_imgproc2413    \
                -lopencv_video2413      \
                -lopencv_objdetect2413  \
    }

}

linux{
    INCLUDEPATH += "/usr/local/include"
    LIBS += -L"/home/Installer/opencv-2.4.13/opencv-2.4.13/lib"

    CONFIG(debug, debug|release){
        LIBS += -lopencv_cored       \
                -lopencv_highguid    \
                -lopencv_imgprocd    \
                -lopencv_videod      \
                -lopencv_objdetectd  \
    }else{
        LIBS += -lopencv_core       \
                -lopencv_highgui    \
                -lopencv_imgproc    \
                -lopencv_video      \
                -lopencv_objdetect  \
    }
}

SOURCES +=\
    facedetect.cpp

HEADERS  +=

FORMS    +=
