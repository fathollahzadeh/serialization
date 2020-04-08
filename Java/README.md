Experiments on Complex Object Models and Serialization with Java
--

This project contains our java implementation of the complex object experiments with different java serialization techniques.

Requirements and dependencies
--
Java implementation has been compiled, built, and tested in Ubuntu 18.04 LTS. For the system to work properly, make sure the following requirements are satisfied.
Dependencies

Library/Software
--
### 1. install Maven
    $ sudo apt-get install maven
    
### 2. install JDK(1.8)
* download Java SE 8u241 from this link:
    -       https://www.oracle.com/java/technologies/javase-downloads.html
    
* extract and move Java source:

    -       $ tar -xvf jdk-8u241-linux-x64.tar.gz
            $ sudo mv jdk1.8.0_241/ /usr/lib/jvm/

* install JDK 1.8:

    -       $ sudo update-alternatives --install "/usr/bin/java" "java" "/usr/lib/jvm/jdk1.8.0_241/bin/java" 100
            $ sudo update-alternatives --install "/usr/bin/javac" "javac" "/usr/lib/jvm/jdk1.8.0_241/bin/javac" 100
            $ sudo update-alternatives --install "/usr/bin/javaws" "javaws" "/usr/lib/jvm/jdk1.8.0_241/bin/javaws" 100


* set JDK 1.8 as a default:
    - choices a number for the alternative java:
    -      $ sudo update-alternatives --config java

    - add to ```.bashrc``` file:
     -      $ sudo nano ~/.bashrc

    - add bellow texts to the  ```.bashrc``` file:
    
            JAVA_HOME=/usr/lib/jvm/jdk1.8.0_241
            PATH=$PATH:$HOME/bin:$JAVA_HOME/bin
            export JAVA_HOME
            export JRE_HOME
            export PATH
    - submit changes:
     -      $ source ~/.bashrc

* test current Java version:
-       $ sudo java -version

    - result:
-       java version "1.8.0_241"
        Java(TM) SE Runtime Environment (build 1.8.0_241-b07)
        Java HotSpot(TM) 64-Bit Server VM (build 25.241-b07, mixed mode)

How to compile and run benchmarks?
--
#### Step 1: download tweet data and store it in a path:

A sample of tweets data available in bellow link. This data is in text format and each line is a complete tweet in json format:
 ``` bash
https://metcs777.s3.amazonaws.com/tweets_1M_rows.txt.bz2
```

####  Step 2: compile the project:

To compile the project and create a single jar file with all dependencies:
 ``` bash
./makeClean.sh
```
####  Step 3: serialize data for experiment:
```bash
./twitterSerialization.sh {path/to/data} {path/to/out/} {number/of/tweets/want/to/serialize}
```
for example:
```bash
./twitterSerialization.sh /mnt/tweets_1M_rows.txt /mnt/cppdata 1000
```
after finish the serialization task in the out path(parameter two) you can seed this files:
* Java Default serialization:
    - serialization_1.se
    - serialization_1.se.index
* Java Json serialization:
    - serialization_2.se
    - serialization_2.se.index
* Java Bson serialization:
    - serialization_3.se
    - serialization_3.se.index
* Java ProtoBuf serialization:
    - serialization_4.se
    - serialization_4.se.index
* Java Kryo serialization:
    - serialization_5.se
    - serialization_5.se.index
* Java Byte Buffer serialization:
    - serialization_6.se
    - serialization_6.se.index
#### Step 4: run the experiments:
##### 4.1) Read object experiments:
This experiment include sequential and random read serialized objects,
so make sure generated enough list of objects in the Step 3. 
For random read, before run the experiment we need to generate random lists and
save it in a text files. We did this task in cpp section and the random list data 
shared between Java and C++ experiments.
 
