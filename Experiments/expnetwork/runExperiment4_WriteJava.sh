#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
nrow=$4

SCRIPT="$jnCMD -DinDataPath=${inDataPath}\
               -DoutDataPath=${outDataPath}.${method}Java\
               -Dnrow=${nrow}\
               -Dmethod=${method}\
               -cp ./SerializationJava.jar at.tugraz.experiments.DataWriteSingle
        "
echo $SCRIPT
time $SCRIPT
