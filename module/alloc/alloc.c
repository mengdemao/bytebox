/**
 * @file alloc.c
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2021-05-01
 *
 * @brief 内存分配
 *
 * @copyright Copyright (c) 2021  mengdemao
 *
 */
#define pr_fmt(fmt) "alloc: " fmt
#include <linux/init.h>
#include <linux/module.h>
#include <kversion.h>

struct page *g_page;
unsigned long *g_addr;

int order = 9;

static int __init alloc_init(void)
{
	int node = NUMA_NO_NODE;
	if (node == NUMA_NO_NODE)
		g_page = alloc_pages(GFP_KERNEL, order);
	else
		g_page = __alloc_pages_node(node, GFP_KERNEL, order);
	
	if (!g_page) {
		pr_err("alloc pages fail\r\n");
		return 0;
	}

	printk(KERN_INFO"Alloc Init %s %s\r\n", REVISION_GIT, COMPILE_TIME);
	return 0;
}
module_init(alloc_init);

static void __exit alloc_exit(void)
{
	__free_pages(g_page, order);
	printk(KERN_INFO"Alloc Exit %s, %s\r\n", REVISION_GIT, COMPILE_TIME);
}
module_exit(alloc_exit);

MODULE_DESCRIPTION("page alloc test");
MODULE_ALIAS("page");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);