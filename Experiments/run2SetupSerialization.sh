#!/bin/bash

#cleanup
rm -rf SerializationJava.jar
rm -rf cppbin

# compile Java baselines
cd ..
cd Java
#mvn clean compile assembly:single
#mv target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar ../Experiments/SerializationJava.jar

cd ..
# compile C++ baslelines
cd Java/src/main/cpp
rm -rf CMakeFiles
rm -rf cmake_install.cmake
rm -rf CMakeCache.txt
rm -rf Makefile
rm -rf cpp.cbp
rm -rf bin
# cmake .
make clean
# make -j12

# mv  bin/ ../../../../Experiments/cppbin




# compile Rust baselines
