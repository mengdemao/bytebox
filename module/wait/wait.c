/**
 * @file   wait.c
 * @author mengdemao <mengdemao19951021@163.com>
 * @date   Fri Dec 11 11:18:32 2020
 *
 * @brief
 *
 *
 */

#define pr_fmt(fmt) "wait: " fmt

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
#include <linux/wait.h>
#include <linux/sched/signal.h>

#include <kversion.h>
#include "wait.h"

#define PTRACE		pr_err("%s\r\n", __func__)

struct wait_device {
	struct class *mclass;		/* 设备类 */
	struct cdev mcdev;			/* cdev */
	const char *name;			/* 设备名称 */
	dev_t major;				/* 主设备号 */

	int wait_flag;				/* 等待标志 */

	struct mutex mutex;			/* 信号量 */
	wait_queue_head_t wait_r;	/* 读等待队列 */
	wait_queue_head_t wait_w;	/* 写等待队列 */
};

struct wait_device wait_device = {
	.name  = WAIT_NAME,
	.major = WAIT_MAJOR,
	.wait_flag = 0,
};

ssize_t wait_write(struct file *file, const char __user *data,
				   size_t len, loff_t *ppos)
{
	DECLARE_WAITQUEUE(wait, current);		/* 声明等待队列 */
	int ret = -1;
	PTRACE;

	mutex_lock(&wait_device.mutex);
	/* 非阻塞模式直接写入 */
	if (file->f_flags & O_NONBLOCK) {
		pr_err("write in O_NONBLOCK Mode");
		goto pure_write;
	}

	add_wait_queue(&wait_device.wait_w, &wait);
	while (wait_device.wait_flag == true) {
		pr_err("Write INTERRUPTIBLE");
		__set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&wait_device.mutex);
		schedule();
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			remove_wait_queue(&wait_device.wait_w, &wait);
			__set_current_state(TASK_RUNNING);
			goto out;
		}
	}
	remove_wait_queue(&wait_device.wait_w, &wait);

pure_write:
	wait_device.wait_flag = true;
	pr_err("Write Successful");

	wake_up_interruptible(&wait_device.wait_r);
	pr_err("Wakeup Read");
	goto out;

out:
	mutex_unlock(&wait_device.mutex);
	return ret;
}

ssize_t wait_read(struct file *file, char __user *buf,
				  size_t len, loff_t * ppos)
{
	DECLARE_WAITQUEUE(wait, current);		/* 声明等待队列 */
	int ret = 0;
	PTRACE;

	mutex_lock(&wait_device.mutex);
	/* 非阻塞模式直接写入 */
	if (file->f_flags & O_NONBLOCK) {
		pr_err("write in O_NONBLOCK Mode");
		goto pure_read;
	}

	add_wait_queue(&wait_device.wait_r, &wait);
	while (wait_device.wait_flag == false) {
		pr_err("Write INTERRUPTIBLE");
		__set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&wait_device.mutex);
		schedule();
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			remove_wait_queue(&wait_device.wait_r, &wait);
			__set_current_state(TASK_RUNNING);
			goto out;
		}
	}
	remove_wait_queue(&wait_device.wait_r, &wait);

pure_read:
	wait_device.wait_flag = false;
	pr_err("Read Successful");

	wake_up_interruptible(&wait_device.wait_w);
	pr_err("Wakeup Write");

	goto out;

out:
	mutex_unlock(&wait_device.mutex);
	return 0;
}

static int wait_open(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static int wait_release(struct inode *inode, struct file *file)
{
	PTRACE;
	return 0;
}

static loff_t wait_llseek(struct file *file, loff_t offset, int origin)
{
	PTRACE;
	return 0;
}

static const struct file_operations wait_ops = {
	.owner   = THIS_MODULE,
	.write   = wait_write,
	.read    = wait_read,
	.open    = wait_open,
	.release = wait_release,
	.llseek  = wait_llseek,
};

static int __init wait_init(void)
{
	int ret = 0;
	dev_t devid;
	PTRACE;

	/* get the divice id */
	if (wait_device.major) {
		devid = MKDEV(wait_device.major, 0);
		ret = register_chrdev_region(devid, WAIT_NR, wait_device.name);
	} else {
		ret = alloc_chrdev_region(&devid, 0, WAIT_NR, wait_device.name);
		wait_device.major = MAJOR(devid);
	}

	init_waitqueue_head(&wait_device.wait_r);	/* 初始化读队列头 */
	init_waitqueue_head(&wait_device.wait_w);	/* 初始化写队列头 */

	/* create device class */
	wait_device.mclass = class_create(THIS_MODULE, wait_device.name);

	/* device_create */
	device_create(wait_device.mclass, NULL, MKDEV(wait_device.major, 0), NULL, wait_device.name, 0);

	/* init cdev */
	cdev_init(&wait_device.mcdev, &wait_ops);

	/* cdev add */
	cdev_add(&wait_device.mcdev, MKDEV(wait_device.major, 0), 1);

	return ret;
}

static void __exit wait_exit(void)
{
	PTRACE;
	device_destroy(wait_device.mclass, MKDEV(wait_device.major, 0));
	class_destroy(wait_device.mclass);
	unregister_chrdev_region(MKDEV(wait_device.major, 0), WAIT_NR);
}

module_init(wait_init);
module_exit(wait_exit);

MODULE_DESCRIPTION("Wait Tetst Driver");
MODULE_ALIAS("kmodule:wait world");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
