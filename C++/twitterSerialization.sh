#!/usr/bin/env bash

#define a name for project target
project_target="TwitterSerialization"

#set data and out serialization files path
datapath=$1
mkdir -p "$2"
numberOfTweets=$3

for serialization_type in 1 2 3 4 5 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto 5-BSON
do
    outpath="$2/serialization_$serialization_type.se"
    echo "start to run the project for serialization type: " $serialization_type
    echo "------------------------"
    time ./bin/$project_target $datapath $serialization_type $outpath $numberOfTweets
done
