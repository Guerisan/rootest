# Kernel Driver (char driver)
Dans cette partie, le but est de créer un driver qui pourrait être utilisé par n'importe quel utilisateur du système pour lancer un code arbitraire.
## Mise en place du driver
Lorsque le driver est injecté alors il faudra lui donner les droits suivants :  
```bash
chmod og+rw /dev/graphics-control
```  
Cette commande permet au driver d'être utilisé par n'importe quel utilisateur.  

***Nom du driver*** : graphics-control  
***Class du driver*** : qemu-core  
***Résultat lsmod*** : kvm_amd 
## Utilisation du driver
```bash
echo "root" > /dev/graphics-control
```
L'orsque des informations sont écris dans le driver, la chaine envoyée est analysée.  
Si cette dernière est égle à la chaine "root" alors l'utilisateur deviendra root de la machine. 

