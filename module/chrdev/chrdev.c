/**
 * @file char_dev.c
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2021-04-24
 * 
 * @brief 
 * 
 * @copyright Copyright (c) 2021  mengdemao
 * 
 */
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
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

#include <kversion.h>
#include "hello.h"

struct hello_device {
	struct class *mclass;		/* 设备类 */
	struct cdev mcdev;			/* cdev */
	const char *name;			/* 设备名称 */
	dev_t major;				/* 主设备号 */
	uint8_t mem[128];			/* 存储单元 */
};

struct hello_device hello =
{
	.name  = HELLO_NAME,
	.major = HELLO_MAJOR_NR,
};

ssize_t hello_write(struct file *file, const char __user *data,
					size_t len, loff_t *ppos)
{
	printk(KERN_ERR"Write %s\r\n", data);
	return 0;
}

ssize_t hello_read(struct file *file, char __user *buf,
				   size_t len, loff_t * ppos)
{
	return 0;
}

static int hello_open(struct inode *inode, struct file *file)
{

	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	return 0;
}

static loff_t hello_llseek(struct file *file, loff_t offset, int origin)
{
	return 0;
}

static const struct file_operations hello_ops = {
	.owner   = THIS_MODULE,
	.write   = hello_write,
	.read    = hello_read,
	.open    = hello_open,
	.release = hello_release,
	.llseek  = hello_llseek,
};

static int __init hello_init(void)
{
	int i;
	int rc;
	dev_t devid;
	char fmt[12];

	printk(KERN_INFO "Hello World Init\r\n");

	/* get the divice id */
	if (hello.major) {
		devid = MKDEV(hello.major, 0);
		rc = register_chrdev_region(devid, HELLO_MAJOR_NR, hello.name);
	} else {
		rc = alloc_chrdev_region(&devid, 0, HELLO_MAJOR_NR, hello.name);
		hello.major = MAJOR(devid);
	}
	printk(KERN_ERR "hello_major %d\r\n", hello.major);

	/* create device class */
	hello.mclass = class_create(THIS_MODULE, hello.name);

	strcpy(fmt, hello.name);
	strcpy(fmt+strlen(hello.name), "%d");
	for (i = 0; i < HELLO_MAJOR_NR; i++)
		device_create(hello.mclass, NULL, MKDEV(hello.major, i), NULL, fmt, i);

	/* setup cdev */
	cdev_init(&hello.mcdev, &hello_ops);

	return 0;
}

static void __exit hello_exit(void)
{
	int i = 0;
	printk(KERN_INFO "Hello World Exit\r\n");
	for (i = 0; i < HELLO_MAJOR_NR; i++) {
		device_destroy(hello.mclass, MKDEV(hello.major, i));
	}
	class_destroy(hello.mclass);

	unregister_chrdev_region(MKDEV(hello.major, 0), HELLO_MAJOR_NR);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("Hello Tetst Driver");
MODULE_ALIAS("kmodule:hello world");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