We run all of our experiments 5 times and observed that the results have low variance.
Run this script for read objects. This script inclode both sequential and random read:
```bash
$ sudo ./experimentReadObjects.sh {path/to/serialized/data} {path/to/randomlist}
```
for example:
```bash
$ sudo ./experimentReadObjects.sh /mnt/serialized_data/cppdata1000 /mnt/randomlist
```
the contect of "experimentReadObjects.sh" is here:
```bash
#!/usr/bin/env bash
data_path=$1
random_list_path=$2
# for round:
for r in 1 2 3 4 5
do
    # for serialization types:
    for i in 1 2 3 4 5 6
    do
        #for number of objects:
        for n in  1000000 2000000 3000000 4000000 5000000
        do
        ./twitterSequentialRead.sh $i $n $r $data_path
        sleep 200
        ./twitterRandomRead.sh $i $n $r $data_path $random_list_path
        sleep 200
        done
    done
done
```

this experiment prepared for 1 million to 5 million data, so if you want to change number of read objects 
just change inner for loop.

Finally, the final log file results for read object experiment available in this path:
```bash
{project/path}/bin/benchmark/readobjects
```
example of files :
```bash
result_java_readobjects_1000_1.txt
result_java_readobjects_1000_2.txt
result_java_readobjects_1000_3.txt
result_java_readobjects_1000_4.txt
result_java_readobjects_1000_5.txt
```
example of result content:
```bash
language#method#seq#datatype#iotime#totaltime
[ReadTimeJAVA]#Java Default#true#TweetStatus#0.002910177#0.53175854
[ReadTimeJAVA]#Java Default#true#TweetStatus#0.002811223#0.530201562
[ReadTimeJAVA]#Java Default#false#TweetStatus#0.059467179#0.431964925
[ReadTimeJAVA]#Java Json#true#TweetStatus#0.001006207#0.49057253
[ReadTimeJAVA]#Java Json#false#TweetStatus#0.021903647#0.378536125
[ReadTimeJAVA]#Java Bson#true#TweetStatus#0.008939544#2.269378632
[ReadTimeJAVA]#Java Bson#false#TweetStatus#0.06538651#2.157031023
[ReadTimeJAVA]#Java ProtoBuf#true#TweetStatus#9.46014E-4#0.412552214
[ReadTimeJAVA]#Java ProtoBuf#false#TweetStatus#0.018210505#0.326047429
[ReadTimeJAVA]#Java Kryo#true#TweetStatus#8.85481E-4#0.327833103
[ReadTimeJAVA]#Java Kryo#false#TweetStatus#0.011504063#0.223180498
[ReadTimeJAVA]#Java Byte Buffer#true#TweetStatus#9.52354E-4#0.29042324
[ReadTimeJAVA]#Java Byte Buffer#false#TweetStatus#0.021162836#0.20620445
```
##### 4.2) External sort experiments:
Make sure generated enough list of objects in the Step 3. 
e run all of our experiments 5 times and observed that the results have low variance.
Run this script for read objects. This script inclode both sequential and random read:
```bash
$ sudo ./experimentExternalSort.sh {path/to/serialized/data} {number/of/splites}
```
for example:
```bash
$ sudo ./experimentExternalSort.sh /mnt/serialized_data/cppdata1000 20
```
in this script we run external sort and split the large files to 20 parts.
Finally, the final log file results for read object experiment available in this path:
 ```bash
 {project/path}/bin/benchmark/externalsort
 ```
 example of files :
 ```bash
 result_java_readobjects_1000_1.txt
 result_java_readobjects_1000_2.txt
 result_java_readobjects_1000_3.txt
 result_java_readobjects_1000_4.txt
 result_java_readobjects_1000_5.txt
 ```
 example of result content:
 ```bash
 language#method#seq#datatype#iotime#totaltime
 [ReadTimeJAVA]#Java Default#true#TweetStatus#0.065219451#2.133305723
 [ReadTimeJAVA]#Java Json#true#TweetStatus#0.016413406#3.760303266
 [ReadTimeJAVA]#Java Bson#true#TweetStatus#0.060226151#13.398960503
 [ReadTimeJAVA]#Java ProtoBuf#true#TweetStatus#0.029981841#1.446549824
 [ReadTimeJAVA]#Java Kryo#true#TweetStatus#0.025616975#0.772949934
 [ReadTimeJAVA]#Java Byte Buffer#true#TweetStatus#0.031267013#0.7274486
 ```