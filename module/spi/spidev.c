/**
 * @file spidev.c
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2021-04-30
 * 
 * @brief spi总线测试程序
 * 1. 模拟一个spi总线设备
 * 2. 可以直接用来进行
 * 
 * @copyright Copyright (c) 2021  mengdemao
 * 
 */

#define pr_fmt(fmt) "spidev: " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/dmaengine.h>
#include <linux/iova.h>
#include <linux/anon_inodes.h>
#include <linux/file.h>
#include <linux/vmalloc.h>
#include <linux/of_platform.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>
#include <linux/io.h>
#include <linux/of_gpio.h>
#include <linux/slab.h>
#include <kversion.h>

#define PTRACE						pr_err("%s\r\n", __func__)
#define DRV_NAME					"spidev"

struct demo_spi {
	struct spi_master *master;
	spinlock_t lock;
	int data;
};

static int demo_spi_setup(struct spi_device *spi)
{
	PTRACE;
	return 0;
}

static int demo_spi_transfer(struct spi_device *spi, struct spi_message *msg)
{
	PTRACE;
	return 0;
}

static void demo_spi_set_cs(struct spi_device *spi, bool gpio_level)
{
	PTRACE;
}

static int demo_spi_transfer_one(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *tfr)
{
	return 0;
}

static void demo_spi_handle_err(struct spi_master *master,
				struct spi_message *msg)
{
	PTRACE;
}

static int demo_spi_prepare_message(struct spi_master *master,
				    struct spi_message *msg)
{
	PTRACE;
	return 0;
}

static int demo_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct demo_spi *ds;
	int ret = 0;
	PTRACE;

	/* 申请spi主机驱动 */
	master = spi_alloc_master(&pdev->dev, sizeof(*ds));
	if (!master) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->dev.of_node = pdev->dev.of_node;
	
	master->setup = demo_spi_setup;
	master->set_cs = demo_spi_set_cs;
	master->transfer_one = demo_spi_transfer_one;
	master->handle_err = demo_spi_handle_err;
	master->prepare_message = demo_spi_prepare_message;
	master->transfer = demo_spi_transfer;

	platform_set_drvdata(pdev, master);

	ds = spi_master_get_devdata(master);
	ds->master = master;
	ds->data   = 0;

	spin_lock_init(&ds->lock);

	ret = spi_register_master(master);
	if (ret) {
		goto err_register;
	}

	return 0;

err_register:
	pr_err("error in spi_register_master");
	spi_master_put(master);
	return ret;

err_alloc:
	pr_err("error in spi_alloc_master");
	return ret;
}

static int demo_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = spi_master_get(platform_get_drvdata(pdev));
	struct demo_spi *ds = spi_master_get_devdata(master);
	PTRACE;

     	spi_unregister_master(master);
	spi_master_put(master);
	
	ds->data = 0;

	return 0;
}

static const struct of_device_id demo_spi_match[] = {
	{ .compatible = "demo,demo-spi", },
	{}
};
MODULE_DEVICE_TABLE(of, demo_spi_match);

static struct platform_driver demo_spi_of_driver = {
	.driver = {
		.name = DRV_NAME,
		.of_match_table = demo_spi_match,
	},
	.probe = demo_spi_probe,
	.remove = demo_spi_remove,
};

// static struct demo_spi_of_info {
// 	char name[16];
// } demo_spi_of_info = {
// 	.name = DRV_NAME,
// };

// static struct spi_board_info demo_spi_board_info[] = {
// 	{
// 		.modalias	= "test",
// 		.bus_num	= 2,
// 		.chip_select	= 3,
// 		.max_speed_hz	= 12000000,
// 		.platform_data	= NULL,
// 	}
// };

void demo_spi_of_device_release(struct device *dev)
{
	PTRACE;
}

/* 设备描述 */
static struct platform_device demo_spi_of_device = {
	.name = DRV_NAME,
	.id = -1,
	// .num_resources = ARRAY_SIZE(demo_spi_board_info),
	// .resource = demo_spi_board_info,		/* 基础资源 */
	.dev = {
		.release = demo_spi_of_device_release,
	},
};

static int __init demo_spi_of_driver_init(void)
{
	PTRACE;
	platform_device_register(&demo_spi_of_device);
	platform_driver_register(&demo_spi_of_driver);
	return 0;
}

static void __exit demo_spi_of_driver_exit(void)
{
	PTRACE;
	platform_driver_unregister(&demo_spi_of_driver);
	platform_device_unregister(&demo_spi_of_device);
}

module_init(demo_spi_of_driver_init);
module_exit(demo_spi_of_driver_exit);

MODULE_AUTHOR(KMODULE_AUTHOR);
MODULE_LICENSE(KMODULE_LICENSE);
MODULE_VERSION(KMODULE_VERSION);
MODULE_DESCRIPTION("spi_test driver test");
MODULE_ALIAS("spi_test:spi_test test");
