/**
 * @file hello.c
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2021-04-24
 *
 * @brief 驱动开发环境测试
 *
 * @copyright Copyright (c) 2021  mengdemao
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <kversion.h>

static int __init hello_init(void)
{
	printk(KERN_INFO"Hello Init %s %s\r\n", REVISION_GIT, COMPILE_TIME);
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	printk(KERN_INFO"Hello Exit %s, %s\r\n", REVISION_GIT, COMPILE_TIME);
}
module_exit(hello_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
