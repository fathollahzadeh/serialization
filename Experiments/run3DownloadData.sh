#!/bin/bash

cd data
rm -rf *
wget https://storage.googleapis.com/tweets_1m/tweets.zip
wget https://storage.googleapis.com/tweets_1m/random_lists.zip


sudo apt-get install zip -y
unzip tweets.zip
unzip random_lists.zip

mv random_lists/*.dat .
# duplicate data
head -100000 tweets.txt > tweets_1m.txt
rm -rf tweets.txt

#mv tweets.txt tweets_1m.txt
cd ..
SCRIPT="$jnCMD  -DinDataPath=data/tweets_1m.txt\
               -DoutDataPath=data/tweets.txt\
               -cp ./SerializationJava.jar at.tugraz.experiments.DataDuplicate
                "          
echo $SCRIPT
time $SCRIPT