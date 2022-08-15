#!/bin/bash

# This script runs all network experiments on the cluster scale-up machines.
inDataPathMemoryJava="data/tweets.jbin"
inDataPathDiskJava="data/tweets"
outDataPath="data/tmp/tweets"
nrow=1000000

# Load data into memory
# 1.a Java enviroments
# write header to log file
##########################
echo "baseline,language,plan,machineip,time" >>results/Experiment4_ExternalSort_times.dat

# Serialize data into disk and keep it
./expnetwork/runExperiment4_Write.sh $inDataPathMemoryJava $outDataPath $nrow 

./expnetwork/runExperiment4_ExternalSort_Memory.sh $inDataPathMemoryJava $outDataPath m2m Experiment4_ExternalSort_times
./expnetwork/runExperiment4_ExternalSort_Memory.sh $inDataPathMemoryJava $outDataPath m2d Experiment4_ExternalSort_times

./expnetwork/runExperiment4_ExternalSort_Disk.sh $inDataPathDiskJava $outDataPath d2m Experiment4_ExternalSort_times
./expnetwork/runExperiment4_ExternalSort_Disk.sh $inDataPathDiskJava $outDataPath d2d Experiment4_ExternalSort_times

