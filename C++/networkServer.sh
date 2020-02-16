#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
./makeClean.sh

#define a name for project target
project_target="TwitterNetworkServer"

#serialization type
serialization_type=1 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto
number_of_clients=1
#20 M network page size
networkPageSize=20971520

#out data path
mkdir -p "bin/benchmark/network/server"
out_data_path="bin/benchmark/network/server"



echo "start to run the project"
echo "------------------------"
./bin/$project_target $number_of_clients $networkPageSize $out_data_path $serialization_type