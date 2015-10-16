#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T12:52:25
#
#-------------------------------------------------

QT       += core gui
QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AddFrequencies
TEMPLATE = app

#enables c++14 features
CONFIG += c++14
LIBS += -stdlib=libc++
QMAKE_CXXFLAGS += -stdlib=libc++

#Gives me access to my tat library headers, library object, and boost
INCLUDEPATH += /Users/raymondvaldes/Dropbox/code/tat/src
QMAKE_CXXFLAGS += -isystem /usr/local/Cellar/boost/1.58.0/include
macx: LIBS += -L/tmp/tat.dst/usr/local/bin -ltatlib


## Source Files
SOURCES += main.cpp\
        addfrequencies.cpp

HEADERS  += addfrequencies.h

FORMS    += addfrequencies.ui

RESOURCES += \
    default_frequencies.qrc
