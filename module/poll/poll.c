/*
 * @Author: your name
 * @Date: 2021-04-19 21:06:53
 * @LastEditTime: 2021-04-24 20:22:24
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /project/kmodule/12.poll/poll.c
 */
#include <linux/init.h>
#include <linux/module.h>
#include <kversion.h>

static int __init poll_init(void)
{
	printk(KERN_INFO"Poll Init %s %s\r\n", REVISION_GIT, COMPILE_TIME);
	return 0;
}
module_init(poll_init);

static void __exit poll_exit(void)
{
	printk(KERN_INFO"Poll Exit %s, %s\r\n", REVISION_GIT, COMPILE_TIME);
}
module_exit(poll_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
