#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
./makeClean.sh

#define a name for project target
project_target="TwitterNetworkClient"

serialization_type=1 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto
datapath="data/serialization_$serialization_type.se"
hostName="127.0.0.1"
portNumber=30000
numOfObjects=978
ioType=2 #1: RAM, 2:Disk
networkPageSize=20971520


echo "start to run the project"
echo "------------------------"
./bin/$project_target $datapath $hostName $serialization_type $numOfObjects $portNumber $ioType $networkPageSize