#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T10:36:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plot-transient-amplitudes
TEMPLATE = app

#target platforms
QMAKE_MAC_SDK = macosx10.11

#enables c++14 features
LIBS += -stdlib=libc++
QMAKE_CXXFLAGS += -stdlib=libc++
CONFIG += c++14
ICON = plot-transient-amplitudes.icns


#Gives me access to my tat library headers, library object, and boost
INCLUDEPATH += /Users/raymondvaldes/Dropbox/code/tat/src

QMAKE_CXXFLAGS += -isystem /usr/local/Cellar/boost/1.58.0/include
macx: LIBS += -L/usr/local/lib -lboost_system
macx: LIBS += -L/usr/local/lib -lboost_filesystem
macx: LIBS += -L/tmp/tat.dst/usr/local/bin -ltatlib

INCLUDEPATH += /Users/raymondvaldes/Dropbox/code/tat/qt_utilities
macx: LIBS += -L/Users/raymondvaldes/code/tat/qt_utilities/build-qt_utilities-Desktop_Qt_5_5_0_clang_64bit-Release -lqt_utilities

## source files
SOURCES += main.cpp\
        mainwindow.cpp \
    analyze_tbd_meta_info_for_transient_temperature.cpp \
    phase_analysis.cpp \
    amplitude_analysis.cpp

HEADERS  += mainwindow.h \
    analyze_tbd_meta_info_for_transient_temperature.h \
    phase_analysis.h \
    amplitude_analysis.h

FORMS    += mainwindow.ui
