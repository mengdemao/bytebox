/**
 * @file param.c
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2021-04-24
 * 
 * @brief 模块的参数传递测试
 * 
 * @copyright Copyright (c) 2021  mengdemao
 * 
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <kversion.h>

static int pid_qury = 1;
module_param(pid_qury, int, S_IRUGO);

/* static char *name_qury = "systemd"; */
/* module_param(name_qury, charp, S_IRUGO); */

static int __init hello_init(void)
{
	struct task_struct *task = NULL, *p = NULL;
	struct list_head *pos = NULL;
	int cnt = 0;

	printk(KERN_INFO"Hello Init\r\n");
	task = &init_task;
	list_for_each(pos, &task->tasks) {
		p = list_entry(pos, struct task_struct, tasks);
		cnt += 1;
		/* printk(KERN_INFO"PID %d ---> %s\r\n", p->pid, p->comm); */
		if (pid_qury == p->pid) {
			printk(KERN_INFO"task state %ld\r\n", p->state);
		}
	}
	/* printk(KERN_INFO"task count %d\r\n", cnt); */

	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	printk(KERN_INFO"Hello Exit\r\n");
}
module_exit(hello_exit);

MODULE_AUTHOR("MengDemao mengdemao19951021@163.com");
MODULE_LICENSE("GPL v2");
