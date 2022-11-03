#!/bin/bash

declare -a servers=("34.171.107.137" "35.224.45.21" "34.121.118.248" "35.232.102.201" "35.202.158.180") 

for server in "${servers[@]}"; do
    path="archive/externalsort/${server}"
    mkdir -p "archive/externalsort/${server}"
    scp "saeed@$server:/mnt/ssd/serialization/Experiments/results/*.dat" $path
    scp "saeed@$server:/mnt/ssd/serialization/Experiments/nohup.out" $path

done
