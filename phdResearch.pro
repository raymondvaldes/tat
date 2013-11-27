###REQUIRED########################
cache()
#application type
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT

#paths
unix:!macx{
INCLUDEPATH += /usr/lib/
INCLUDEPATH += /usr/include/
LIBS += -L/usr/lib -lgomp
LIBS += -L/usr/lib -lgsl -lgslcblas -lm
LIBS += -L/usr/lib -lboost_system -lboost_filesystem
}

macx {
#CONFIG += MAC_CONFIG
#QMAKE_CXX = /opt/local/bin/g++
INCLUDEPATH += /opt/local/lib
INCLUDEPATH += /opt/local/include

#LIBS += /opt/local/lib -lgsl -lgslcblas -lm
#LIBS += /opt/local/lib -lboost_system -lboost_filesystem

INCLUDEPATH += opt/local/include
DEPENDPATH  += opt/local/include

unix: LIBS += -L$$PWD/../../../../../opt/local/lib/gcc48/ -lgomp
unix: PRE_TARGETDEPS += $$PWD/../../../../../opt/local/lib/gcc48/libgomp.a

unix: LIBS += -L$$PWD/../../../../../opt/local/lib/ -lgsl
unix: PRE_TARGETDEPS += $$PWD/../../../../../opt/local/lib/libgsl.a

unix: LIBS += -L$$PWD/../../../../../opt/local/lib/ -lgslcblas
unix: PRE_TARGETDEPS += $$PWD/../../../../../opt/local/lib/libgslcblas.a

unix: LIBS += -L$$PWD/../../../../../opt/local/lib/ -lboost_filesystem-mt
unix: PRE_TARGETDEPS += $$PWD/../../../../../opt/local/lib/libboost_filesystem-mt.a

unix: LIBS += -L$$PWD/../../../../../opt/local/lib/ -lboost_system-mt
unix: PRE_TARGETDEPS += $$PWD/../../../../../opt/local/lib/libboost_system-mt.a

}

#compiler flags
#QMAKE_CXXFLAGS += -std=gnu++11 (automatically applied with c++11 flag)
#QMAKE_CXXFLAGS += -m64 (automatically applied with release)
#QMAKE_CXXFLAGS += -O3 (automatically applied with release)
QMAKE_CXXFLAGS += -fopenmp
QMAKE_CXXFLAGS += -march=native

#linker flags
QMAKE_LFLAGS += -fopenmp

##Optional#########################
#compiler warnings
QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Wextra
QMAKE_CXXFLAGS += -Wfatal-errors
QMAKE_CXXFLAGS += -pedantic
QMAKE_CXXFLAGS += -Wmain
QMAKE_CXXFLAGS += -Wswitch-default
QMAKE_CXXFLAGS += -Wswitch-enum
#QMAKE_CXXFLAGS += -Wfloat-equal (BUG fix this)
QMAKE_CXXFLAGS += -Wcast-align
QMAKE_CXXFLAGS += -Wredundant-decls
QMAKE_CXXFLAGS += -Winit-self
#QMAKE_CXXFLAGS += -Wshadow (TODO fix this)

#compiler
QMAKE_CXXFLAGS += -Wdeprecated
QMAKE_CXXFLAGS += -Wunused-parameter
QMAKE_CXXFLAGS += -fmessage-length=0
QMAKE_CXXFLAGS += -Wwrite-strings
QMAKE_CXXFLAGS += -Wcast-qual
QMAKE_CXXFLAGS += -Wpointer-arith
QMAKE_CXXFLAGS += -Wstrict-aliasing
QMAKE_CXXFLAGS += -Wformat=2
QMAKE_CXXFLAGS += -Wuninitialized
QMAKE_CXXFLAGS += -flto
QMAKE_CXXFLAGS += -fwhole-program

##Optional#########################

#source files
SOURCES += \
    src/main.cpp \
    src/algorithms/ThermalProp_Analysis.cpp \
    src/algorithms/statistical_tools.cpp \
    src/algorithms/sensitivity_analysis.cpp \
    src/investigations/sensitivity_paper.cpp \
    src/numSimulations/Numerical_Temperature.cpp \
    src/numSimulations/Numerical_Setup.cpp \
    src/numSimulations/Numerical_PhaseOfEmission_Results.cpp \
    src/numSimulations/Numerical_PhaseOfEmission.cpp \
    src/numSimulations/Experimental_PhaseOfEmission.cpp \
    src/tools/filesystem.cpp \
    src/tools/timing.cpp \
    src/models/Thermal_models.cpp \
    src/models/expEquipment.cpp \
    src/algorithms/lmdiff.cpp \
    src/algorithms/parameterestimation.cpp \
    src/models/poptea.cpp \
    src/models/physicalmodel.cpp \
    src/numSimulations/mesh.cpp \
    src/models/numericalmodel.cpp

#header files
HEADERS += \
    include/Header.h \
    include/algorithms/ThermalProp_Analysis.h \
    include/algorithms/statistical_tools.hpp \
    include/investigations/sensitivity_paper.h \
    include/numSimulations/Numerical_Temperature.h \
    include/numSimulations/Numerical_Setup.h \
    include/numSimulations/Numerical_PhaseOfEmission_Results.h \
    include/numSimulations/Numerical_PhaseOfEmission.h \
    include/numSimulations/Experimental_PhaseOfEmission.h \
    include/tools/filesystem.hpp \
    include/tools/timing.h \
    include/algorithms/sensitivity_analysis.hpp \
    include/models/Thermal_models.h \
    include/models/expEquipment.hpp \
    include/algorithms/lmdiff.h \
    include/algorithms/parameterestimation.hpp \
    include/models/poptea.hpp \
    include/models/physicalmodel.hpp \
    include/numSimulations/mesh.hpp \
    include/models/numericalmodel.hpp
