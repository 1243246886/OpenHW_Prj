#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T15:51:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION,4): QT += widgets printsupport

TARGET = DP_customplot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../qcustomplot/qcustomplot.cpp \
    Serial_HRT.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    Serial_HRT.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv \
            /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so
target.path = /usr/bin
INSTALLS += target
