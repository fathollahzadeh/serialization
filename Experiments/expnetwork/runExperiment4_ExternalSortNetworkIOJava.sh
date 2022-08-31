#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
plan=$4
log_file_name=$5

IP=$(hostname -I)
IP="${IP%%*( )}"

for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="$jnCMD -DinDataPath=${inDataPath}\
                   -DoutDataPath=${outDataPath}\
                   -Dplan=${plan}\
                   -Dmethod=${method}\
                   -Dconfig=${NETWORKCONFIG}\
                   -cp ./SerializationJava.jar at.tugraz.experiments.DataReadNetworkIO
           "
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo ${method}"Java,Java,IO,"${plan}","${IP}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done     