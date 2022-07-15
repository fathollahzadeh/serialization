#!/bin/bash

cd data
wget https://storage.googleapis.com/tweets_1m/tweets.zip

sudo apt-get install zip -y
unzip tweets.zip
