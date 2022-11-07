#!/bin/bash

#cleanup
rm -rf SerializationJava.jar
rm -rf cppbin
rm -rf rustbin
cd ..
path=$(pwd)

cd "$path"
# compile Java baselines
#mvn clean compile assembly:single
#mv target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar "$path/Experiments/SerializationJava.jar"

# compile C++ baslelines
cd "$path/src/main/cpp"
# rm -rf CMakeFiles
# rm -rf cmake_install.cmake
# rm -rf CMakeCache.txt
# rm -rf Makefile
# rm -rf cpp.cbp
# rm -rf bin
cmake .
#make clean
make -j16

mv  bin/ "$path/Experiments/cppbin"

# rm -rf CMakeFiles
# rm -rf cmake_install.cmake
# rm -rf CMakeCache.txt
# rm -rf Makefile
# rm -rf cpp.cbp
# rm -rf bin

# compile Rust baselines
cd "$path/src/main/rust"
# $HOME/.cargo/bin/cargo clean

# $HOME/.cargo/bin/cargo build --release
# mkdir -p "$path/Experiments/rustbin"
# cp -r target/release/DataPrepare "$path/Experiments/rustbin/"
# cp -r target/release/DataLoadToMemorySingle "$path/Experiments/rustbin/"
# cp -r target/release/DataLoadToMemoryParallel "$path/Experiments/rustbin/"
# cp -r target/release/DataReadIOParallel "$path/Experiments/rustbin/"
# cp -r target/release/DataReadSingle "$path/Experiments/rustbin/"
# cp -r target/release/DataReadParallel "$path/Experiments/rustbin/"
# cp -r target/release/DataReadIOSingle "$path/Experiments/rustbin/"
# cp -r target/release/DataSerializationSingle "$path/Experiments/rustbin/"
# cp -r target/release/DataSerializationParallel "$path/Experiments/rustbin/"
# cp -r target/release/DataWriteSingle "$path/Experiments/rustbin/"
# cp -r target/release/DataWriteParallel "$path/Experiments/rustbin/"
# cp -r target/release/ExternalSort "$path/Experiments/rustbin/"
# cp -r target/release/ExternalSortIO "$path/Experiments/rustbin/"
# cp -r target/release/DataReadNetwork "$path/Experiments/rustbin/"
# cp -r target/release/DataReadNetworkIO "$path/Experiments/rustbin/"

