#ifndef ROOTEST_H
#define ROOTEST_H

#include <linux/kernel.h>
#include <linux/kprobes.h>

// Fonctions de test kprobes
int kprobes_init(void);
void kprobes_exit(void);
int kprobe_handler(struct kprobe *p, struct pt_regs *regs);

#endif //ROOTEST_H

