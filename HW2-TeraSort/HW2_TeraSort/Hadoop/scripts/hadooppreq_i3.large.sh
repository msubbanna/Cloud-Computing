echo "Installing mdadm"
sudo apt-get update
sudo apt-get install mdadm


lsblk
sudo file -s /dev/nvme0n1
sudo mkfs -t ext4 /dev/nvme0n1
sudo mkdir /data
sudo mount /dev/nvme0n1 /data