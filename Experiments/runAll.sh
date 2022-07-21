#!/bin/bash

# clean original results
rm -rf results/*;
mkdir -p results;

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export NETWORKCONFIG='conf/machines.inf'
export jCMD="java -Xms60g -Xmx60g -Xmn7g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export jnCMD="java -Xms8g -Xmx8g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"


./run1SetupDependencies.sh
./run2SetupSerialization.sh
./run3DownloadData.sh
./run4PrepareData.sh
#./run5LocalExperiments.sh

./run6NetworkExperiments.sh
