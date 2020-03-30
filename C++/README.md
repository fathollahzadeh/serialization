Experiments on Complex Object Models and Serialization with C++
-

Requirements and dependencies
--
C++ implementation has been compiled, built, and tested in Ubuntu 18.04 LTS. For the system to work properly, make sure the following requirements are satisfied.
Dependencies

Library/Software
--
### 1. install C++ :
* clang and clang++ version 6.0
    ```bash 
    sudo apt-get install clang

### 2. install ubuntu rapid json:
* rapid-json
    ```bash 
    $ sudo apt-get install rapidjson-dev 
### 3. install libboost:
* download last version of boost from this link: https://www.boost.org/users/download/
* follow bellow steps for install from source(tested version 1_72):
   ```bash 
     $ tar -xvzf boost_1_72_0.tar.gz  
     $ cd boost_1_72_0
     $ ./bootstrap.sh --prefix=/usr/
     $ ./b2
     $ sudo ./b2 install
  ```
### 4.install google protobuf
To build protobuf from source, the following tools are needed:
* autoconf
* automake
* libtool
* make
* g++
* unzip

On Ubuntu/Debian, you can install them with:
```bash 
$ sudo apt-get install autoconf automake libtool curl make g++ unzip
```
To get the source, download one of the release .tar.gz or .zip packages in the release page:
(download .cpp version)
```bash 
https://github.com/protocolbuffers/protobuf/releases/latest
```

To build and install the C++ Protocol Buffer runtime and the Protocol Buffer compiler (protoc) execute the following:

extract .tar.gz file and cd to source folder:
```bash 
    $ ./configure
    $ make
    $ make check
    $ sudo make install
    $ sudo ldconfig # refresh shared library cache.
```

### 5. install C++ BSON: Installing the mongocxx driver
The official url for install MongoDB driver is here: http://mongocxx.org/mongocxx-v3/installation/

* Step 1: Install the latest version of the MongoDB C driver.
    - you will need to download and build from the source code. Get a tarball from the C Driver releases page.
    ```bash 
    https://github.com/mongodb/mongo-c-driver/releases
    ```
  - Follow the instructions for building from a tarball at Installing libmongoc.
  ```bash
  $ tar xzf mongo-c-driver-x.y.z.tar.gz
  $ cd mongo-c-driver-x.y.z
  $ mkdir cmake-build
  $ cd cmake-build
  $ cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
  $ sudo make install
  ```
* Step 2: Download the latest version of the mongocxx driver.
    - get source from this link: 
    ```bash
    https://github.com/mongodb/mongo-cxx-driver/releases
  ```
    - extract the source and goto to the build path:
    ```bash
    $ tar -xzf r3.4.1.tar.gz
    $ cd mongo-cxx-driver-r3.4.1/build
  ```
* Step 3: Configure the driver
 
On Unix systems, libmongoc installs into /usr/local by default. Without additional configuration, mongocxx installs into its local build directory as a courtesy to those who build from source. To configure mongocxx for installation into /usr/local as well, use the following cmake command:
```bash
cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local
``` 
* Step 4: Build and install the driver
```bash
make && sudo make install
```

How to compile and run benchmarks?
--
#### Step 1: download tweet data and store it in a path:

A sample of tweets data available in bellow link. This data is in text format and each line is a complete tweet in json format:
 ``` bash
https://metcs777.s3.amazonaws.com/tweets_1M_rows.txt.bz2
```

####  Step 2: compile the project:

Run this bash script for compile the project:
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
* HandCoded serialization:
    - serialization_1.se
    - serialization_1.se.index
* InPlace serialization:
    - serialization_2.se
    - serialization_2.se.index
* Boost serialization:
    - serialization_3.se
    - serialization_3.se.index
* ProtoBuf serialization:
    - serialization_4.se
    - serialization_4.se.index
* BSON serialization:
    - serialization_5.se
    - serialization_5.se.index
#### Step 4: run the experiments:
##### 4.1) Read object experiments:
This experiment include sequential and random read serialized objects,
so make sure generated enough list of objects in the Step 3. 
For random read, before run the experiment we need to generate random lists and
save it in a text files. For generate random list you can run this script:
```bash
$ ./twitterGenerateRandomList.sh {maximum/value/in/list} {number/of/random/data} {out/path}
``` 
for example:
```bash
$ ./twitterGenerateRandomList.sh 1000 100 /mnt/randomlist
```
we create 100 random number from 0 to maximum number 1000 in "/mnt/randomlist/randomlist_100.txt"

Now, we are ready for run the read object experiment. 
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
    for i in 1 2 3 4 #5
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
result_cpp_readobjects_1000_1.txt
result_cpp_readobjects_1000_2.txt
result_cpp_readobjects_1000_3.txt
result_cpp_readobjects_1000_4.txt
result_cpp_readobjects_1000_5.txt
```
example of result content:
```bash
language#method#seq#datatype#iotime#totaltime
[ReadTimeCPP]#HANDCODED#true#TweetStatus#0.00435849#0.0122351
[ReadTimeCPP]#HANDCODED#false#TweetStatus#0.0387502#0.0465473
[ReadTimeCPP]#INPLACE#true#TweetStatus#0.00817438#0.00825829
[ReadTimeCPP]#INPLACE#false#TweetStatus#0.0464583#0.0467077
[ReadTimeCPP]#BOOST#true#TweetStatus#0.00483162#0.0443216
[ReadTimeCPP]#BOOST#false#TweetStatus#0.0347336#0.0802113
[ReadTimeCPP]#PROTOBUF#true#TweetStatus#0.00424887#0.0189199
[ReadTimeCPP]#PROTOBUF#false#TweetStatus#0.0361407#0.0526357
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
 result_cpp_readobjects_1000_1.txt
 result_cpp_readobjects_1000_2.txt
 result_cpp_readobjects_1000_3.txt
 result_cpp_readobjects_1000_4.txt
 result_cpp_readobjects_1000_5.txt
 ```
 example of result content:
 ```bash
 language#method#seq#datatype#iotime#totaltime
 [ReadTimeCPP]#HANDCODED#true#TweetStatus#0.00206699#0.0318655
 [ReadTimeCPP]#INPLACE#true#TweetStatus#0.00447328#0.0239138
 [ReadTimeCPP]#BOOST#true#TweetStatus#0.00159802#0.160149
 [ReadTimeCPP]#PROTOBUF#true#TweetStatus#0.00173092#0.0518689
 ```

 