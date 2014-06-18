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
#CONFIG += static
CONFIG += c++11
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT
QMAKE_CXXFLAGS += -std=c++11

#paths
unix:!macx{

  LIBS += -L/usr/lib -lgomp
  LIBS += -L/usr/lib -lm

  INCLUDEPATH += /usr/include/usr/
  DEPENDPATH += /usr/include
  LIBS += -L/usr/lib/ -lgsl
  LIBS += -L/usr/lib/ -lgslcblas

  INCLUDEPATH += /usr/lib/
  DEPENDPATH += /usr/lib/
  LIBS += -L/usr/lib/ -lboost_filesystem
  LIBS += -L/usr/lib/ -lboost_program_options
  LIBS += -L/usr/lib/ -lboost_system
}

macx {
  CONFIG += MAC_CONFIG

  INCLUDEPATH += /usr/include/
  DEPENDPATH  += /usr/include/

  LIBS += -L/usr/lib/gcc/x86_64-linux-gnu/4.8/ -lgomp
  LIBS += -L/usr/lib/ -lgsl
  LIBS += -L/usr/lib/ -lgslcblas
  LIBS += -L/usr/lib/x86_64-linux-gnu/ -lboost_filesystem
  LIBS += -L/usr/lib/x86_64-linux-gnu/ -lboost_system
}

#compiler flags
QMAKE_CXXFLAGS += -std=gnu++11 #(automatically applied with c++11 flag)
QMAKE_CXXFLAGS += -m64 #(automatically applied with release)
QMAKE_CXXFLAGS += -O3 #(automatically applied with release)
QMAKE_CXXFLAGS += -fopenmp
QMAKE_CXXFLAGS += -march=native


#linker flags
QMAKE_LFLAGS += -fopenmp
#QMAKE_LFLAGS += -static-libgcc -static-libstdc++
#QMAKE_LFLAGS += -static

#header flags
QMAKE_CXXFLAGS += -I /usr/include/
QMAKE_LFLAGS += -I /usr/include/


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
#QMAKE_CXXFLAGS += -fwhole-program
##Optional#########################

#source files
# Input
HEADERS += investigations/num_method2014.h \
           investigations/sensitivityvaldes2013.hpp \
           math/bisection.hpp \
           math/statistical_tools.hpp \
           math/utility.hpp \
           sensible/layer.h \
           sensible/property.h \
           sensible/radiativeSysProp.h \
           sensible/TBCsystem.h \
           sensible/temperature_scale.h \
           tools/programoptions.hpp \
           tools/timing.h \
           tools/tools.hpp \
           math/algorithms/combinations.hpp \
           math/algorithms/complex.h \
           math/algorithms/spline.h \
           math/algorithms/spline_cplx.h \
           math/estimation/constrained.hpp \
           math/estimation/cosfit.hpp \
           math/estimation/lmdiff.hpp \
           math/estimation/lmdiff_helper.hpp \
           math/estimation/parameterestimation.hpp \
           math/estimation/utils.hpp \
           math/numIntegration/gslfunc.hpp \
           math/numIntegration/simpsons_3_8.hpp \
           math/sensitivityAnalysis/estimationInterval.hpp \
           math/solvers/sor.h \
           math/solvers/tma.h \
           physics/classical_mechanics/kinematics.h \
           thermal/analysis/basedata.hpp \
           thermal/analysis/kernal.hpp \
           thermal/analysis/lmdiff_poptea.hpp \
           thermal/analysis/lmdiff_poptea_help.hpp \
           thermal/analysis/methods.hpp \
           thermal/analysis/pie.hpp \
           thermal/analysis/poptea.hpp \
           thermal/analysis/poptea_initialize.h \
           thermal/analysis/thermalData.hpp \
           thermal/analysis/thermalsweepoptimizer.hpp \
           thermal/define/construct.hpp \
           thermal/define/diffusivity.h \
           thermal/define/effusivity.hpp \
           thermal/define/lthermal.h \
           thermal/define/model.hpp \
           thermal/define/model_type.h \
           thermal/define/omega.h \
           thermal/define/temperature.h \
           thermal/emission/emission.hpp \
           thermal/emission/noise.hpp \
           thermal/emission/phase99.hpp \
           thermal/equipment/detector.h \
           thermal/equipment/laser.h \
           thermal/equipment/setup.h \
           thermal/model/labels.h \
           thermal/simulations/Numerical_PhaseOfEmission.h \
           tools/interface/exportfile.hpp \
           tools/interface/filesystem.hpp \
           tools/interface/xml.h \
           thermal/analysis/cmplx_combination/cmplx_combination.h \
           thermal/analysis/sweep/temp_cmplx.h \
           thermal/analysis/sweep/temp_ss.h \
           thermal/model/one_dim/one_dim.h \
           thermal/model/one_dim/Tss_ana.h \
           thermal/model/one_dim/analytical_2005/analytical_2005.h \
           thermal/model/one_dim/numerical_2011/mesh.hpp \
           thermal/model/one_dim/numerical_2011/numerical_2011.h \
           thermal/model/one_dim/numerical_2011/Numerical_Setup.h \
           thermal/model/one_dim/numerical_2011/Numerical_Temperature.h \
           thermal/model/two_dim/analytical_2009/heat2DAna.hpp \
           "thermal/model/utilities/heat generation/Iheat.h" \
           thermal/model/utilities/nondimensional/tau_0.h \
            investigations/execute.h \
            algorithms/string/starts_with.h \
            algorithm/string/split.h

