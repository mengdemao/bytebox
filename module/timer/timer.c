/*
 * @Author: your name
 * @Date: 2021-04-19 21:06:53
 * @LastEditTime: 2021-04-24 20:22:03
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /project/kmodule/11.timer/timer.c
 */
#include <linux/init.h>
#include <linux/module.h>

#include <kversion.h>

static int __init hello_init(void)
{
	printk(KERN_INFO"Hello Init\r\n");
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	printk(KERN_INFO"Hello Exit\r\n");
}
module_exit(hello_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
