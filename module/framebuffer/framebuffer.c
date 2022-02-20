/**
 * @file   framebuffer.c
 * @author mengdemao <mengdemao19951021@163.com>
 * @date   Fri Dec 11 11:18:32 2020
 *
 * @brief framebuffer driver
 *
 *
 */

#define pr_fmt(fmt) "framebuffer: " fmt

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
#include <linux/sched/signal.h>

#include <kversion.h>
#include "framebuffer.h"

#define PTRACE		pr_err("%s\r\n", __func__)

struct framebuffer_device {
	struct class *mclass;		/* 设备类 */
	struct cdev mcdev;			/* cdev */
	const char *name;			/* 设备名称 */
	dev_t major;				/* 主设备号 */
};

#define FRAMEBUFFER_NAME		"framebuffer_test"
#define FRAMEBUFFER_MAJOR		0
#define FRAMEBUFFER_NR			1
#define FRAMEBUFFER_SIZE		1024

struct framebuffer_device framebuffer_device = {
	.name  = FRAMEBUFFER_NAME,
	.major = FRAMEBUFFER_MAJOR,
};

static ssize_t framebuffer_write(struct file *file, const char __user *data,
				   size_t len, loff_t *ppos)
{
	PTRACE;
	return 0;
}

static ssize_t framebuffer_read(struct file *file, char __user *buf,
				  size_t len, loff_t * ppos)
{
	PTRACE;
	return 0;
}

static int framebuffer_open(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static int framebuffer_release(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static loff_t framebuffer_llseek(struct file *file, loff_t offset, int origin)
{
	PTRACE;
	return 0;
}

static const struct file_operations framebuffer_ops = {
	.owner   = THIS_MODULE,
	.write   = framebuffer_write,
	.read    = framebuffer_read,
	.open    = framebuffer_open,
	.release = framebuffer_release,
	.llseek  = framebuffer_llseek,
};

static int __init framebuffer_init(void)
{
	int ret = 0;
	dev_t devid;
	PTRACE;

	/* get the divice id */
	if (framebuffer_device.major) {
		devid = MKDEV(framebuffer_device.major, 0);
		ret = register_chrdev_region(devid, FRAMEBUFFER_NR, framebuffer_device.name);
	} else {
		ret = alloc_chrdev_region(&devid, 0, FRAMEBUFFER_NR, framebuffer_device.name);
		framebuffer_device.major = MAJOR(devid);
	}

	/* create device class */
	framebuffer_device.mclass = class_create(THIS_MODULE, framebuffer_device.name);

	/* device_create */
	device_create(framebuffer_device.mclass, NULL, MKDEV(framebuffer_device.major, 0), NULL, framebuffer_device.name, 0);

	/* init cdev */
	cdev_init(&framebuffer_device.mcdev, &framebuffer_ops);

	/* cdev add */
	cdev_add(&framebuffer_device.mcdev, MKDEV(framebuffer_device.major, 0), 1);

	return ret;
}

static void __exit framebuffer_exit(void)
{
	PTRACE;
	device_destroy(framebuffer_device.mclass, MKDEV(framebuffer_device.major, 0));
	class_destroy(framebuffer_device.mclass);
	unregister_chrdev_region(MKDEV(framebuffer_device.major, 0), FRAMEBUFFER_NR);
}

module_init(framebuffer_init);
module_exit(framebuffer_exit);

MODULE_DESCRIPTION("Framebuffer Tetst Driver");
MODULE_ALIAS("kmodule:framebuffer test");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
