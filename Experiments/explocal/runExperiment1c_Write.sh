#!/bin/bash

inDataPath=$1
outDataPath=$2
nrow=$3
platform=$4
task_set=$5
log_file_name=$6

declare -a methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") #"Gson" 

#declare -a methods=("Default")

for method in "${methods[@]}"; do
    for rp in {1..1}; do
        start=$(date +%s%N)
        SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                       -DoutDataPath=${outDataPath}.${method}\
                       -Dnrow=${nrow}\
                       -Dplatform=${platform}\
                       -Dmethod=${method}\
                       -cp ./SerializationJava.jar at.tugraz.experiments.DataWrite${platform}
                "
        echo $SCRIPT
        if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
        fi
        $SCRIPT
        end=$(date +%s%N)
        echo ${method}"Java,Java,"${task_set}",total,"${platform}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
    done
done    

