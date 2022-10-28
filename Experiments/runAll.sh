#!/bin/bash

# clean original results
rm -rf results
mkdir -p results
mkdir -p data
mkdir -p data/tmp

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export NETWORKCONFIG='conf/machines.inf'
export jCMD="java -Xms110g -Xmx110g -Xmn11g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export jnCMD="java -Xms28g -Xmx28g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export cppValgrind="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt"

#./run1SetupDependencies.sh
#./run2SetupSerialization.sh
#./run3DownloadData.sh
#./run4PrepareData.sh
#./run5LocalExperiments.sh
#./run5LocalExperimentsExternalSort.sh
#./_run6NetworkExperiments.sh  


# ./_run6NetworkExperiments.sh  server
# ./_run6NetworkExperiments.sh  m1
# ./_run6NetworkExperiments.sh  m2
# ./_run6NetworkExperiments.sh  l1
# ./_run6NetworkExperiments.sh  l2
# ./_run6NetworkExperiments.sh  l3
# ./_run6NetworkExperiments.sh  l4
