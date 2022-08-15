#!/bin/bash

# prepare data for Java experiments

# cleanup
rm -rf data/tweets.jbin
rm -rf data/tweets.jbin.index

rm -rf data/tweets.cbin
rm -rf data/tweets.cbin.index

inDataPath="data/tweets.txt"
outDataPathJava="data/tweets.jbin"
outDataPathCPP="data/tweets.cbin"
nrow=$(sed -n '$=' $inDataPath)

# SCRIPT="$jnCMD  -DinDataPath=${inDataPath}\
#                 -DoutDataPath=${outDataPathJava}\
#                 -Dnrow=${nrow}\
#                 -cp ./SerializationJava.jar at.tugraz.experiments.DataPrepare
#         "
# echo $SCRIPT
# time $SCRIPT

# prepare data for C++ experiments

SCRIPT="./cppbin/DataPrepare ${inDataPath} ${outDataPathCPP} ${nrow}"
echo $SCRIPT
time $SCRIPT



# prepare data for Rust experiments