SOURCES += main.cpp \
           investigations/num_method2014.cpp \
           investigations/sensitivityvaldes2013.cpp \
           math/bisection.cpp \
           math/statistical_tools.cpp \
           math/utility.cpp \
           sensible/layer.cpp \
           sensible/property.cpp \
           sensible/radiativeSysProp.cpp \
           sensible/TBCsystem.cpp \
           sensible/temperature_scale.cpp \
           tools/programoptions.cpp \
           tools/timing.cpp \
           math/algorithms/combinations.cpp \
           math/algorithms/complex.cpp \
           math/algorithms/spline.cpp \
           math/algorithms/spline_cplx.cpp \
           math/estimation/constrained.cpp \
           math/estimation/cosfit.cpp \
           math/estimation/lmdiff.cpp \
           math/estimation/lmdiff_helper.cpp \
           math/estimation/parameterestimation.cpp \
           math/estimation/utils.cpp \
           math/numIntegration/gslfunc.cpp \
           math/numIntegration/simpsons_3_8.cpp \
           math/sensitivityAnalysis/estimationInterval.cpp \
           math/solvers/sor.cpp \
           math/solvers/tma.cpp \
           physics/classical_mechanics/kinematics.cpp \
           thermal/analysis/kernal.cpp \
           thermal/analysis/lmdiff_poptea.cpp \
           thermal/analysis/lmdiff_poptea_help.cpp \
           thermal/analysis/methods.cpp \
           thermal/analysis/pie.cpp \
           thermal/analysis/poptea.cpp \
           thermal/analysis/poptea_initialize.cpp \
           thermal/analysis/thermalData.cpp \
           thermal/analysis/thermalsweepoptimizer.cpp \
           thermal/define/construct.cpp \
           thermal/define/diffusivity.cpp \
           thermal/define/effusivity.cpp \
           thermal/define/lthermal.cpp \
           thermal/define/model.cpp \
           thermal/define/omega.cpp \
           thermal/define/temperature.cpp \
           thermal/emission/emission.cpp \
           thermal/emission/noise.cpp \
           thermal/emission/phase99.cpp \
           thermal/equipment/detector.cpp \
           thermal/equipment/laser.cpp \
           thermal/equipment/setup.cpp \
           thermal/model/labels.cpp \
           thermal/simulations/Numerical_PhaseOfEmission.cpp \
           tools/interface/exportfile.cpp \
           tools/interface/filesystem.cpp \
           tools/interface/xml.cpp \
           thermal/analysis/cmplx_combination/cmplx_combination.cpp \
           thermal/analysis/sweep/temp_cmplx.cpp \
           thermal/analysis/sweep/temp_ss.cpp \
           thermal/model/one_dim/one_dim.cpp \
           thermal/model/one_dim/Tss_ana.cpp \
           thermal/model/one_dim/analytical_2005/analytical_2005.cpp \
           thermal/model/one_dim/numerical_2011/mesh.cpp \
           thermal/model/one_dim/numerical_2011/numerical_2011.cpp \
           thermal/model/one_dim/numerical_2011/Numerical_Setup.cpp \
           thermal/model/one_dim/numerical_2011/Numerical_Temperature.cpp \
           thermal/model/two_dim/analytical_2009/heat2DAna.cpp \
           "thermal/model/utilities/heat generation/Iheat.cpp" \
           thermal/model/utilities/nondimensional/tau_0.cpp \
           investigations/execute.cpp \
            algorithms/string/starts_with.cpp \
            algorithm/string/split.cpp
