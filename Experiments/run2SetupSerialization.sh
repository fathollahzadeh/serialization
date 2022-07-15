#!/bin/bash

# compile Java baselines
cd ..
cd Java
mvn clean compile assembly:single
mv target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar ../Experiments/SerializationJava.jar

cd Experiments


# compile C++ baslelines

# compile Rust baselines
