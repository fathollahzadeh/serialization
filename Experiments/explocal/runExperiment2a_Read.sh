#!/bin/bash

inDataPath=$1
nrow=$2
platform=$3
task_set=$4
log_file_name=$5

declare -a methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") #"Gson" 

for method in "${methods[@]}"; do
    for rp in {1..5}; do
        start=$(date +%s%N)
        SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                       -Dnrow=${nrow}\
                       -Dmethod=${method}\
                       -cp ./SerializationJava.jar at.tugraz.experiments.DataRead${platform}
                "
        echo $SCRIPT
        if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
        fi
        $SCRIPT
        end=$(date +%s%N)
        echo ${method}"Java,Java,"${task_set}",Total,"${platform}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
    done
done    

