#!/usr/bin/env bash

#set data and out serialization files path
datapath=$1
mkdir -p "$2"
numberOfTweets=$3

for serialization_type in  1 2 3 4 5 6
do
    outpath="$2/serialization_$serialization_type.se"
    echo "start to run the project for serialization type: " $serialization_type
    echo "------------------------"
    time java   -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms4g -Xmx6g -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.DataSerialization $datapath $serialization_type $outpath $numberOfTweets
done
