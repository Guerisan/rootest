#!/bin/sh

# Chemin pour compiler le kernel
dossier_kernel="/home/dooc/Documents/Cours/Kernel/TP2/linux"

# Chemin du fichier disk.img
dossier_image="/home/dooc/Documents/Cours/Kernel/TP2"

# Chemin du répertoire temporaire
dossier_temp="/tmp/my-rootfs"
sudo umount "$dossier_temp"
sudo losetup -d /dev/loop0

# Vérification de l'existence du répertoire temporaire
if [ ! -d "$dossier_temp" ]; then
    mkdir "$dossier_temp"
fi

# Vérification du répertoire pour la compilation du kernel
if [ ! -d "$dossier_kernel" ]; then
    echo "Erreur : Le répertoire pour la compilation du kernel n'existe pas."
    exit 1
fi

# Vérification du fichier disk.img
if [ ! -f "$dossier_image/disk.img" ]; then
    echo "Erreur : Le fichier disk.img n'existe pas dans le bon dossier."
    exit 1
fi

# Compilation du kernel
if ! make -C "$dossier_kernel" -j$(nproc); then
    echo "Erreur : Échec de la compilation du kernel."
    exit 1
fi

# Configuration du loopback et montage du disque image
echo "Configuration du loopback et montage du disque image"
sudo losetup -Pf "$dossier_image/disk.img"
sudo mount /dev/loop0p1 "$dossier_temp"

# Copie de l'image du kernel compilé dans le système de fichiers monté
echo "Copie de l'image du kernel compilé dans le système de fichiers monté"
sudo cp "$dossier_kernel/arch/x86/boot/bzImage" "$dossier_temp/boot/vmlinuz"

echo "Copie des scripts"
sudo cp -r "./test" "$dossier_temp/root"

#Démontage du système de fichiers et suppression du périphérique loopback
echo "Démontage du système de fichiers et suppression du périphérique loopback"
sudo umount "$dossier_temp"
sudo losetup -d /dev/loop0

read rd
qemu-system-x86_64 -hda disk.img -nographic
