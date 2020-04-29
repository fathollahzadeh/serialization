#!/bin/bash
experiment_name=$1
filename="_$2"
mkdir -p "../monitor/monitordata"
log_file="../monitor/monitordata/cpu_$filename.csv"
rm -rf $log_file	
 
while :
do
DATE=`date +"%H:%M:%S:%s%:z"`
#echo -n "$DATE," | tee -a $log_file
var="$(top -b -n 1| grep -w $experiment_name | tr -s ' ' | cut -d ' ' -f 10)"

sum=0.0
for i in $var
	do	
	sum=$(echo "${sum} + ${i}" | bc)
	done 


echo "$DATE,$sum">>$log_file
#echo "scale=3;$sum"| bc|tee -a $log_file
sleep 1
done
