Experiments on Complex Object Models and Serialization with Java
--

This project contains our java implementation of the complex object experiments with different java serialization techniques.

Requirements and dependencies
--
Java implementation has been compiled, built, and tested in Ubuntu 18.04 LTS. For the system to work properly, make sure the following requirements are satisfied.


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

     result:
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
* Java FlatBuffers serialization:
    - serialization_7.se
    - serialization_7.se.index
#### Step 4: run the experiments:
##### 4.1) Write object experiments:
This experiment include sequential write serialized objects.
One round of this experimentation need for next "Read Experiments".
We run all of our experiments 5 times and observed that the results have low variance.
Run this script for write objects:
```bash
$ sudo ./twitterSerialization.sh {path/to/raw/file} {path/to/output} {number/of/tweets/want/to/serialize}
```
for example:
```bash
./twitterSerialization.sh /mnt/tweets_1M_rows.txt /mnt/javadata/ 5000000
```
the content of "experimentReadObjects.sh" is here:
```bash
for r in 1 2 3 4 5
do
    for serialization_type in   1 2 3 4 5 6 7
    do
        outpath="serialization_$serialization_type.se"
        #clear the OS cache
        echo 3 > /proc/sys/vm/drop_caches && sync
        
        #Run normal experiment 
        time java   -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms4g -Xmx7g -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.DataSerialization $datapath $serialization_type $outpath $numberOfTweets $r false
        
        # wait a short time for back to stable state
        sleep 200

        #clear the OS cache
        echo 3 > /proc/sys/vm/drop_caches && sync
       
        # Run the experiment just on Core 0
        time taskset -c 0 java   -XX:-UseGCOverheadLimit -XX:+UseConcMarkSweepGC -Xms4g -Xmx7g -cp  ./target/Twitter-1.0-SNAPSHOT-jar-with-dependencies.jar edu.bu.benchmarks.DataSerialization $datapath $serialization_type $outpath $numberOfTweets $r true

    done

done
```
this experiment for 5 million data.The final log file results for write objects experiment available in this path:
```bash
{project/path}/bin/benchmark/writeobjects
```
example of files :
```bash
result_java_writeobjects_5000000_1.txt
result_java_writeobjects_5000000_2.txt
result_java_writeobjects_5000000_3.txt
result_java_writeobjects_5000000_4.txt
result_java_writeobjects_5000000_5.txt
```

example of result content:
```bash
language#taskset#method#seq#datatype#iotime#totaltime
[WriteTimeJAVA]#false#Java Default#true#TweetStatus#46.533803422#402.846320084
[WriteTimeJAVA]#true#Java Default#true#TweetStatus#57.150347609#548.940365011
[WriteTimeJAVA]#false#Java Json+Gzip#true#TweetStatus#17.098395421#1589.679004718
[WriteTimeJAVA]#true#Java Json+Gzip#true#TweetStatus#28.520531689#2014.750860796
...
[WriteTimeJAVA]#false#Java FlatBuffers#true#TweetStatus#45.86361197#171.276057655
[WriteTimeJAVA]#true#Java FlatBuffers#true#TweetStatus#53.48092523#254.482728354
```
##### 4.2) Read object experiments:
This experiment include sequential and random read serialized objects,
so make sure generated enough list of objects in the 4.1. 
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
the content of "experimentReadObjects.sh" is here:
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
language#taskset#method#seq#datatype#iotime#totaltime
[ReadTimeJAVA]#true#Java Default#true#TweetStatus#23.798836036#352.906722848
[ReadTimeJAVA]#false#Java Default#true#TweetStatus#18.159668422#165.313603375
[ReadTimeJAVA]#true#Java Default#false#TweetStatus#1572.860794899#1921.952341106
[ReadTimeJAVA]#false#Java Default#false#TweetStatus#1546.022621157#1708.930474179
...
[ReadTimeJAVA]#true#Java FlatBuffers#true#TweetStatus#12.389147518#27.126166431
[ReadTimeJAVA]#false#Java FlatBuffers#true#TweetStatus#12.793152134#20.527560654
[ReadTimeJAVA]#true#Java FlatBuffers#false#TweetStatus#960.76642819#980.017399323
[ReadTimeJAVA]#false#Java FlatBuffers#false#TweetStatus#936.032555176#947.904076846
```
##### 4.3) External sort experiments:
Make sure generated enough list of objects in the Step 3. 
e run all of our experiments 5 times and observed that the results have low variance.
Run this script for read objects. This script include both sequential and random read:
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
language#taskset#method#seq#datatype#iotime#totaltime
[ReadTimeJAVA]#true#Java Default#true#TweetStatus#10216.984410636001#152753.422
[ReadTimeJAVA]#true#Java FlatBuffers#true#TweetStatus#4312.255638584#89578.700841005
[ReadTimeJAVA]#true#Java Byte Buffer#true#TweetStatus#4978.641430961001#98795.474594109
[ReadTimeJAVA]#true#Java ProtoBuf#true#TweetStatus#4242.381662146#99885.152843346
[ReadTimeJAVA]#true#Java Bson#true#TweetStatus#11536.926679607#168239.949147106
[ReadTimeJAVA]#true#Java Json+Gzip#true#TweetStatus#3851.4960500650004#189387.954780967
 ```