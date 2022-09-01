#!/bin/bash

# clean original results
rm -rf results
mkdir -p results

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export NETWORKCONFIG='conf/machines.inf'
export jCMD="java -Xms120g -Xmx120g -Xmn11g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export jnCMD="java -Xms15g -Xmx15g -Xmn3g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"

#./run1SetupDependencies.sh
#./run2SetupSerialization.sh
./run3DownloadData.sh
#./run4PrepareData.sh
#./run5LocalExperiments.sh
#./run5LocalExperimentsExternalSort.sh
#./run6NetworkExperiments.sh

