#!/bin/bash

# This script runs all local experiments on the specified scale-up machine.
inDataPathJava="data/tweets.jbin"
outDataPath="data/tmp/tweets"

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo baseline,language,plan,machineip,time >>results/Experiment4_ExternalSort_times.dat

./expnetwork/runExperiment4_ExternalSort.sh $inDataPathJava $outDataPath m2m Experiment4_ExternalSort_times
./expnetwork/runExperiment4_ExternalSort.sh $inDataPathJava $outDataPath m2d Experiment4_ExternalSort_times
./expnetwork/runExperiment4_ExternalSort.sh $inDataPathJava $outDataPath d2m Experiment4_ExternalSort_times
./expnetwork/runExperiment4_ExternalSort.sh $inDataPathJava $outDataPath d2d Experiment4_ExternalSort_times

