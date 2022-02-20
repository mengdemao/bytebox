/**
 * @file mapping.c
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2021-04-24
 * 
 * @brief 
 * 
 * @copyright Copyright (c) 2021  mengdemao
 * 
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/sched/task.h>
#include <kversion.h>

static int pid_qury = 1;
module_param(pid_qury, int, S_IRUGO);

/**
 * 打印指定的PID
 *
 * @param pid
 *
 * @return
 */
static struct task_struct *pcb_print(int pid)
{
	struct task_struct *task;
	struct list_head *pos;

	list_for_each(pos, &init_task.tasks) {
		task = list_entry(pos, struct task_struct, tasks);
		if (pid == task->pid) {
			return task;
		}
	}

	return 0;
}

static void mm_set(struct task_struct *task)
{
	struct mm_struct *mm = task->mm;
	(void)mm;
}
static int __init hello_init(void)
{
	mm_set(pcb_print(pid_qury));
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
}
module_exit(hello_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
