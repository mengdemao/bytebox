/**
 * @file platform.c
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
#include <linux/platform_device.h>

#include <kversion.h>

#define PTRACE					pr_err("%s\r\n", __func__)
#define PLATFORM_DEMO_NR		1  /* local major, change later */
#define PLATFORM_DEMO_NAME		"platform_demo_test"
#define PLATFORM_DEMO_MAJOR		0

struct platform_demo_private {
	struct class *mclass;		/* 设备类 */
	struct cdev mcdev;			/* cdev */
	const char *name;			/* 设备名称 */
	dev_t major;				/* 主设备号 */
};

struct platform_demo_private platform_demo =
{
	.name  = PLATFORM_DEMO_NAME,
	.major = PLATFORM_DEMO_MAJOR,
};

ssize_t platform_demo_write(struct file *file, const char __user *data,
	size_t len, loff_t *ppos)
{
	PTRACE;
	return 0;
}

ssize_t platform_demo_read(struct file *file, char __user *buf,
	size_t len, loff_t * ppos)
{
	PTRACE;
	return 0;
}

static int platform_demo_open(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static int platform_demo_release(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static loff_t platform_demo_llseek(struct file *file, loff_t offset, int origin)
{
	PTRACE;
	return 0;
}

static const struct file_operations platform_demo_ops = {
	.owner   = THIS_MODULE,
	.write   = platform_demo_write,
	.read    = platform_demo_read,
	.open    = platform_demo_open,
	.release = platform_demo_release,
	.llseek  = platform_demo_llseek,
};

/* 平台驱动 */
static int platform_demo_probe(struct platform_device *pdev)
{
	dev_t devid;
	int ret = 0;
	PTRACE;

	/* get the divice id */
	if (platform_demo.major) {
		devid = MKDEV(platform_demo.major, 0);
		ret = register_chrdev_region(devid, PLATFORM_DEMO_NR, platform_demo.name);
	} else {
		ret = alloc_chrdev_region(&devid, 0, PLATFORM_DEMO_NR, platform_demo.name);
		platform_demo.major = MAJOR(devid);
	}

	/* create device class */
	platform_demo.mclass = class_create(THIS_MODULE, platform_demo.name);

	/* device_create */
	device_create(platform_demo.mclass, NULL, MKDEV(platform_demo.major, 0), NULL, platform_demo.name, 0);

	/* init cdev */
	cdev_init(&platform_demo.mcdev, &platform_demo_ops);

	/* cdev add */
	cdev_add(&platform_demo.mcdev, MKDEV(platform_demo.major, 0), 1);

	return ret;
}

static int platform_demo_remove(struct platform_device *pdev)
{
	PTRACE;

	device_destroy(platform_demo.mclass, MKDEV(platform_demo.major, 0));

	class_destroy(platform_demo.mclass);

	unregister_chrdev_region(MKDEV(platform_demo.major, 0), PLATFORM_DEMO_NR);

	return 0;
}

static void platform_demo_shutdown(struct platform_device *pdev)
{
	PTRACE;
}

static int platform_demo_suspend(struct platform_device *pdev, pm_message_t message)
{
	PTRACE;
	return 0;
}

static int platform_demo_resume(struct platform_device *pdev)
{
	PTRACE;
	return 0;
}

static struct platform_driver platform_demo_driver = {
	.probe = platform_demo_probe,
	.remove = platform_demo_remove,
	.shutdown = platform_demo_shutdown,
	.suspend = platform_demo_suspend,
	.resume = platform_demo_resume,
	.driver = {
		.name = "Platform_Demo"
	},
};

/* 设备资源 */
static struct resource platform_demo_resource[] =
{
	{
		.start = 0,
		.end = 4 * 1024,
		.flags = IORESOURCE_MEM,
	},
};

/* 扩展资源 */
static struct platform_demo_info {
	char name[16];
} platform_demo_info = {
	.name = "Platform_Demo",
};

void platform_demo_device_release(struct device *dev)
{
	PTRACE;
}

/* 设备描述 */
static struct platform_device platform_demo_device = {
	.name = "Platform_Demo",
	.id = -1,
	.num_resources = ARRAY_SIZE(platform_demo_resource),
	.resource = platform_demo_resource,	/* 基础资源 */
	.dev = {					/* 扩展资源 */
		.platform_data = &platform_demo_info,
		.release = platform_demo_device_release,
	},
};

static int __init platform_demo_init(void)
{
	PTRACE;
	platform_driver_register(&platform_demo_driver);
	platform_device_register(&platform_demo_device);
	return 0;
}

static void __exit platform_demo_exit(void)
{
	PTRACE;
	platform_device_unregister(&platform_demo_device);
	platform_driver_unregister(&platform_demo_driver);
}

module_init(platform_demo_init);
module_exit(platform_demo_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
MODULE_DESCRIPTION("Platform Driver For Device");
MODULE_ALIAS("platform:demo test");
