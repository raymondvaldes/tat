tat: thermal analysis toolbox
===========

program can be compiled and executed with the following information:

The first part includes links to the GSL libraries.
The second part includes link to the Boost Libraries
The third part are the linker and compiler flags used for compilation.

The source code can be compiled on any system as long as the GSL and Boost are
available. 

The boost and gsl libraries can be downloaded using with the following:
sudo port install boost-dev
sudo port install gsl-dev

#status
[![Build Status](https://travis-ci.org/raymondvaldes/tat.png)](https://travis-ci.org/raymondvaldes/tat)


#compiler flags
QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS += -m64
QMAKE_CXXFLAGS += -march=native
