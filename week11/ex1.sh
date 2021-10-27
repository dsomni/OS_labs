fallocate -l 50MB ./lofs.img
sudo losetup /dev/loop0 ./lofs.img
mkfs -t ext4 ./lofs.img
mkdir ./lofsdisk
sudo mount -t ext4 /dev/loop0 ./lofsdisk
sudo chown -R dsomni ./lofsdisk
chmod a+rwx ./lofsdisk