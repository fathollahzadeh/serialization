#!/bin/bash

cd data
wget https://storage.googleapis.com/tweets_1m/tweets.zip
wget https://storage.googleapis.com/tweets_1m/random_lists.zip


sudo apt-get install zip -y
unzip tweets.zip
unzip random_lists.zip

# duplicate data

cd ..
SCRIPT="$jCMD  -DinDataPath=data/tweets_1m.txt\
               -DoutDataPath=data/tweets.txt\
               -cp ./SerializationJava.jar at.tugraz.experiments.DataDuplicate
                "          
    echo $SCRIPT
time $SCRIPT
