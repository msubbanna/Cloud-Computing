
clear
echo "Installing mdadm"
sudo apt-get update
sudo apt-get install mdadm

echo "changing to raid 0" 
lsblk 
sudo mdadm --create --verbose /dev/md0 --level=0 --name=Cloud --raid-devices=2 /dev/nvme0n1 /dev/nvme1n1
 sudo mkfs.ext4 -L Cloud /dev/md0 
sudo mkdir -p /data/raid
sudo mount LABEL=Cloud /data/raid

echo "Installing Java"
sudo apt-get install default-jdk
java -version

echo "Installing ant"
sudo apt-get install ant
