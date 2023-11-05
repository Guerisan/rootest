# 2600 project Rootkit

## Arborescence :

Le module est compilé out-of-tree.
Le makefile considère l'arborescence suivante :

- kernel
   - modules
       - rootest/ <-- Repo git
- linux-5.15.131/ <-- Sources du noyaux
    

## Organisation du développpement :
- On peut écrire nos fonctions chacun dans un fichier séparé !
- Il n'y a qu'à compléter le fichier rootest.h, et l'importer dans nos fichiers de travail
- Puis appeler nos fonctions dans l'init du rootest_main.c
- Et enfin éditer le makefile pour rajouter notrefichier.o à la liste des `rootest-objs`

## Rendu :
   - Image QCOW2 avec : 
      - PDF de votre présentation
      - Documentation utilisateur et de conception de vos programmes
      - Sources codes
         - Sources C du rootkit
         - Makefiles
         - Scripts de fabrication de LFS

## To-Do : 
- Script de fabrication LFS
- Module stealth
- MakeFile
- Header

## Infos diverse :
- Votre LFS contiendra 2 comptes:
   - un compte root permettant de charger votre rootkit sous forme de fichier.ko
   - un compte user permettant de démontrer l’usage de votre rootkit via un/des programme(s) compagnon(s)
   - Les login/mdp des différents comptes seront donnés dans la documentation.
- Le code de votre rootkit devra respecter au maximum les consignes de l’ANSSI 
     concernant le développement sécurisé C Coding Standards concernant l’écriture du
     code C en terme de coding style. De plus, l’usage d’une langue différente de l’anglais
     pour les identifiants est proscrite.
- Vous êtes libres sur le langage de programmation utilisé pour votre/vos programme(s)
     compagnon(s), toutefois le respect de la coding style usuelle pour ce langage devra être
     respecté.
- Vous rendrez un rapport sur la conception et la mise en oeuvre de votre rootkit,
     détaillant vos choix et votre mise en oeuvre. 
