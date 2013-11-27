phdResearch
===========

program can be compiled and executed with the following information:

The first part includes links to the GSL libraries.
The second part includes link to the Boost Libraries
The third part are the linker and compiler flags used for compilation.

The boost and gsl libraries can be downloaded using with the following:

sudo port install boost-dev
sudo port install gsl-dev

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
Setting up a custom macports gcc compiler in QT Creator needed the modification
of the QT MkSpecs folder :" macx-g++48". The files within the folder must be 
modified to only reference gcc/g++48 instead of gcc/g++. If these changes are
not made then QT Creator will invoke the default Apple GCC compiler v4.2. 
