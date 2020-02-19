#!/usr/bin/env bash

# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
./makeClean.sh


#set data and out serialization files path
datapath="/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/tweets_jsonline_1M.txt"

for serialization_type in 6 #2 3 4 5 6
do
    outpath="/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/jdata/serialization_$serialization_type.se"
    echo "start to run the project"
    echo "------------------------"

    #./bin/$project_target $datapath $serialization_type $outpath
    #-Xms15g -Xmx30g

    #echo 3 > /proc/sys/vm/drop_caches && sync
    time taskset -c 0 java   -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.DataSerialization $datapath $serialization_type $outpath
done
