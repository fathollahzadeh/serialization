#!/bin/bash

method=$1
inDataPath=$2
outDataPath=$3
nrow=$4
SCRIPT="./cppbin/DataWriteSingle ${inDataPath} ${outDataPath} ${nrow} ${method}"
echo $SCRIPT
time $SCRIPT
