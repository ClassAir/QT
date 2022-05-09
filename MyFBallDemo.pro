#-------------------------------------------------
#
# Project created by QtCreator 2018-09-09T11:08:07
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyFBallDemo
TEMPLATE = app


SOURCES += main.cpp\
    fballwidget.cpp \
    mainwindow.cpp \




HEADERS  += \
    fballwidget.h \
    mainwindow.h



FORMS    += \
    mainwindow.ui

RESOURCES += \
    myfballdemo.qrc

DISTFILES += \
    images/background.png \
    images/handle.png \
    images/handlePress.png \
    images/QQ截图1.png \
    images/QQ截图2.png \
    images/QQ截图3.png \
    images/QQ截图4.png

LIBS +=-LC:/Qt/workSpace/MyFBallDemo/libs -lHCCore -lHCNetSDK -lPlayCtrl
LIBS +=-LC:/Qt/workSpace/MyFBallDemo/libs/HCNetSDKCom -lHCAlarm -lHCGeneralCfgMgr -lHCPreview
