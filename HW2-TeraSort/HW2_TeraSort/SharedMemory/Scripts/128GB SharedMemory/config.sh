echo "Configuration Settings"
sudo apt-get update
sudo apt-get install mdadm

echo "Creating file system"
lsblk
sudo file -s /dev/nvme0n1
sudo mkfs -t ext4 /dev/nvme0n1
sudo mkdir /data
sudo mount /dev/nvme0n1 /data

echo "Installing Java Installables"
sudo apt-get install default-jdk
java -version
sudo apt-get install ant

echo " Generating data"
wget http://www.ordinal.com/try.cgi/gensort-linux-1.5.tar.gz
tar -xvf gensort-linux-1.5.tar.gz
cd 64
./gensort -a 1367122448 /data/input

echo "Running the Program"
javac SharedMemory.java SortingChunk.java
java -Xmx12g SharedMemory

echo "Validating the output"
./valsort /data/sortedFile



