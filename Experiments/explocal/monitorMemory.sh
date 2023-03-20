#!/bin/bash

log_file_name=$1

total="$(free -m | grep Mem | tr -s ' ' | cut -d ' ' -f 2)"
 
while :
    do
        DATE=`date +"%H:%M:%S:%s%:z"`
        var="$(free -m | grep Mem | tr -s ' ' | cut -d ' ' -f 3)"

    echo "$DATE,$total,$var">>$log_file

    sleep 1
done