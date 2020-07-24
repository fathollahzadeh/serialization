#!/usr/bin/env bash

#set data and out serialization files path
datapath=$1
mkdir -p "$2"
numberOfTweets=$3

# for round:
for r in 1 2 3 #4 5
do
    for serialization_type in 1 2 3 4 5
    do
       ./resultPath.sh $numberOfTweets $r
        outpath="$2/serialization_$serialization_type.se"
        echo "start to run the project for serialization type: " $serialization_type

       #clear the OS cache
        #echo 3 > /proc/sys/vm/drop_caches && sync
        time cargo run --release write  $datapath $serialization_type $outpath $numberOfTweets $r false

        sleep 1

        #clear the OS cache
        #echo 3 > /proc/sys/vm/drop_caches && sync
        time taskset -c 0 cargo run --release write  $datapath $serialization_type $outpath $numberOfTweets $r true

    done

done
