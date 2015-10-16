TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14

SOURCES += main.cpp

INCLUDEPATH += /Users/raymondvaldes/Dropbox/code/tat/src
QMAKE_CXXFLAGS += -isystem /usr/local/Cellar/boost/1.58.0/include
macx: LIBS += -L/tmp/tat.dst/usr/local/bin -ltatlib
