#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/file.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HOOOKING");
MODULE_AUTHOR("Professor Jack");



static int kprobe_handler(struct kprobe *p, struct pt_regs *regs) {
    printk(KERN_INFO "kprobe_handler triggered\n");
    return 0;
}

/*
static int kprobe_handler(struct kprobe *p, struct pt_regs *regs) {
    struct file *file = (struct file *)regs->di; // DI register contient généralement le premier argument de la fonction sur x86_64

    if (file && file->f_path.dentry && file->f_path.dentry->d_name.name) {
        if (strcmp(file->f_path.dentry->d_name.name, "plop") == 0) {
          printk(KERN_INFO "PLOP PLOP\n");
        }
    }
    return 0;
}
*/
static struct kprobe kp = {
    .symbol_name = "vfs_open", // Par exemple, pour surveiller l'ouverture de fichiers
    .pre_handler = kprobe_handler,
};

static int __init kprobe_init(void) {
    int ret;

    ret = register_kprobe(&kp);
    if (ret < 0) {
        printk(KERN_INFO "register_kprobe failed: %d\n", ret);
        return ret;
    }

    printk(KERN_INFO "kprobe registered\n");
    return 0;
}

static void __exit kprobe_exit(void) {
    unregister_kprobe(&kp);
    printk(KERN_INFO "kprobe unregistered\n");
}

module_init(kprobe_init);
module_exit(kprobe_exit);

