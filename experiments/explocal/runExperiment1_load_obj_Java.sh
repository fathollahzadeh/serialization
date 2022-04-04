#!/usr/bin/env bash

inputFile=data/$1
datasetName=$2
log_file_name=$3

start=$(date +%s%N)
SCRIPT="$jCMD -DinputFile=$inputFile\
              -DdatasetName=$datasetName\
              -cp ./bin/Serialization.jar at.tugraz.experiment.ExpSerializeLoadText"
$SCRIPT

end=$(date +%s%N)

echo "Java,"${datasetName}","$((($end - $start) / 1000000)) >>results/$log_file_name.dat

