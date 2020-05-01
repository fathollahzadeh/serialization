#!/usr/bin/env bash

#define a name for project target
project_target="TwitterSerialization"

#set data and out serialization files path
datapath=$1
mkdir -p "$2"
numberOfTweets=$3
# for round:
for r in 1 2 3 4 5
do
    for serialization_type in 1 2 3 4 5 6 #1-Handcoded, 2-InPlace, 3-Boost, 4-Proto 5-BSON 6-FlatBufers
    do
      ./resultPath.sh $numberOfTweets $r

        outpath="$2/serialization_$serialization_type.se"
        echo "start to run the project for serialization type: " $serialization_type

        #clear the OS cache
        echo 3 > /proc/sys/vm/drop_caches && sync
        time ./bin/$project_target $datapath $serialization_type $outpath $numberOfTweets $r 0

        sleep 200

        echo 3 > /proc/sys/vm/drop_caches && sync
        time taskset -c 0 ./bin/$project_target $datapath $serialization_type $outpath $numberOfTweets $r 1
    done

done
