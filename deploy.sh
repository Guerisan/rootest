echo "Création les lo"
sudo losetup -Pf disk.img

echo "Création du dossier /tmp/my-rootfs"
mkdir -p /tmp/my-rootfs

echo "Mount /tmp/-my-rootfs sur /dev/loop0p1"
sudo mount /dev/loop0p1 /tmp/my-rootfs

echo "Copie du kernel dans l'image"
sudo cp linux-5.15.131/arch/x86/boot/bzImage /tmp/my-rootfs/boot/vmlinuz

echo "Suppression du dossier modules sur l'img"
sudo rm -rf /tmp/my-rootfs/root/modules

echo "Copie clean des modules"
sudo cp -r ./modules /tmp/my-rootfs/root/

echo "Démontage de /tmp/my-rootfs"
sudo umount /tmp/my-rootfs

echo "Supression du répertoire lo"
sudo losetup -d /dev/loop0

echo "Suppression du dossier rootfs"
sudo rm -rf /tmp/my-rootfs

echo "Boot with : qemu-system-x86_64 -hda disk.img -nographic"
