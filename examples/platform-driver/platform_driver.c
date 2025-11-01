#include <linux/module.h>
#include <linux/platform_device.h>

static int myprobe(struct platform_device *pdev){
	pr_info("my_platform_driver: probe called for %s\n", dev_name(&pdev->dev));
	return 0;
}

static void myremove(struct platform_device *pdev){
	pr_info("my_platform_driver: remove called for %s\n", dev_name(&pdev->dev));
}

static struct platform_driver my_platform_driver = {
	.probe  = myprobe,
	.remove = myremove,
	.driver  = {
		.name  = "my_platform_device",
		.owner = THIS_MODULE,
	},
};

module_platform_driver(my_platform_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhana");
MODULE_DESCRIPTION("Basic platform driver example");
