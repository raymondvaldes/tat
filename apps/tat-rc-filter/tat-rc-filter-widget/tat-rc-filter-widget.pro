#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T11:07:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tat-rc-filter-widget
TEMPLATE = app

#enable printing images
QT += svg

#enables c++14 features
CONFIG += c++14
LIBS += -stdlib=libc++
QMAKE_CXXFLAGS += -stdlib=libc++

#Gives me access to my tat library headers, library object, and boost
INCLUDEPATH += /Users/raymondvaldes/Dropbox/code/tat/src
QMAKE_CXXFLAGS += -isystem /usr/local/Cellar/boost/1.58.0/include
macx: LIBS += -L/tmp/tat.dst/usr/local/bin -ltatlib

#source code and headers
SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
