/**
 * @file   rtc.c
 * @author mengdemao <mengdemao19951021@163.com>
 * @date   Fri Dec 11 11:18:32 2020
 *
 * @brief rtc driver
 *
 *
 */

#define pr_fmt(fmt) "rtc: " fmt

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
#include <linux/rtc.h>
#include <linux/sched/signal.h>

#include <kversion.h>
#include "rtc_private.h"

#define PTRACE		pr_err("%s\r\n", __func__)

struct rtc_device_private {
	struct class *mclass;		/* 设备类 */
	struct cdev mcdev;			/* cdev */
	const char *name;			/* 设备名称 */
	dev_t major;				/* 主设备号 */
};

struct rtc_device_private rtc_device_private = {
	.name  = RTC_NAME,
	.major = RTC_MAJOR,
};

static ssize_t rtc_write(struct file *file, const char __user *data,
				   size_t len, loff_t *ppos)
{
	PTRACE;
	return 0;
}

static ssize_t rtc_read(struct file *file, char __user *buf,
				  size_t len, loff_t * ppos)
{
	PTRACE;
	return 0;
}

static int rtc_open(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static int rtc_release(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static loff_t rtc_llseek(struct file *file, loff_t offset, int origin)
{
	PTRACE;
	return 0;
}

static const struct file_operations rtc_ops = {
	.owner   = THIS_MODULE,
	.write   = rtc_write,
	.read    = rtc_read,
	.open    = rtc_open,
	.release = rtc_release,
	.llseek  = rtc_llseek,
};

static int __init rtc_init(void)
{
	int ret = 0;
	dev_t devid;
	PTRACE;

	/* get the divice id */
	if (rtc_device_private.major) {
		devid = MKDEV(rtc_device_private.major, 0);
		ret = register_chrdev_region(devid, RTC_NR, rtc_device_private.name);
	} else {
		ret = alloc_chrdev_region(&devid, 0, RTC_NR, rtc_device_private.name);
		rtc_device_private.major = MAJOR(devid);
	}

	/* create device class */
	rtc_device_private.mclass = class_create(THIS_MODULE, rtc_device_private.name);

	/* device_create */
	device_create(rtc_device_private.mclass, NULL, MKDEV(rtc_device_private.major, 0), NULL, rtc_device_private.name, 0);

	/* init cdev */
	cdev_init(&rtc_device_private.mcdev, &rtc_ops);

	/* cdev add */
	cdev_add(&rtc_device_private.mcdev, MKDEV(rtc_device_private.major, 0), 1);

	return ret;
}

static void __exit rtc_exit(void)
{
	PTRACE;

	device_destroy(rtc_device_private.mclass, MKDEV(rtc_device_private.major, 0));

	class_destroy(rtc_device_private.mclass);

	unregister_chrdev_region(MKDEV(rtc_device_private.major, 0), RTC_NR);
}

module_init(rtc_init);
module_exit(rtc_exit);

MODULE_DESCRIPTION("Rtc Driver Test");
MODULE_ALIAS("kmodule:rtc test");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
