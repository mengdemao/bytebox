/**
 * @file   async.c
 * @author mengdemao <mengdemao19951021@163.com>
 * @date   Fri Dec 11 11:18:32 2020
 *
 * @brief
 *
 *
 */

#define pr_fmt(fmt) "async: " fmt

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
#include <linux/async.h>
#include <linux/sched/signal.h>

#include <kversion.h>
#include "async.h"

#define PTRACE		pr_err("%s\r\n", __func__)

struct async_device {
	struct class *mclass;		/* 设备类 */
	struct cdev mcdev;			/* cdev */
	const char *name;			/* 设备名称 */
	dev_t major;				/* 主设备号 */
	struct fasync_struct *fasync_queue; 	/* 异步结构体 */
};

#define ASYNC_NAME		"async_test"
#define ASYNC_MAJOR		0
#define ASYNC_NR		1
#define ASYNC_SIZE		1024

struct async_device async_device = {
	.name  = ASYNC_NAME,
	.major = ASYNC_MAJOR,
};

static ssize_t async_write(struct file *file, const char __user *data,
				   size_t len, loff_t *ppos)
{
	PTRACE;
	if (async_device.fasync_queue != NULL) {
		kill_fasync(&async_device.fasync_queue, SIGIO, POLL_IN);	// 发送信号
		pr_debug("kill_fasync");
	}
	return 0;
}

static ssize_t async_read(struct file *file, char __user *buf,
				  size_t len, loff_t * ppos)
{
	PTRACE;
	return 0;
}

static int async_open(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static int async_release(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static loff_t async_llseek(struct file *file, loff_t offset, int origin)
{
	PTRACE;
	return 0;
}

static int async_fasync(int fd, struct file *file, int mode)
{
	PTRACE;
	fasync_helper(fd, file, mode, &async_device.fasync_queue);	// 类似于注册信号
	return 0;
}

static const struct file_operations async_ops = {
	.owner   = THIS_MODULE,
	.write   = async_write,
	.read    = async_read,
	.open    = async_open,
	.release = async_release,
	.llseek  = async_llseek,
	.fasync	 = async_fasync,
};

static int __init async_init(void)
{
	int ret = 0;
	dev_t devid;
	PTRACE;

	/* get the divice id */
	if (async_device.major) {
		devid = MKDEV(async_device.major, 0);
		ret = register_chrdev_region(devid, ASYNC_NR, async_device.name);
	} else {
		ret = alloc_chrdev_region(&devid, 0, ASYNC_NR, async_device.name);
		async_device.major = MAJOR(devid);
	}

	/* create device class */
	async_device.mclass = class_create(THIS_MODULE, async_device.name);

	/* device_create */
	device_create(async_device.mclass, NULL, MKDEV(async_device.major, 0), NULL, async_device.name, 0);

	/* init cdev */
	cdev_init(&async_device.mcdev, &async_ops);

	/* cdev add */
	cdev_add(&async_device.mcdev, MKDEV(async_device.major, 0), 1);

	return ret;
}

static void __exit async_exit(void)
{
	PTRACE;
	device_destroy(async_device.mclass, MKDEV(async_device.major, 0));
	class_destroy(async_device.mclass);
	unregister_chrdev_region(MKDEV(async_device.major, 0), ASYNC_NR);
}

module_init(async_init);
module_exit(async_exit);

MODULE_DESCRIPTION("Async Tetst Driver");
MODULE_ALIAS("kmodule:async test");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);