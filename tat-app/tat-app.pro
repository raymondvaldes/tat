TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -march=native
QMAKE_CXXFLAGS += -stdlib=libc++

QMAKE_CXXFLAGS += -isystem /usr/local/include
INCLUDEPATH += /Users/raymondvaldes/Dropbox/code/tat/src

SOURCES += main.cpp

