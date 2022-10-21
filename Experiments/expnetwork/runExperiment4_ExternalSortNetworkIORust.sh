#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
plan=$4
log_file_name=$5

IP=$(hostname -I)
IP="${IP%%*( )}"

echo 3 > /proc/sys/vm/drop_caches && sync
sleep 100

for rp in {1..1}; do
    start=$(date +%s%N)
    SCRIPT="./rustbin/DataReadNetworkIO ${inDataPath} ${outDataPath} ${method} ${NETWORKCONFIG} ${plan}"
    echo $SCRIPT
    time $SCRIPT
    end=$(date +%s%N)
    echo ${method}"Rust,Rust,IO,"${plan}","${IP}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat
done    