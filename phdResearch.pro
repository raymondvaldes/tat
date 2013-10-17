#application type
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#paths
INCLUDEPATH += /usr/lib/
INCLUDEPATH += /usr/include/

#source files
SOURCES += main.cpp \
    algorithms/ThermalProp_Analysis.cpp \
    algorithms/statistical_tools.cpp \
    algorithms/parameterEstimationAlgorithms.cpp \
    investigations/sensitivity_paper.cpp \
    numSimulations/Numerical_Temperature.cpp \
    numSimulations/Numerical_Setup.cpp \
    numSimulations/Numerical_PhaseOfEmission_Results.cpp \
    numSimulations/Numerical_PhaseOfEmission.cpp \
    numSimulations/models.cpp \
    numSimulations/Experimental_PhaseOfEmission.cpp \
    tools/filesystem.cpp

#header files
HEADERS += \
    Header.h \
    algorithms/ThermalProp_Analysis.h \
    algorithms/statistical_tools.hpp \
    algorithms/parameterEstimationAlgorithms.hpp \
    investigations/sensitivity_paper.h \
    numSimulations/Numerical_Temperature.h \
    numSimulations/Numerical_Setup.h \
    numSimulations/Numerical_PhaseOfEmission_Results.h \
    numSimulations/Numerical_PhaseOfEmission.h \
    numSimulations/models.h \
    numSimulations/Experimental_PhaseOfEmission.h \
    tools/filesystem.hpp

#gsl libraries
LIBS += -L/usr/lib -lgsl -lgslcblas -lm

#boost libraries
LIBS += -L/usr/lib -lboost_system -lboost_filesystem

#compiler flags
QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS += -m64
QMAKE_CXXFLAGS += -fopenmp
QMAKE_CXXFLAGS += -march=native

#compiler warnings
QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Wextra
QMAKE_CXXFLAGS += -Wfatal-errors
QMAKE_CXXFLAGS += -pedantic
QMAKE_CXXFLAGS += -Wmain
QMAKE_CXXFLAGS += -Wswitch-default
QMAKE_CXXFLAGS += -Wswitch-enum
QMAKE_CXXFLAGS += -Wfloat-equal
QMAKE_CXXFLAGS += -Wcast-align
QMAKE_CXXFLAGS += -Wredundant-decls
QMAKE_CXXFLAGS += -Winit-self
QMAKE_CXXFLAGS += -Wshadow

#compiler
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -funroll-loops
QMAKE_CXXFLAGS += -fmessage-length=0
QMAKE_CXXFLAGS += -Wwrite-strings
QMAKE_CXXFLAGS += -Wcast-qual
QMAKE_CXXFLAGS += -Wpointer-arith
QMAKE_CXXFLAGS += -Wstrict-aliasing
QMAKE_CXXFLAGS += -Wformat=2
QMAKE_CXXFLAGS += -Wuninitialized
QMAKE_CXXFLAGS += -flto
QMAKE_CXXFLAGS += -fwhole-program

#linker flags
QMAKE_LFLAGS +=  -fopenmp
