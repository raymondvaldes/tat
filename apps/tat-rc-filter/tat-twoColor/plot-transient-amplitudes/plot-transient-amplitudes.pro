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

QMAKE_CXXFLAGS += -isystem /usr/local/include

macx: LIBS += -L/usr/local/lib -lboost_system
macx: LIBS += -L/usr/local/lib -lboost_filesystem
macx: LIBS += -L/usr/local/bin -ltatlib

## source files
SOURCES += main.cpp\
        mainwindow.cpp \
    analyze_tbd_meta_info_for_transient_temperature.cpp \
    phase_analysis.cpp \
    amplitude_analysis.cpp \
    load_file_path_from_dialog.cpp

HEADERS  += mainwindow.h \
    analyze_tbd_meta_info_for_transient_temperature.h \
    phase_analysis.h \
    amplitude_analysis.h \
    load_file_path_from_dialog.h

FORMS    += mainwindow.ui
