/**
 * @file   tty.c
 * @author mengdemao <mengdemao19951021@163.com>
 * @date   Fri Dec 11 11:18:32 2020
 *
 * @brief
 *
 *
 */

#define pr_fmt(fmt) "tty: " fmt

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/bcd.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kfifo.h>
#include <linux/tty.h>
#include <linux/sched/signal.h>

#include <kversion.h>
#include "tty.h"

#define PTRACE		pr_err("%s\r\n", __func__)

struct tty_private_device {
	struct class *mclass;		/* 设备类 */
	struct cdev mcdev;			/* cdev */
	const char *name;			/* 设备名称 */
	dev_t major;				/* 主设备号 */
	struct ftty_private_struct *ftty_private_queue;		/* 异步结构体 */
};

#define TTY_PRIVATE_NAME		"tty_private_test"
#define TTY_PRIVATE_MAJOR		0
#define TTY_PRIVATE_NR		1
#define TTY_PRIVATE_SIZE		1024

struct tty_private_device tty_private_device = {
	.name  = TTY_PRIVATE_NAME,
	.major = TTY_PRIVATE_MAJOR,
};

static ssize_t tty_private_write(struct file *file, const char __user *data,
				   size_t len, loff_t *ppos)
{
	PTRACE;
	return 0;
}

static ssize_t tty_private_read(struct file *file, char __user *buf,
				  size_t len, loff_t * ppos)
{
	PTRACE;
	return 0;
}

static int tty_private_open(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static int tty_private_release(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static loff_t tty_private_llseek(struct file *file, loff_t offset, int origin)
{
	PTRACE;
	return 0;
}

static const struct file_operations tty_private_ops = {
	.owner   = THIS_MODULE,
	.write   = tty_private_write,
	.read    = tty_private_read,
	.open    = tty_private_open,
	.release = tty_private_release,
	.llseek  = tty_private_llseek,
};

static int __init tty_private_init(void)
{
	int ret = 0;
	dev_t devid;
	PTRACE;

	/* get the divice id */
	if (tty_private_device.major) {
		devid = MKDEV(tty_private_device.major, 0);
		ret = register_chrdev_region(devid, TTY_PRIVATE_NR, tty_private_device.name);
	} else {
		ret = alloc_chrdev_region(&devid, 0, TTY_PRIVATE_NR, tty_private_device.name);
		tty_private_device.major = MAJOR(devid);
	}

	/* create device class */
	tty_private_device.mclass = class_create(THIS_MODULE, tty_private_device.name);

	/* device_create */
	device_create(tty_private_device.mclass, NULL, MKDEV(tty_private_device.major, 0), NULL, tty_private_device.name, 0);

	/* init cdev */
	cdev_init(&tty_private_device.mcdev, &tty_private_ops);

	/* cdev add */
	cdev_add(&tty_private_device.mcdev, MKDEV(tty_private_device.major, 0), 1);

	return ret;
}

static void __exit tty_private_exit(void)
{
	PTRACE;
	device_destroy(tty_private_device.mclass, MKDEV(tty_private_device.major, 0));
	class_destroy(tty_private_device.mclass);
	unregister_chrdev_region(MKDEV(tty_private_device.major, 0), TTY_PRIVATE_NR);
}

module_init(tty_private_init);
module_exit(tty_private_exit);

MODULE_DESCRIPTION("Tty_Private Tetst Driver");
MODULE_ALIAS("kmodule:tty_private test");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
