#!/bin/bash
mkdir -p data
mkdir -p data/tmp


#Kia's Storage:
#https://utcs378.s3.amazonaws.com/tweets_15M_rows.txt.lzo
#https://utcs378.s3.amazonaws.com/tweets_1M_rows.txt.bz2
#sudo apt-get install -y lzop

#pip install gdown
#gdown https://drive.google.com/uc?id=1ZrsgJ_f2gXTBzAgA6vVq_S2mcopHtpv6

# cd data
# rm -rf *
# wget https://storage.googleapis.com/tweets_1m/tweets.zip
# #wget https://storage.googleapis.com/tweets_1m/random_lists.zip


# sudo apt-get install zip -y
# unzip tweets.zip
# unzip random_lists.zip

# mv random_lists/*.dat .

# # duplicate data
# mv tweets.txt tweets_1m.txt
# cd ..

SCRIPT="$jnCMD -DinDataPath=data/tweets_1m.txt\
               -DoutDataPath=data/tweets.txt\
               -Dcount=10\
               -cp ./SerializationJava.jar at.tugraz.experiments.DataDuplicate
                "          
echo $SCRIPT
time $SCRIPT