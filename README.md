<!-- Short description -->
<p align="center">
   Understanding Performance Implications of Complex Objects Implementations for Big Data Systems
</p>

<!-- Draw horizontal rule -->
<hr>


<!-- Table of content -->
|Section|Description|
| --- |---|
| [Installation](#installation) | Installing the dependencies |
| [Getting started](#getting-started) | A quick introduction on how to run benchmarks |
| [Experimental Results](#experimental_results) | An extensive overview of experimental results|
| [Citation](#referencing-tslearn) | A citation for scholarly articles |


## Installation
Our implementation has been compiled, built, and tested in Ubuntu 18.04 LTS. For the system to work properly, make sure the following requirements are satisfied.
### 1. C++
#### 1.1. Install C++ :
* Clang and clang++ version 6.0: `$sudo apt-get install clang`

#### 1.2. Install ubuntu rapid json:
* Rapid-json: `$ sudo apt-get install rapidjson-dev` 
#### 1.3. Install libboost:
* Download last version of `Boost` [`https://www.boost.org/users/download/`](https://www.boost.org/users/download/)
* Steps for install from source(`tested version 1_72`):
   ```bash 
     $ tar -xf boost_1_72_0.tar.bz2 
     $ cd boost_1_72_0
     $ ./bootstrap.sh --prefix=/usr/
     $ ./b2
     $ sudo ./b2 install
  ```
#### 1.4. Install google protobuf:
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
(download `.cpp` version)
```bash 
https://github.com/protocolbuffers/protobuf/releases/latest
```

To build and install the C++ Protocol Buffer runtime and the Protocol Buffer compiler (protoc) execute the following:

Extract `.tar.gz` file and cd to source folder:
```bash 
    $ ./configure
    $ make
    $ make check
    $ sudo make install
    $ sudo ldconfig # refresh shared library cache.
```

#### 1.5. Install C++ BSON:
The official url for install `MongoDB` driver available at [`http://mongocxx.org/mongocxx-v3/installation/`](http://mongocxx.org/mongocxx-v3/installation/)

* Step 1: Install the latest version of the `MongoDB C` driver:
    - You will need to download and build from the source code. Get a tarball from the C Driver releases page.
     [`https://github.com/mongodb/mongo-c-driver/releases`](https://github.com/mongodb/mongo-c-driver/releases)
    - Follow the instructions for building from a tarball at Installing `libmongoc`.
      ```bash
      $ tar xzf mongo-c-driver-x.y.z.tar.gz
      $ cd mongo-c-driver-x.y.z
      $ mkdir cmake-build
      $ cd cmake-build
      $ cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
      $ sudo make install
      ```
* Step 2: Download the latest version of the `mongocxx` driver:
    - Download source:[`https://github.com/mongodb/mongo-cxx-driver/releases`](https://github.com/mongodb/mongo-cxx-driver/releases) 
    - Extract the source and goto to the build path:
        ```bash
        $ tar -xzf r3.4.1.tar.gz
        $ cd mongo-cxx-driver-r3.4.1/build
        ```
* Step 3: Configure the driver:
    * On Unix systems, `libmongoc` installs into `/usr/local` by default. Without additional configuration, `mongocxx` installs into its local build directory as a courtesy to those who build from source. To configure `mongocxx` for installation into `/usr/local` as well, use the following cmake command:
        ```bash
        cmake ..                                \
            -DCMAKE_BUILD_TYPE=Release          \
            -DCMAKE_INSTALL_PREFIX=/usr/local
        ``` 
* Step 4: Build and install the driver:
    ```bash
    make && sudo make install
    ```
### 2. Java
#### 2.1 install Maven
* `python -m pip install tslearn`
    
#### 2.2 install JDK(1.8)
* Download Java SE 8u241 [`https://www.oracle.com/java/technologies/javase-downloads.html`](https://www.oracle.com/java/technologies/javase-downloads.html)
 
* Extract and move Java source:
    * Extract: `tar -xvf jdk-8u241-linux-x64.tar.gz`
    * Move: `sudo mv jdk1.8.0_241/ /usr/lib/jvm/`

* Install JDK 1.8:
    -     $ sudo update-alternatives --install "/usr/bin/java" "java" "/usr/lib/jvm/jdk1.8.0_241/bin/java" 1
          $ sudo update-alternatives --install "/usr/bin/javac" "javac" "/usr/lib/jvm/jdk1.8.0_241/bin/javac" 1
          $ sudo update-alternatives --install "/usr/bin/javaws" "javaws" "/usr/lib/jvm/jdk1.8.0_241/bin/javaws" 1


* Set JDK 1.8 as a default:
    * Choices a number for the alternative java: `$ sudo update-alternatives --config java`
    * Add to ```.bashrc``` file: `$ sudo nano ~/.bashrc`
    * Add bellow texts to the  ```.bashrc``` file:
        
            JAVA_HOME=/usr/lib/jvm/jdk1.8.0_241
            PATH=$PATH:$HOME/bin:$JAVA_HOME/bin
            export JAVA_HOME
            export JRE_HOME
            export PATH
    * Submit changes: `$ source ~/.bashrc`

* Test current Java version: `$ sudo java -version`
    * result:
    -       java version "1.8.0_241"
            Java(TM) SE Runtime Environment (build 1.8.0_241-b07)
            Java HotSpot(TM) 64-Bit Server VM (build 25.241-b07, mixed mode)


### 3. Rust
* Install the `Rust` and `Cargo` follow this link: [`https://www.rust-lang.org/tools/install`](https://www.rust-lang.org/tools/install):
    
## Getting started

#### 1. Download `Twitter` dataset:
A sample of `Twitter` dataset available in bellow link. This data is in text format and each line is a complete tweet in json format:

* Data Link: [`https://metcs777.s3.amazonaws.com/tweets_1M_rows.txt.bz2`](https://metcs777.s3.amazonaws.com/tweets_1M_rows.txt.bz2)

####  2. Compile the project:
There is a bash script in each subdirectories `C++`, `Java`, and `Rust`. Run the related bash script for compile the project:
* C++:`$./C++/makeClean.sh`
* Java:`$./Java/makeClean.sh`
* Rust:`$./Rust/makeClean.sh` 
 
## Experimental Results
####  1. Write object experiments:
This experiment include sequential write serialized objects.  One round of this experimentation need for next `Read Experiments`. We run all of our experiments 3 times and observed that the results have low variance. Run this script for write objects:
* C++: `$./C++/twitterSerialization.sh {path/to/data} {path/to/out/} {number/of/tweets/want/to/serialize}`
* Java: `$./Java/twitterSerialization.sh {path/to/data} {path/to/out/} {number/of/tweets/want/to/serialize}`
* Rust: `$./Rust/twitterSerialization.sh {path/to/data} {path/to/out/} {number/of/tweets/want/to/serialize}` 

Example:
```bash
./C++/twitterSerialization.sh /mnt/tweets_1M_rows.txt /mnt/cppdata 1000
```
The content of `twitterSerialization.sh` is:
* C++:
```
            for r in 1 2 3
            do
                for serialization_type in   1 2 3 4 5 6
                do
                    outpath="serialization_$serialization_type.se"
                    #clear the OS cache
                    echo 3 > /proc/sys/vm/drop_caches && sync
                    
                    #Run normal experiment 
                    time ./bin/TwitterSerialization $datapath $serialization_type $outpath $numberOfTweets $r 0
                    
                    # wait a short time for back to stable state
                    sleep 200
            
                    #clear the OS cache
                    echo 3 > /proc/sys/vm/drop_caches && sync
                   
                    # Run the experiment just on Core 0
                   time taskset -c 0 ./bin/TwitterSerialization $datapath $serialization_type $outpath $numberOfTweets $r 1
                done
            done
```
* Java: set `-XmsXg` `-XmxXg` based on your system configuration
```
            for r in 1 2 3
            do
                for serialization_type in   1 2 3 4 5 6 7 8
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
* Rust:
```
            for r in 1 2 3
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
After finish the serialization task in the out path(the second parameter) you can see the following files:

| # |C++|Java |Rust|
|---|--- |---|---|
|1|`HandCoded` <br> `serialization_1.[se, se.index]`|`Default` <br> `serialization_1.[se, se.index]`|`Json ` <br> `serialization_1.[se, se.index]`|
|2|`InPlace` <br> `serialization_2.[se, se.index]`|`Json+Gzip` <br> `serialization_2.[se, se.index]`|`Bincode` <br> `serialization_2.[se, se.index]`|
|3|`Boost` <br> `serialization_3.[se, se.index]`|`Bson` <br> `serialization_3.[se, se.index]`|`MessagePack` <br> `serialization_3.[se, se.index]`|
|4|`ProtoBuf`<br> `serialization_4.[se, se.index]` |`ProtoBuf` <br> `serialization_4.[se, se.index]`|`Bson` <br> `serialization_4.[se, se.index]`|
|5|`BSON` <br> `serialization_5.[se, se.index]`|`Kryo` <br> `serialization_5.[se, se.index]`|`FlexBuffers` <br> `serialization_5.[se, se.index]`|
|6|`FlatBuffers` <br> `serialization_6.[se, se.index]` |`Byte Buffer` <br> `serialization_6.[se, se.index]`|---|
|7|--- |`FlatBuffers` <br> `serialization_7.[se, se.index]`|---|
|8|--- |`Json` <br> `serialization_8.[se, se.index]`|---|

The experiment was based on 5 million data.The final log file results for write objects experiment available at the related path:
```bash
{project/path}/bin/benchmark/writeobjects
```
Example of files:
```bash
result_java_writeobjects_5000000_1.txt
result_java_writeobjects_5000000_2.txt
result_java_writeobjects_5000000_3.txt
```

Example of result content:
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

The table below present the all of the experiments results and distribution.

<table>  
  <tr>
    <td rowspan="3">Method</td>
    <td colspan="2">IO</td>
    <td colspan="2">Total</td>    
  </tr> 

  <tr>  
    <td colspan="2">Mean(SD)</td>
    <td colspan="2">Mean(SD)</td>    
  </tr>  
  <tr>
    <td >TS=True</td>
    <td >TS=False</td>
    <td >TS=True</td>
    <td >TS=False</td>   
  </tr>   
<tr><td>Java Default</td><td>57.22(10.24)</td><td>55.2(15.61)</td><td>583.85(30.24)</td><td>424.78(19)</td><td></td></tr>
<tr><td>Java Json+Gzip</td><td>25.11(3.03)</td><td>24.65(10.12)</td><td>2060.56(64.51)</td><td>1620.41(48.84)</td><td></td></tr>
<tr><td>Java Bson</td><td>83.42(3)</td><td>80.77(8.55)</td><td>847.16(57.89)</td><td>421.62(18.39)</td><td></td></tr>
<tr><td>Java ProtoBuf</td><td>40.38(4.4)</td><td>28.81(4.24)</td><td>313.46(14.86)</td><td>165.59(11.57)</td><td></td></tr>
<tr><td>Java Kryo</td><td>40.58(5.59)</td><td>31.27(4.5)</td><td>201.17(24.3)</td><td>122.54(4.84)</td><td></td></tr>
<tr><td>Java Byte Buffer</td><td>44.63(3.82)</td><td>37.75(2.64)</td><td>255.73(18.48)</td><td>139.94(6.06)</td><td></td></tr>
<tr><td>Java FlatBuffers</td><td>55.49(4.66)</td><td>44.62(1.46)</td><td>268.64(22.31)</td><td>176.81(5.38)</td><td></td></tr>
<tr><td>Java Json</td><td>61.19(4.59)</td><td>54.28(5.36)</td><td>1098.67(22.31)</td><td>985.71(12.14)</td><td></td></tr>
<tr><td>C++ HandCoded</td><td>28.12(5.71)</td><td>17.79(6.61)</td><td>56.32(6.11)</td><td>32.69(6.69)</td><td></td></tr>
<tr><td>C++ inPlace</td><td>42.99(4.66)</td><td>23.45(7.2)</td><td>79.36(5)</td><td>43.1(8.19)</td><td></td></tr>
<tr><td>C++ Boost</td><td>36.8(1.47)</td><td>17.35(3.67)</td><td>419.8(4.12)</td><td>210.31(7.3)</td><td></td></tr>
<tr><td>C++ ProtoBuf</td><td>29.24(5.94)</td><td>15.13(3.24)</td><td>164.62(6.74)</td><td>83.69(4.56)</td><td></td></tr>
<tr><td>C++ Bson</td><td>112.52(26.2)</td><td>66.91(10.83)</td><td>2345.63(28)</td><td>1195.31(12.21)</td><td></td></tr>
<tr><td>C++ FlatBuffers</td><td>40.07(6.13)</td><td>31.38(3.89)</td><td>111.62(6.16)</td><td>70.09(5.03)</td><td></td></tr>
<tr><td>Rust Json</td><td>22.17(1.65)</td><td>25.15(5.28)</td><td>103.41(2.39)</td><td>107.21(6.28)</td><td></td></tr>
<tr><td>Rust Bincode</td><td>13.09(2.14)</td><td>11.93(1.49)</td><td>44.51(2.28)</td><td>43.11(1.76)</td><td></td></tr>
<tr><td>Rust MessagePack</td><td>9.34(1.23)</td><td>8.89(1.08)</td><td>39.06(1.36)</td><td>39.29(1.67)</td><td></td></tr>
<tr><td>Rust Bson</td><td>27.5(3.59)</td><td>30.62(8.99)</td><td>457.23(3.63)</td><td>459.53(10.07)</td><td></td></tr>
<tr><td>Rust FlexBuffers</td><td>24.56(3.36)</td><td>21.35(3.65)</td><td>301.21(4)</td><td>297.82(2.22)</td><td></td></tr>
</table>




![Image of Yaktocat](images/write.png)

## Citation

