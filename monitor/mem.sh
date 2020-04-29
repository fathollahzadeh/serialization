#!/bin/bash
filename="_$1"
mkdir -p "../monitor/monitordata"
log_file="../monitor/monitordata/mem_$filename.csv"
rm -rf $log_file	
total="$(free -m | grep Mem | tr -s ' ' | cut -d ' ' -f 2)"
echo $total
 
while :
do
DATE=`date +"%H:%M:%S:%s%:z"`
#var="$(top -b -n 1| grep -w $experiment_name | tr -s ' ' | cut -d ' ' -f 11)"
var="$(free -m | grep Mem | tr -s ' ' | cut -d ' ' -f 3)"

#sum=0.0
#for i in $var
#	do	
#	sum=$(echo "${sum} + ${i}" | bc)
#	done 


echo "$DATE,$total,$var">>$log_file

sleep 1
done
