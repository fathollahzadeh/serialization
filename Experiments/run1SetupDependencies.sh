#!/bin/bash
sudo apt update

# install zip and bzip2 for unzip dataset
sudo apt-get install zip -y
sudo apt-get -y install bzip2
pip install gdown -y

# setup Java dependencies
sudo apt-get install -y openjdk-11-jdk-headless
sudo apt install -y maven
sudo apt install -y git
export JAVA_HOME=/usr/lib/jvm/java-1.11.0-openjdk-amd64

# setup C++ dependencies
# create a directory for cpp dependecies
sudo rm -rf CPPDependencies #clean-up
mkdir CPPDependencies
cd CPPDependencies
path=$(pwd)

sudo apt-get install -y cmake
# 1. install C++ :
sudo apt-get install -y clang

# 2. install ubuntu RapidJson:
sudo apt-get install -y rapidjson-dev

# 3. install libboost:
wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.bz2
tar -xf boost_1_80_0.tar.bz2
cd boost_1_80_0
./bootstrap.sh --prefix=/usr/
./b2
sudo ./b2 install
cd $path

# 4.install google protobuf
sudo apt-get autoremove -y libprotobuf-dev protobuf-compiler
sudo apt-get install -y autoconf automake libtool curl make g++ unzip
wget https://github.com/protocolbuffers/protobuf/releases/download/v21.5/protobuf-cpp-3.21.5.tar.gz
tar -xf protobuf-cpp-3.21.5.tar.gz
cd "$path/protobuf-3.21.5"
./configure
make
make check
sudo make install
sudo ldconfig # refresh shared library cache.
cd $path

# 5. install C++ BSON: Installing the mongocxx driver
sudo apt-get install -y libssl-dev
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.22.1/mongo-c-driver-1.22.1.tar.gz
tar xzf mongo-c-driver-1.22.1.tar.gz
cd "$path/mongo-c-driver-1.22.1"
mkdir cmake-build
cd cmake-build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
sudo make install
cd $path

wget https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.7/mongo-cxx-driver-r3.6.7.tar.gz
tar xzf mongo-cxx-driver-r3.6.7.tar.gz
cd mongo-cxx-driver-r3.6.7/build
sudo cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install

# setup Rust dependencies
# curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
