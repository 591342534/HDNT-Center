#-------------------------------------------------
#
# Project created by QtCreator 2019-02-15T20:10:07
#
#-------------------------------------------------

QT       += widgets serialport

TARGET = hdntCom
TEMPLATE = lib

DEFINES += HDNTCOM_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        hdntcom.cpp \
    workthread.cpp

HEADERS += \
        hdntcom.h \
        hdntcom_global.h \  
    workthread.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
