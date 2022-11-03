#!/bin/bash

# clean original results
rm -rf results
mkdir -p results
mkdir -p data
mkdir -p data/tmp

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export NETWORKCONFIG='conf/machines.inf'
export jCMD="java -Xms12g -Xmx12g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export jnCMD="java -Xms12g -Xmx12g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export cppValgrind="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt"

#./run1SetupDependencies.sh
#./run2SetupSerialization.sh
#./run3DownloadData.sh
#./run4PrepareData.sh
./run5LocalExperiments.sh
#./run5LocalExperimentsExternalSort.sh
#./run6NetworkExperiments.sh


#cssh -l saeed 34.171.107.137 35.224.45.21 34.121.118.248 35.232.102.201 35.202.158.180 34.171.204.131 34.136.129.1 
# GC: SSD add commands:
#sudo mdadm --create /dev/md0 --level=0 --raid-devices=2 /dev/nvme0n1 /dev/nvme0n2
#sudo mkfs.ext4 -F /dev/md0
#sudo mkdir -p /mnt/ssd
#sudo mount /dev/md0 /mnt/ssd
#sudo chmod a+w /mnt/ssd
#echo UUID=`sudo blkid -s UUID -o value /dev/md0` /mnt/ssd ext4 discard,defaults,nofail 0 2 | sudo tee -a /etc/fstab
#cat /etc/fstab



#######################################3
#drwxr-xr-x 3 root root 4,0K Okt 31 03:06 tweets
# -rw-r--r-- 1 root root 6,3G Nov  2 15:43 tweets.BsonJava
# -rw-r--r-- 1 root root  12M Nov  2 15:43 tweets.BsonJava.index
# -rw-r--r-- 1 root root 3,0G Nov  2 15:46 tweets.ByteBufferJava
# -rw-r--r-- 1 root root  12M Nov  2 15:46 tweets.ByteBufferJava.index
# -rw-r--r-- 1 root root 6,0G Nov  2 15:38 tweets.DefaultJava
# -rw-r--r-- 1 root root  12M Nov  2 15:38 tweets.DefaultJava.index
# -rw-r--r-- 1 root root 3,8G Nov  2 15:50 tweets.FlatBuffersJava
# -rw-r--r-- 1 root root  12M Nov  2 15:50 tweets.FlatBuffersJava.index
# -rw-r--r-- 1 root root 1,6G Nov  2 15:41 tweets.Json+GzipJava
# -rw-r--r-- 1 root root  12M Nov  2 15:41 tweets.Json+GzipJava.index
# -rw-r--r-- 1 root root 5,3G Nov  2 15:49 tweets.JsonJava
# -rw-r--r-- 1 root root  12M Nov  2 15:49 tweets.JsonJava.index
# -rw-r--r-- 1 root root 2,5G Nov  2 15:45 tweets.KryoJava
# -rw-r--r-- 1 root root  12M Nov  2 15:45 tweets.KryoJava.index
# -rw-r--r-- 1 root root 2,5G Nov  2 15:44 tweets.ProtoBufJava
# -rw-r--r-- 1 root root  12M Nov  2 15:44 tweets.ProtoBufJava.index