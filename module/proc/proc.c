/*
 * @Author: your name
 * @Date: 2021-04-19 21:06:53
 * @LastEditTime: 2021-04-24 20:20:17
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /project/kmodule/7.proc/proc.c
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/version.h>

#include <kversion.h>

static int hello_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO"open\r\n");
	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO"close\r\n");
	return 0;
}

#if LINUX_VERSION_CODE <= KERNEL_VERSION(5, 0, 0)
static const struct file_operations hello_fops = {
	.open		= hello_open,
	.release	= hello_release,
};
#else
static const struct proc_ops hello_fops = {
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_open	= hello_open,
	.proc_release	= hello_release,
};
#endif

static struct proc_dir_entry *pe;

static int __init hello_init(void)
{
	printk(KERN_INFO"Hello Init\r\n");
	pe = proc_create("hello", 0444, NULL, &hello_fops);
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	proc_remove(pe);
	printk(KERN_INFO"Hello Exit\r\n");
}
module_exit(hello_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
