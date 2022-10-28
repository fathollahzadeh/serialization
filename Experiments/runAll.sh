#!/bin/bash

# clean original results
rm -rf results
mkdir -p results
mkdir -p data
mkdir -p data/tmp

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export NETWORKCONFIG='conf/machines.inf'
export jCMD="java -Xms28g -Xmx28g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export jnCMD="java -Xms28g -Xmx28g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export cppValgrind="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt"

#./run1SetupDependencies.sh
#./run2SetupSerialization.sh
#./run3DownloadData.sh
./run4PrepareData.sh
#./run5LocalExperiments.sh
#./run5LocalExperimentsExternalSort.sh
./run6NetworkExperiments.sh
