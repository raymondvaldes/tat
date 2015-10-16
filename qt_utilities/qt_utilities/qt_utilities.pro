#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T11:35:02
#
#-------------------------------------------------

QT       += svg testlib

QT       -= gui

TARGET = qt_utilities
TEMPLATE = lib
CONFIG += staticlib


#enables c++14 features
CONFIG += c++14
LIBS += -stdlib=libc++
QMAKE_CXXFLAGS += -stdlib=libc++

#Gives me access to my tat library headers, library object, and boost
INCLUDEPATH += /Users/raymondvaldes/Dropbox/code/tat/src
macx: LIBS += -L/tmp/tat.dst/usr/local/bin -ltatlib

QMAKE_CXXFLAGS += -isystem /usr/local/Cellar/boost/1.58.0/include


## source
SOURCES += \
    load_file_path_from_dialog.cpp

HEADERS += \
    load_file_path_from_dialog.h
unix {
    target.path = /Users/raymondvaldes/usr/local/bin
    INSTALLS += target
}


macx {
    QMAKE_MAC_SDK = macosx10.11
}
