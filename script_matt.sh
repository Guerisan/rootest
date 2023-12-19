#!/bin/bash

# Vérification si l'utilisateur est root
if [ "$EUID" -ne 0 ]
then
   echo "Veuillez exécuter ce script en tant que root ou avec sudo."
   exit 1
fi

sudo losetup -Pf /home/matt/Documents/ecole2600/2S1/ProjetRootKit/kernel_rootkit/disk_project/disk.img
mkdir -p /tmp/my-rootfs
sudo mount /dev/loop3p1 /tmp/my-rootfs
sudo cp rootest.ko /tmp/my-rootfs/
sudo umount /tmp/my-rootfs
sudo losetup -d /dev/loop3

qemu-system-x86_64 -hda /home/matt/Documents/ecole2600/2S1/ProjetRootKit/kernel_rootkit/disk_project/disk.img -nographic
