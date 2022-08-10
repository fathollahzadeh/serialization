#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
outDataPath="data/tmp/tweets"

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo baseline,language,taskset,platform,plan,machineip,time >>results/runExperiment5b_ExternalSort.dat

./expnetwork/runExperiment5b_ExternalSort.sh $inDataPathJava $outDataPath m2m false Experiment5_LoadToMemory_times
./expnetwork/runExperiment5b_ExternalSort.sh $inDataPathJava $outDataPath m2d false Experiment5_LoadToMemory_times
./expnetwork/runExperiment5b_ExternalSort.sh $inDataPathJava $outDataPath d2m false Experiment5_LoadToMemory_times
./expnetwork/runExperiment5b_ExternalSort.sh $inDataPathJava $outDataPath d2d false Experiment5_LoadToMemory_times

