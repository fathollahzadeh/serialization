#!/bin/bash

#cleanup
rm -rf SerializationJava.jar
rm -rf cppbin
rm -rf rustbin
cd ..
path=$(pwd)

cd "$path"
# compile Java baselines
# mvn clean compile assembly:single
# mv target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar "$path/Experiments/SerializationJava.jar"

# # compile C++ baslelines
cd "$path/src/main/cpp"
# rm -rf CMakeFiles
# rm -rf cmake_install.cmake
# rm -rf CMakeCache.txt
# rm -rf Makefile
# rm -rf cpp.cbp
# rm -rf bin
# cmake .
# make clean
# make -j12

# mv  bin/ "$path/Experiments/cppbin"

# compile Rust baselines
cd "$path/src/main/rust"
#cargo clean

cargo build --release
mkdir -p "$path/Experiments/rustbin"
cp -r target/release/DataPrepare "$path/Experiments/rustbin/"
cp -r target/release/DataSerializationSingle "$path/Experiments/rustbin/"


