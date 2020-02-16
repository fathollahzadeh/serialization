#!/usr/bin/env bash
# clean last cmake files and the run "make clean" and make
echo "start to compiling the project"
echo "------------------------------"
echo ""
./makeClean.sh

#define a name for project target
project_target="TwitterGenerateData"

#set number of repeats
number_of_repeats=10

#set data and out serialization files path
datapath="data/tweets_jsonline_1M.txt"
outpath="data/tweet_$number_of_repeats.txt"

echo "start to run the project"
echo "------------------------"
./bin/$project_target $datapath $outpath $number_of_repeats



