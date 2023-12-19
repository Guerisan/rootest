#!/bin/bash

echo "Création du loopback device"
if sudo losetup -Pf disk.img; then
    echo "Loopback device créé avec succès."
else
    echo "Erreur lors de la création du loopback device."
    exit 1
fi

echo "Création du dossier /tmp/my-rootfs"
if mkdir -p /tmp/my-rootfs; then
    echo "Dossier /tmp/my-rootfs créé avec succès."
else
    echo "Erreur lors de la création du dossier /tmp/my-rootfs."
    exit 1
fi

echo "Montage /tmp/my-rootfs sur /dev/loop0p1"
if sudo mount /dev/loop0p1 /tmp/my-rootfs; then
    echo "Montage réussi."
else
    echo "Erreur lors du montage."
    exit 1
fi

echo "Copie du kernel dans l'image"
if sudo cp linux-5.15.131/arch/x86/boot/bzImage /tmp/my-rootfs/boot/vmlinuz; then
    echo "Copie du kernel réussie."
else
    echo "Erreur lors de la copie du kernel."
    exit 1
fi

echo "Suppression du dossier modules sur l'img"
if sudo rm -rf /tmp/my-rootfs/root/modules; then
    echo "Suppression du dossier modules réussie."
else
    echo "Erreur lors de la suppression du dossier modules."
    exit 1
fi

echo "Copie clean des modules"
if sudo cp -r ./modules /tmp/my-rootfs/root/; then
    echo "Copie des modules réussie."
else
    echo "Erreur lors de la copie des modules."
    exit 1
fi

echo "Démontage de /tmp/my-rootfs"
if sudo umount /tmp/my-rootfs; then
    echo "Démontage réussi."
else
    echo "Erreur lors du démontage."
    exit 1
fi

echo "Suppression du loopback device"
if sudo losetup -d /dev/loop0; then
    echo "Loopback device supprimé avec succès."
else
    echo "Erreur lors de la suppression du loopback device."
    exit 1
fi

echo "Suppression du dossier /tmp/my-rootfs"
if sudo rm -rf /tmp/my-rootfs; then
    echo "Dossier /tmp/my-rootfs supprimé avec succès."
else
    echo "Erreur lors de la suppression du dossier /tmp/my-rootfs."
    exit 1
fi

echo "Boot with : qemu-system-x86_64 -hda disk.img -nographic"

