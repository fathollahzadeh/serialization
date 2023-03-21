# Reproducibility Submission TKDE 2023
**Authors:** Saeed Fathollahzadeh, Kia Teymourian, Chris Jermaine

**Paper Name:** How Object Model and Its Implementation Impacts Performance of Big Data Systems: A Controlled Experimental Study

**Paper Links:** 
 * Link 
 * PDF

 **Source Code Info:**
 * Repository: serialization (https://github.com/fathollahzadeh/serialization)
 * Programming Language: C++, Java, Rust
 * Packages/Libraries Needed: OpenJDK, Clang++, Rust

**Dataset Used:**
* Twiter: <https://utcs378.s3.amazonaws.com/tweets_1M_rows.txt.bz2>

**Hardware and Software Info:** The experiments use both a scale-up, one-socket AMD server, and a scale-out cluster of 7 single-socket Intel servers:
 * Scale-up node: AMD EPYC 7302 CPU @ 3.0-3.3 GHz (16 physical/32 virtual cores) with 512KB, 8MB and 128MB
L1, L2 and L3 caches, and 128 GB DDR4 RAM (peak performance is 768 GFLOP/s, 183.2 GB/s).The OpenJDK
11 with 120 GB max and initial JVM heap sizes for Java 
* Scale-out cluster: 7 nodes, each a single on Google Cloud Platform using N2 Series which have 4
vCPU cores (Intel Cascade), 32 GB RAM, and 750 GB (2× 375 GB) local SSD (Sustained random IOPS limit:
read=340,000 and write=180,000). The OpenJDK 11 with 28 GB max and initial JVM heap sizes for Java based
implementations.

**Setup and Experiments:** The entire experimental evaluation can be run via `./runAll.sh`, which deletes the results and plots and performs setup, dataset download and preparation, local and distributed experiments, and plotting. However, for a more controlled evaluation, we recommend running the individual steps separately:

  ```bash
      ./run1SetupDependencies.sh
      ./run2SetupSerialization.sh
      ./run3DownloadData.sh
      ./run4PrepareData.sh
      ./run5LocalExperiments.sh # on scale-up node
      ./run5LocalExperimentsExternalSort.sh # on scale-up GC node
      ./run6NetworkExperiments.sh # on scale-out cluster
      ./run7LocalMemoryExperiments.sh # on scale-up node
   ```

**Last Update:** March 21, 2023 (first draft)



