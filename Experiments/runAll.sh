#!/bin/bash

# clean original results
rm -rf results
mkdir -p results

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export NETWORKCONFIG='conf/machines.inf'
export jCMD="java -Xms25g -Xmx25g -Xmn200m --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export jnCMD="java -Xms12g -Xmx12g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export cppValgrind="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt"

#./run1SetupDependencies.sh
./run2SetupSerialization.sh
#./run3DownloadData.sh
./run4PrepareData.sh
./run5LocalExperiments.sh
#./run5LocalExperimentsExternalSort.sh
#./run6NetworkExperiments.sh



#cssh -l saeed 35.184.204.129 34.170.33.92 35.188.121.177 35.202.155.192 34.68.33.71 35.239.44.13 35.225.167.22
