#!/bin/bash

# setup Java dependencies
sudo apt update
sudo apt-get install -y openjdk-11-jdk-headless
sudo apt install -y maven
sudo apt install -y git
export JAVA_HOME=/usr/lib/jvm/java-1.11.0-openjdk-amd64

# setup C++ dependencies

# setup Rust dependencies
