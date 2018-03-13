  I have implemented the Shared-Memory Sort application using Java and measured its performance on single node of the below mentioned instances.
1)	i3.large
2)	i3.4xlarge
I have used multi-threading , (1-2 and 4 ) threads in i3.large and 2 threads in i3.4xlarge and measured the time to sort application on 128 GB and 1TB in the respective instances mentioned in the requirement.

          Sort is an application which sorts a file-resident dataset,it should be able to sort datasets that are larger than memory. I’ve developed java code ,it runs  on any machine. But I did performance evaluation must be done on Amazon EC2 on a “i3.large” instance. And Measured the time to execute the Sort application on the 128GB dataset produced with the Gensort on 1 node.,Varied the number of threads from 1 to 4,evaluated the best performance. For 1 TB we have run the code for 4 threads .



In My Sharedmemorycode,Initially i am reading input file  which is generated using gensort and reads the number of threads to run the sort.Based on the number of threads,work will be shared across the threads.and divide the inputfile into chuncks.Then We sort each chunkAfter sorting each file, i am merging all the intermediate outfiles into one output file.now i am  taking last system time after sorting.Then i am doing valsort on outputfile and reading first 10 lines and last 10 lines of output file.

Procedure to run the Sharedmemory code for 128 GB:
1.Create an instance in AWS Console and download the private key and a ppk private key via PuttyGen and use he Public DNS name , user name and the ppk file generated to connect to the instance.
2. Basic initial config.
sudo apt-get update
sudo apt-get install mdadm

3.Creating File System
lsblk
sudo file -s /dev/nvme0n1
sudo mkfs -t ext4 /dev/nvme0n1
sudo mkdir /data
sudo mount /dev/nvme0n1 /data

4. Java installables
sudo apt-get install default-jdk
java -version
sudo apt-get install ant

5.Generate Dataset
wget http://www.ordinal.com/try.cgi/gensort-linux-1.5.tar.gz
tar -xvf gensort-linux-1.5.tar.gz
cd 64
./gensort -a 1367122448 /data/input


6.Run the program:
javac SharedMemory.java SortingChunk.java
java -Xmx12g SharedMemory

Validation of Output:
7.Add the permission for valsort. 
Chmod 777 valsort
8.Run the Following command to validate the output file.
./valsort /data/sortedFile
9.Take the first 10 lines of outputfile by,
Head -10 /data/sortedFile
10.Take the flast 10 lines of outputfile by,
tail -10 /data/sortedFile


Procedure to run the Sharedmemory code for 1TB( We have performed the analysis for 1 TB + GB):
1.Create an instance in AWS Console and download the private key and a ppk private key via PuttyGen and use he Public DNS name , user name and the ppk file generated to connect to the instance.

2. Basic initial config.
sudo apt-get update
sudo apt-get install mdadm

3.Creating File System
lsblk
sudo mdadm --create --verbose /dev/md0 --level=0 --name=Cloud --raid-devices=2 /dev/nvme0n1 /dev/nvme1n1 
sudo mkfs.ext4 -L Cloud /dev/md0
sudo mkdir -p /data/raid
sudo mount LABEL=Cloud /data/raid


4. Java installables
sudo apt-get install default-jdk
java -version
sudo apt-get install ant

5.Generate Dataset
wget http://www.ordinal.com/try.cgi/gensort-linux-1.5.tar.gz
tar -xvf gensort-linux-1.5.tar.gz
cd 64
./gensort -a 10801224480 /data/raid/input


6.Run the program:
javac SharedMemory.java SortingChunk.java
java -Xmx115g SharedMemory

Validation of Output:
7.Add the permission for valsort. 
Chmod 777 valsort
8.Run the Following command to validate the output file.
./valsort /data/raid/sortedFile
9.Take the first 10 lines of outputfile by,
Head -10 /data/raid/sortedFile
10.Take the flast 10 lines of outputfile by,
tail -10 /data/raid/sortedFile