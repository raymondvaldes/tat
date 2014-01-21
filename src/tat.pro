#/*---------------------------------------------------------------------------*\
#  ========      	        |
#     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
#     ||   A Analysis     |
#     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
#     ||  		            |
#-------------------------------------------------------------------------------
#License
#    This file is part of Thermal Analysis Toolbox.
#
#    Thermal Analysis Toolbox is free software: you can redistribute it and/or
#    modify it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or (at your
#    option) any later version.
#
#    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
#    Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.
#
#\*---------------------------------------------------------------------------*/

#cache()
#application type
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT
QMAKE_CXXFLAGS += -std=c++11

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
    main.cpp \
    algorithms/ThermalProp_Analysis.cpp \
    algorithms/statistical_tools.cpp \
    algorithms/sensitivity_analysis.cpp \
    investigations/sensitivity_paper.cpp \
    numSimulations/Numerical_Temperature.cpp \
    numSimulations/Numerical_Setup.cpp \
    numSimulations/Numerical_PhaseOfEmission_Results.cpp \
    numSimulations/Numerical_PhaseOfEmission.cpp \
    tools/filesystem.cpp \
    tools/timing.cpp \
    models/Thermal_models.cpp \
    models/expEquipment.cpp \
    algorithms/lmdiff.cpp \
    models/poptea.cpp \
    models/physicalmodel.cpp \
    models/numericalmodel.cpp \
    tools/configuration.cpp \
    math/bisection.cpp \
    math/sensitivityAnalysis/parameterEstimationInterval.cpp \
    investigations/sensitivityvaldes2013.cpp \
    investigations/manyfit.cpp \
    thermal/thermal.cpp \
    thermal/construct.cpp \
    thermal/emission.cpp \
    thermal/model.cpp \
    thermal/emission/noise.cpp \
    thermal/emission/phase99.cpp \
    math/parameterEstimation/parameterestimation.cpp

#header files
HEADERS += \
    Header.h \
    algorithms/ThermalProp_Analysis.h \
    algorithms/statistical_tools.hpp \
    investigations/sensitivity_paper.h \
    numSimulations/Numerical_Temperature.h \
    numSimulations/Numerical_Setup.h \
    numSimulations/Numerical_PhaseOfEmission_Results.h \
    numSimulations/Numerical_PhaseOfEmission.h \
    tools/filesystem.hpp \
    tools/timing.h \
    algorithms/sensitivity_analysis.hpp \
    models/Thermal_models.h \
    models/expEquipment.hpp \
    algorithms/lmdiff.h \
    models/poptea.hpp \
    models/physicalmodel.hpp \
    models/numericalmodel.hpp \
    tools/configuration.hpp \
    math/bisection.hpp \
    math/sensitivityAnalysis/parameterEstimationInterval.hpp \
    investigations/sensitivityvaldes2013.hpp \
    investigations/manyfit.hpp \
    investigations/all.hpp \
    thermal/thermal.hpp \
    thermal/construct.hpp \
    thermal/emission.hpp \
    thermal/model.hpp \
    thermal/emission/noise.hpp \
    thermal/emission/phase99.hpp \
    math/parameterEstimation/parameterestimation.hpp
