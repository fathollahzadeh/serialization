#!/bin/bash

declare -a servers=("34.170.156.248" "35.232.213.107" "34.69.16.90" "34.172.80.69" "34.134.20.134" "34.122.31.144" "34.173.159.86") 

src="/home/saeed/serialization"
src_exp="$src/Experiments"
src_data="$src/Experiments/data"

for server in "${servers[@]}"; do
    echo ">>>>>>>>>>>>>>>> $server"
    ssh $server "rm -rf $src_data/*"
    ssh $server "mkdir -p $src_data/tmp"     
    ssh -n -f $server "sh -c 'cd $src/Experiments && nohup ./runAll.sh > nohup.out 2>&1 &'"    
    
done

