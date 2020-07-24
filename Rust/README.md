Experiments on Complex Object Models and Serialization with Rust
--

This project contains our Rust implementation of the complex object experiments with different Rust serialization techniques.

Requirements and dependencies
--
Rust implementation has been compiled, built, and tested in Ubuntu 18.04 LTS. For the system to work properly, make sure the following requirements are satisfied.

Library/Software
--
- Install the ```Rust``` and ```Cargo``` from the following link:
    ```
     https://www.rust-lang.org/tools/install
    ```  

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
after finish the serialization task in the out path(second parameter) you can seed this files:
* Rust Json serialization:
    - serialization_1.se
    - serialization_1.se.index
* Rust Bincode serialization:
    - serialization_2.se
    - serialization_2.se.index
* Rust MessagePack serialization:
    - serialization_3.se
    - serialization_3.se.index
* Rust Bson serialization:
    - serialization_4.se
    - serialization_4.se.index
* Rust FlexBuffers serialization:
    - serialization_5.se
    - serialization_5.se.index

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
./twitterSerialization.sh /mnt/tweets_1M_rows.txt /mnt/rustdata/ 5000000
```
the content of "experimentReadObjects.sh" is here:
```bash
for r in 1 2 3 4 5
do
    for serialization_type in   1 2 3 4 5
    do
        outpath="serialization_$serialization_type.se"
        #clear the OS cache
        echo 3 > /proc/sys/vm/drop_caches && sync
        
        #Run normal experiment 
        time cargo run --release write  $datapath $serialization_type $outpath $numberOfTweets $r false
        
        # wait a short time for back to stable state
        sleep 200

        #clear the OS cache
        echo 3 > /proc/sys/vm/drop_caches && sync
       
        # Run the experiment just on Core 0
        time taskset -c 0 cargo run --release write  $datapath $serialization_type $outpath $numberOfTweets $r true

    done

done
```
this experiment for 5 million data.The final log file results for write objects experiment available in this path:
```bash
{project/path}/bin/benchmark/writeobjects
```
example of files :
```bash
result_rust_writeobjects_5000000_1.txt
result_rust_writeobjects_5000000_2.txt
result_rust_writeobjects_5000000_3.txt
result_rust_writeobjects_5000000_4.txt
result_rust_writeobjects_5000000_5.txt
```

example of result content:
```bash
language#taskset#method#seq#datatype#iotime#totaltime
[WriteTimeRUST]#false#Rust JSON#true#TweetStatus#0.043800448#5.087480759
[WriteTimeRUST]#false#Rust Bincode#true#TweetStatus#0.021813129#1.135830763
[WriteTimeRUST]#false#Rust MessagePack#true#TweetStatus#0.015977267#0.918014082
[WriteTimeRUST]#false#Rust BSON#true#TweetStatus#0.039370547#10.462070449
[WriteTimeRUST]#false#Rust FlexBuffers#true#TweetStatus#0.036733787#16.996779504
```
##### 4.2) Read object experiments:
This experiment include sequential and random read serialized objects,
so make sure generated enough list of objects in the 4.1. 
For random read, before run the experiment we need to generate random lists and
save it in a text files. We did this task in cpp section and the random list data 
shared between Java, Rust and C++ experiments.
 
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
    for i in 1 2 3 4 5
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
result_rust_readobjects_1000_1.txt
result_rust_readobjects_1000_2.txt
result_rust_readobjects_1000_3.txt
result_rust_readobjects_1000_4.txt
result_rust_readobjects_1000_5.txt
```
example of result content:
```bash
language#taskset#method#seq#datatype#iotime#totaltime
ReadTimeRUST]#true#Rust JSON#true#TweetStatus#0.295715293#3.887963551
[ReadTimeRUST]#false#Rust JSON#true#TweetStatus#0.296318291#3.8846211349999997
[ReadTimeRUST]#true#Rust JSON#false#TweetStatus#0.42120208#4.017401606
[ReadTimeRUST]#false#Rust JSON#false#TweetStatus#0.421007664#4.02515716
[ReadTimeRUST]#true#Rust Bincode#true#TweetStatus#0.286894705#1.7140592369999998
[ReadTimeRUST]#false#Rust Bincode#true#TweetStatus#0.302331565#1.801248409
...
[ReadTimeRUST]#false#Rust FlexBuffers#true#TweetStatus#0.297779089#5.8303231239999995
[ReadTimeRUST]#true#Rust FlexBuffers#false#TweetStatus#0.42355907#5.937440843
[ReadTimeRUST]#false#Rust FlexBuffers#false#TweetStatus#0.423004583#5.939485542
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
 result_rust_readobjects_1000_1.txt
 result_rust_readobjects_1000_2.txt
 result_rust_readobjects_1000_3.txt
 result_rust_readobjects_1000_4.txt
 result_rust_readobjects_1000_5.txt
 ```
 example of result content:
 ```bash
language#taskset#method#seq#datatype#iotime#totaltime
[ReadTimeRUST]#true#Rust JSON#true#TweetStatus#0.319199577#2.396015248
[ReadTimeRUST]#false#Rust JSON#true#TweetStatus#0.295386215#2.3142172739999998
[ReadTimeRUST]#true#Rust Bincode#true#TweetStatus#0.324854291#1.498018448
[ReadTimeRUST]#false#Rust Bincode#true#TweetStatus#0.327340715#1.580585109
[ReadTimeRUST]#true#Rust MessagePack#true#TweetStatus#0.34694686#1.623175985
[ReadTimeRUST]#false#Rust MessagePack#true#TweetStatus#0.29892823#1.508641467
[ReadTimeRUST]#true#Rust BSON#true#TweetStatus#0.318688665#6.020841073
[ReadTimeRUST]#false#Rust BSON#true#TweetStatus#0.300653901#5.991132305
[ReadTimeRUST]#true#Rust FlexBuffers#true#TweetStatus#0.289004725#2.899898598
[ReadTimeRUST]#false#Rust FlexBuffers#true#TweetStatus#0.300947986#3.133421802
 ```