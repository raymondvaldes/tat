#!/bin/bash


sudo apt-get install qt5-default
sudo apt-get install make

sudo add-apt-repository -y ppa:boost-latest/ppa
sudo apt-get update
sudo apt-get install libboost1.55-all-dev

 
sudo apt-get install libgsl0-dev
 
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get -qq update
sudo apt-get -qq install gcc-4.8 g++-4.8
 
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 90
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 90

g++ --version
gcc --version

chmod +x install
chmod u+w ~
