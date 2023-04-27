#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/random.h>

#define CHRDEV_NAME "catgirl"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Maddy <me@vivi.zone>");
MODULE_DESCRIPTION("meow");
MODULE_VERSION("0.0");

static char nonsense[16][8] = {
    "meow",
    "mrow",
    "mew",
    "mewo",
    "mrao",
    "mraow",
    "nya",
    "nyan",
    "mya",
    "prrr",
    "mrrp",
    "mrrrp",
    "mrrrrp",
    "miao",
    "miaow",
    "mlem",
};

static int major;

static ssize_t read_catgirl(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    size_t written = 0;
    while (count > 8)
    {
        char *s = nonsense[get_random_u8() % 16];
        size_t len = strnlen(s, 8);

        if (copy_to_user(buf, s, len))
            return -EFAULT;

        count -= len;
        written += len;
    }

    return written;
}

static ssize_t write_catgirl(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    return count;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read_catgirl,
    .write = write_catgirl,
};

static int __init init_catgirl(void)
{
    major = register_chrdev(0, CHRDEV_NAME, &fops);

    printk(KERN_INFO "meow (%d)", major);
    return 0;
}

static void __exit exit_catgirl(void)
{
    unregister_chrdev(major, CHRDEV_NAME);

    printk(KERN_INFO "mrao!?");
}

module_init(init_catgirl);
module_exit(exit_catgirl);
