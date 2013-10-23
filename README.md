phdResearch
===========

program can be compiled and executed with the following information:

The first part includes links to the GSL libraries.
The second part includes link to the Boost Libraries
The third part are the linker and compiler flags used for compilation.

////////////////////////////////////////////////////
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
QMAKE_LFLAGS +=  -fopenmp

////////////////////////////////////////////////////
