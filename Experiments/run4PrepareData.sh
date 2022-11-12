#!/bin/bash

# prepare data for Java experiments

# cleanup
rm -rf data/tweets.jbin
rm -rf data/tweets.jbin.index

rm -rf data/tweets.cbin
rm -rf data/tweets.cbin.index

rm -rf data/tweets.rbin
rm -rf data/tweets.rbin.index


inDataPath="data/tweets.txt"
outDataPathJava="data/tweets.jbin"
outDataPathCPP="data/tweets.cbin"
outDataPathRust="data/tweets.rbin"
nrow=$(sed -n '$=' $inDataPath)

# prepare data for Java experiments
##################################
# SCRIPT="$jnCMD  -DinDataPath=${inDataPath}\
#                 -DoutDataPath=${outDataPathJava}\
#                 -Dnrow=${nrow}\
#                 -cp ./SerializationJava.jar at.tugraz.experiments.DataPrepare
#         "
# echo $SCRIPT
# time $SCRIPT

# prepare data for C++ experiments
##################################
# SCRIPT="./cppbin/DataPrepare ${inDataPath} ${outDataPathCPP} ${nrow}"
# echo $SCRIPT
# time $SCRIPT

# prepare data for Rust experiments
##################################
SCRIPT="./rustbin/DataPrepare ${inDataPath} ${outDataPathRust} ${nrow}"
echo $SCRIPT
time $SCRIPT

#rm -rf ${inDataPath}