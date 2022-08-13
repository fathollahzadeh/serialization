#!/bin/bash

inDataPath=$1
outDataPath=$2
nrow=$3

declare -a methods=("Default" "Json+Gzip" "Bson" "ProtoBuf" "Kryo" "ByteBuffer" "Json" "FlatBuffers") #"Gson" 

for method in "${methods[@]}"; do
    for rp in {1..1}; do
        SCRIPT="$jnCMD -DinDataPath=${inDataPath}\
                       -DoutDataPath=${outDataPath}.${method}Java\
                       -Dnrow=${nrow}\
                       -Dmethod=${method}\
                       -cp ./SerializationJava.jar at.tugraz.experiments.DataWriteSingle
                "
        echo $SCRIPT
        time $SCRIPT
    done
done    

