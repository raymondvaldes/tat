tat: thermal analysis toolbox
===========

program can be compiled and executed with the following information:

The first part includes links to the GSL libraries.
The second part includes link to the Boost Libraries
The third part are the linker and compiler flags used for compilation.

The source code can be compiled on any system as long as the GSL, BOOST and
OpenMP libraries are available for linking. OpenMP is bundled with recent
versions of GCC. OpenMP is used to increase the performance of the simulations
and can be disabled in the source code.  This will remove the dependency on the
OpenMP library.  I have seen performance increase of up to 6.4 using 8-core CPU.

The boost and gsl libraries can be downloaded using with the following:
sudo port install boost-dev
sudo port install gsl-dev

#status
[ ![Codeship Status for raymondvaldes/tat](https://codeship.io/projects/d5d3fb70-dd59-0131-1240-527664cf38f6/status)](https://codeship.io/projects/24663)

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



  ,           , 
 /             \ 
((__-^^-,-^^-__)) 
 `-_---' `---_-' 
  `--|o` 'o|--' 
     \  `  / 
      ): :( 
      :o_o: 
       "-" 
