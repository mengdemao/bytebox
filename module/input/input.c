/*
 * @Author: your name
 * @Date: 2021-04-23 13:13:21
 * @LastEditTime: 2021-04-24 20:24:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /project/kmodule/15.input/input.c
 */

#define pr_fmt(fmt) "input: " fmt

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
#include <linux/input.h>
#include <linux/sched/signal.h>

#include <kversion.h>
#include "input_private.h"

#define PTRACE		pr_err("%s\r\n", __func__)

struct input_dev *input_device;

static void input_simulate_timer_func(struct timer_list *unused);
static DEFINE_TIMER(input_simulate_timer, input_simulate_timer_func);

static void input_simulate_timer_func(struct timer_list *unused)
{
	input_event(input_device, EV_KEY, 12, 1);
	input_sync(input_device);
	pr_err("input_simulate_timer_func");

	mod_timer(&input_simulate_timer, jiffies + HZ);
}

static int __init input_init(void)
{
	PTRACE;

	input_device = input_allocate_device();

	if (input_device == NULL) {
		pr_err("input_alloc_device fail!");
		goto err;
	}

	if (input_register_device(input_device)) {
		pr_err("input_register_device fail!");
		goto err2;
	}

	add_timer(&input_simulate_timer);

	return 0;

	input_unregister_device(input_device);

err2:
	input_free_device(input_device);

err:
	return -1;
}

static void __exit input_exit(void)
{
	PTRACE;

	del_timer(&input_simulate_timer);

	input_unregister_device(input_device);

	input_free_device(input_device);
}

module_init(input_init);
module_exit(input_exit);

MODULE_DESCRIPTION("Input Tetst Driver");
MODULE_ALIAS("kmodule:input test");
MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
