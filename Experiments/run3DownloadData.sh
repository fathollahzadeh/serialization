#!/bin/bash

#Kia's Storage:
#https://utcs378.s3.amazonaws.com/tweets_15M_rows.txt.lzo
#https://utcs378.s3.amazonaws.com/tweets_1M_rows.txt.bz2
#sudo apt-get install -y lzop

#pip install gdown
#gdown https://drive.google.com/uc?id=1ZrsgJ_f2gXTBzAgA6vVq_S2mcopHtpv6

rm -rf data/*.txt
cd data
wget https://utcs378.s3.amazonaws.com/tweets_1M_rows.txt.bz2
# wget https://storage.googleapis.com/tweets_1m/random_lists.zip


bzip2 -d tweets_1M_rows.txt.bz2
# unzip random_lists.zip
# mv random_lists/*.dat .

# duplicate data
mv tweets_1M_rows.txt tweets_1m.txt
cd ..

SCRIPT="$jnCMD -DinDataPath=data/tweets_1m.txt\
               -DoutDataPath=data/tweets.txt\
               -Dcount=5\
               -cp ./SerializationJava.jar at.tugraz.experiments.DataDuplicate
                "          
echo $SCRIPT
time $SCRIPT