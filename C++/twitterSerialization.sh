#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
./makeClean.sh

#define a name for project target
project_target="TwitterSerialization"

#set data and out serialization files path
datapath="data/tweets_jsonline_1M.txt"

for serialization_type in 1 2 3 4 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto
do
    outpath="data/serialization_$serialization_type.se"
    echo "start to run the project"
    echo "------------------------"

    ./bin/$project_target $datapath $serialization_type $outpath
done
