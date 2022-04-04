#!/bin/bash

#sudo apt update
#sudo apt-get install openjdk-11-jdk-headless
#sudo apt install -y maven
#sudo apt install -y git
#export JAVA_HOME=/usr/lib/jvm/java-1.11.0-openjdk-amd64

# create an output directory for compiled results: Serialization.jar
rm -rf bin # clean-up
mkdir -p bin

###########################################################
### Java Environments: compile and build a runnable jar ###
##########################################################
cd ..
mvn clean compile assembly:single # compile Java source code
mv target/serialization-1.0-SNAPSHOT-jar-with-dependencies.jar experiments/bin/Serialization.jar
cd experiments

