#!/bin/bash

inDataPath=$1
nrow=$2
platform=$3
task_set=$4
log_file_name=$5


# write header to log file
if [ "$task_set" = false ] ; then
  echo "baseline,language,taskset,execution,platform,time" >>results/$log_file_name.dat
fi

declare -a methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") #"Gson" 

for method in "${methods[@]}"; do
    for rp in {1..1}; do
        start=$(date +%s%N)
        SCRIPT="$jCMD  -DinDataPath=${inDataPath}\
                       -Dnrow=${nrow}\
                       -Dplatform=${platform}\
                       -Dmethod=${method}\
                       -cp ./SerializationJava.jar at.tugraz.experiments.DataSerialization${platform}
                "
        echo $SCRIPT
        if [ "$task_set" = true ] ; then
            SCRIPT="taskset -c 0 $SCRIPT"
        fi
        $SCRIPT
        end=$(date +%s%N)
        echo ${method}"Java,Java,"${task_set}",CPU,"${platform}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
    done
done    

