/*
 * @Author: your name
 * @Date: 2021-04-24 16:36:28
 * @LastEditTime: 2021-04-24 17:25:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /project/kmodule/20.block/block.c
 */
/**
 * @file   block.c
 * @author mengdemao <mengdemao19951021@163.com>
 * @date   Fri Dec 11 11:18:32 2020
 *
 * @brief
 *
 *
 */

#define pr_fmt(fmt) "block: " fmt

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

#define PTRACE		pr_err("%s\r\n", __func__)

static int __init vdisk_init(void)
{
	printk(KERN_INFO"Vdisk Init %s %s\r\n", REVISION_GIT, COMPILE_TIME);
	return 0;
}
module_init(vdisk_init);

static void __exit vdisk_exit(void)
{
	printk(KERN_INFO"Vdisk Exit %s, %s\r\n", REVISION_GIT, COMPILE_TIME);
}
module_exit(vdisk_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
