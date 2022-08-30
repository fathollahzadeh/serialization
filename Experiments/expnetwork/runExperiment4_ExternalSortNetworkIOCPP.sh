#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
plan=$4
log_file_name=$5

IP=$(hostname -I)
IP="${IP%%*( )}

for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="./cppbin/DataReadNetworkNetworkIO ${inDataPath} ${outDataPath} ${method} ${NETWORKCONFIG} ${plan}"
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo ${method}"CPP,CPP,IO,"${plan}","${IP}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    