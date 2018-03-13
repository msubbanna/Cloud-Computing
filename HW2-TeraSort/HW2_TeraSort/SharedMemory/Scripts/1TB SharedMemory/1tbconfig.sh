echo "Configuration Settings"
sudo apt-get update
sudo apt-get install mdadm

echo "Creating file system"
lsblk
sudo mdadm --create --verbose /dev/md0 --level=0 --name=Cloud --raid-devices=2 /dev/nvme0n1 /dev/nvme1n1 
sudo mkfs.ext4 -L Cloud /dev/md0
sudo mkdir -p /data/raid
sudo mount LABEL=Cloud /data/raid

echo "Installing Java Installables"
sudo apt-get install default-jdk
java -version
sudo apt-get install ant

echo " Generating data"
wget http://www.ordinal.com/try.cgi/gensort-linux-1.5.tar.gz
tar -xvf gensort-linux-1.5.tar.gz
cd 64
./gensort -a 10801224480 /data/raid/input

echo "Running the Program"
javac SharedMemory.java SortingChunk.java
java -Xmx115g SharedMemory

echo "Validating the output"
./valsort /data/raid/sortedFile

