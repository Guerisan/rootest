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

