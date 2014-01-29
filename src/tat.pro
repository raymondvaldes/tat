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
LIBS += -L/usr/lib -lboost_system -lboost_filesystem -lboost_program_options
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
    tools/filesystem.cpp \
    tools/timing.cpp \
    models/expEquipment.cpp \
    models/physicalmodel.cpp \
    tools/configuration.cpp \
    math/bisection.cpp \
    investigations/sensitivityvaldes2013.cpp \
    investigations/manyfit.cpp \
    thermal/thermal.cpp \
    thermal/construct.cpp \
    thermal/emission.cpp \
    thermal/model.cpp \
    thermal/emission/noise.cpp \
    thermal/emission/phase99.cpp \
    math/estimation/lmdiff.cpp \
    math/estimation/parameterestimation.cpp \
    math/sensitivityAnalysis/estimationInterval.cpp \
    tools/programoptions.cpp \
    thermal/analysis/kernal.cpp \
    thermal/analysis/poptea.cpp \
    math/estimation/lmdiff_helper.cpp \
    math/estimation/utils.cpp \
    math/estimation/constrained.cpp \
    math/utility.cpp \
    math/numIntegration/simpsons_3_8.cpp \
    math/estimation/cosfit.cpp \
    math/numIntegration/gslfunc.cpp \
    tools/export.cpp \
    thermal/heat/heat2DAna.cpp \
    thermal/analysis/lmdiff_poptea.cpp \
    thermal/analysis/lmdiff_poptea_help.cpp \
    thermal/analysis/sa_sensitivity.cpp \
    thermal/analysis/thermalData.cpp \
    math/statistical_tools.cpp \
    thermal/simulations/Numerical_PhaseOfEmission.cpp \
    thermal/simulations/Numerical_Setup.cpp \
    thermal/simulations/Numerical_Temperature.cpp \
    thermal/simulations/numericalmodel.cpp \
    tools/log.cpp \
    tools/version.cpp

#header files
HEADERS += \
    tools/filesystem.hpp \
    tools/timing.h \
    models/expEquipment.hpp \
    models/physicalmodel.hpp \
    tools/configuration.hpp \
    math/bisection.hpp \
    investigations/sensitivityvaldes2013.hpp \
    investigations/manyfit.hpp \
    investigations/all.hpp \
    thermal/thermal.hpp \
    thermal/construct.hpp \
    thermal/emission.hpp \
    thermal/model.hpp \
    thermal/emission/noise.hpp \
    thermal/emission/phase99.hpp \
    math/estimation/parameterestimation.hpp \
    math/sensitivityAnalysis/parameterEstimationInterval.hpp \
    math/estimation/lmdiff.hpp \
    math/sensitivityAnalysis/estimationInterval.hpp \
    tools/programoptions.hpp \
    thermal/analysis/kernal.hpp \
    thermal/analysis/poptea.hpp \
    math/estimation/lmdiff_helper.hpp \
    math/estimation/utils.hpp \
    math/estimation/constrained.hpp \
    math/utility.hpp \
    math/numIntegration/simpsons_3_8.hpp \
    math/estimation/cosfit.hpp \
    math/numIntegration/gslfunc.hpp \
    tools/export.hpp \
    thermal/heat/heat2DAna.hpp \
    thermal/analysis/lmdiff_poptea.hpp \
    thermal/analysis/lmdiff_poptea_help.hpp \
    thermal/analysis/sa_sensitivity.hpp \
    thermal/analysis/thermalData.hpp \
    math/statistical_tools.hpp \
    thermal/simulations/Numerical_PhaseOfEmission.h \
    thermal/simulations/Numerical_Setup.h \
    thermal/simulations/Numerical_Temperature.h \
    thermal/simulations/numericalmodel.hpp \
    tools/log.hpp \
    tools/tools.hpp \
    tools/version.hpp
