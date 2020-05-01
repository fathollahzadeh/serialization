#!/bin/bash

#compile projects 

cd C++
./makeClean.sh
cd ../Java
./makeClean.sh

rawdatapath="/mnt/tweets_1M_rows.txt"
outdatapath="/mnt"
randomlistpath="/mnt/randomlist/"

cd ..

# start write experiment 

cd C++
./twitterSerialization.sh $rawdatapath "$outdatapath/cppdata/" 5000000

cd ../Java
./twitterSerialization.sh $rawdatapath "$outdatapath/javadata" 5000000

cd ..

# start run read experiments

cd C++
./experimentReadObjects.sh "$outdatapath/cppdata/" $randomlistpath
cd ../Java
./experimentReadObjects.sh "$outdatapath/javadata/" $randomlistpath

cd ..

# start run external sort experiments

cd C++
./experimentExternalSort.sh "$outdatapath/cppdata/" 10
cd ../Java
./experimentExternalSort.sh "$outdatapath/javadata/" 10





