#!/bin/bash

# clean original results
rm -rf results
mkdir -p results
mkdir -p data
mkdir -p data/tmp

rm -rf loging.log
export LOG4JPROP='conf/log4j.properties'
export NETWORKCONFIG='conf/machines.inf'
export jCMD="java -Xms28g -Xmx28g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export jnCMD="java -Xms28g -Xmx28g -Xmn2g --illegal-access=deny -Dlog4j.configuration=file:$LOG4JPROP"
export cppValgrind="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt"

#./run1SetupDependencies.sh
#./run2SetupSerialization.sh
#./run3DownloadData.sh
./run4PrepareData.sh
#./run5LocalExperiments.sh
#./run5LocalExperimentsExternalSort.sh
#./run6NetworkExperiments.sh
./run9LocalMemoryExperiments.sh


#cssh -l saeed 34.23.27.219 34.27.164.78 104.154.191.10 34.105.17.180 34.118.194.218 35.235.83.248 35.236.57.101


# GC: SSD add commands:
#sudo mdadm --create /dev/md0 --level=0 --raid-devices=2 /dev/nvme0n1 /dev/nvme0n2
#sudo mkfs.ext4 -F /dev/md0
#sudo mkdir -p /mnt/ssd
#sudo mount /dev/md0 /mnt/ssd
#sudo chmod a+w /mnt/ssd
#echo UUID=`sudo blkid -s UUID -o value /dev/md0` /mnt/ssd ext4 discard,defaults,nofail 0 2 | sudo tee -a /etc/fstab
#cat /etc/fstab
