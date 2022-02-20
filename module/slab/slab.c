/**
 * @file slab.c
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2021-04-24
 *
 * @brief slab
 *
 * @copyright Copyright (c) 2021  mengdemao
 *
 */
#define pr_fmt(fmt) "slab: " fmt
#include <linux/init.h>
#include <linux/module.h>
#include <linux/btree.h>
#include <linux/cache.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#include <kversion.h>

#define PTRACE						pr_err("%s\r\n", __func__)
#define DRV_NAME					"hello_slab"

static struct kmem_cache *tmp_cachep;
static char *buf;

static int __init slab_init(void)
{
	PTRACE;
	tmp_cachep = kmem_cache_create("hello_slab", 256, 0, SLAB_HWCACHE_ALIGN, NULL);
	if (!tmp_cachep) {
		kmem_cache_destroy(tmp_cachep);
		return -ENOMEM;	
	}
	buf = kmem_cache_zalloc(tmp_cachep, GFP_KERNEL);
	if (buf) {
		strncpy(buf, "Slab test\r\n", 256);
		pr_err("%s", buf);	
	}
	return 0;
}
module_init(slab_init);

static void __exit slab_exit(void)
{
	PTRACE;
	kmem_cache_free(tmp_cachep, buf);
	kmem_cache_destroy(tmp_cachep);
}
module_exit(slab_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
