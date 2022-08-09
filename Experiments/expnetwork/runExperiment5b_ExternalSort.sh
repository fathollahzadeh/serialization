#!/bin/bash

inDataPath=$1
outDataPath=$2
task_set=$3
log_file_name=$4



declare -a methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers")

for method in "${methods[@]}"; do
    for rp in {1..1}; do
        start=$(date +%s%N)
        SCRIPT="$jnCMD -DinDataPath=${inDataPath}\
                       -DoutDataPath=${outDataPath}.${method}Java\
                       -Dmethod=${method}\
                       -Dconfig=${NETWORKCONFIG}\
                       -cp ./SerializationJava.jar at.tugraz.experiments.DataReadNetwork
                "
        echo $SCRIPT
        if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
        fi
        time $SCRIPT
        end=$(date +%s%N)
        echo ${method}"Java,Java,"${task_set}",Total,"$((($end - $start) / 1000000)) >>results/$log_file_name.dat
        
    done
done    
