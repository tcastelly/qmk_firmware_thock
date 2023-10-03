#!/bin/bash
sudo umount /mnt/usb

./build-conundrum.sh

echo "prepare keyboard in dfu mode ..."
echo "in 3 seconds ..."
sleep 3

sudo mount /dev/sda /mnt/usb
sudo cp ./thock_conundrum_default.uf2 /mnt/usb
sudo umount /mnt/usb
