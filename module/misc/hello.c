/*
 * @Author: your name
 * @Date: 2021-04-23 11:21:13
 * @LastEditTime: 2021-04-24 17:44:35
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /project/kmodule/6.misc/hello.c
 */
#define pr_fmt(fmt) "misc: " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/dmaengine.h>
#include <linux/iova.h>
#include <linux/anon_inodes.h>
#include <linux/file.h>
#include <linux/vmalloc.h>
#include <kversion.h>

#define PTRACE				pr_err("%s\r\n", __func__)
#define HELLO_MISC_NAME		"hello_misc_test"
#define HELLO_MISC_MINOR	MISC_DYNAMIC_MINOR

static int hello_misc_open(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static int hello_misc_release(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

const struct file_operations hello_misc_fops = {
	.open = hello_misc_open,
	.release = hello_misc_release,
	.owner = THIS_MODULE,
};

/* 私有结构 */
struct hello_dev_private {
	struct miscdevice dev;
};

static struct hello_dev_private hello_dev_private = {
		.dev = {
		.minor = HELLO_MISC_MINOR,
		.name = HELLO_MISC_NAME,
		.fops = &hello_misc_fops,
	}
};

static int __init hello_init(void)
{
	PTRACE;
	misc_register(&hello_dev_private.dev);
	return 0;
}

static void __exit hello_exit(void)
{
	PTRACE;
	misc_deregister(&hello_dev_private.dev);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
MODULE_DESCRIPTION("misc driver test");
MODULE_ALIAS("misc:misc test");
