#!/bin/bash

# clean original results
rm -rf results/*;
mkdir -p results;

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export jCMD="java -Xms30g -Xmx30g -Xmn4g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"


#./run2SetupSerialization.sh
#./run4PrepareData.sh
./run5LocalExperiments.sh
