#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/efi.h>
#include <linux/slab.h>

#include <asm/setup.h>

struct kobject *hellop_kobj;
struct kobject *hello1_kobj;
struct kobject *hello2_kobj;
struct kobject *hello3_kobj;

static int __init hello_init(void)
{
	/* 主目录 */
	hellop_kobj = kobject_create_and_add("hellop", NULL);

	/* 子目录 */
	hello1_kobj = kobject_create_and_add("hello1", hellop_kobj);
	hello2_kobj = kobject_create_and_add("hello2", hellop_kobj);
	hello3_kobj = kobject_create_and_add("hello3", hellop_kobj);

	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	kobject_put(hello1_kobj);
	kobject_put(hello2_kobj);
	kobject_put(hello3_kobj);
	kobject_put(hellop_kobj);
}
module_exit(hello_exit);

MODULE_AUTHOR("MengDemao mengdemao19951021@163.com");
MODULE_LICENSE("GPL v2");
