#include <linux/module.h>
#include <linux/platform_device.h>
 
static struct platform_device my_device = {
    .name = "my_platform_device", // must match driver name
    .id = -1,
};

static int my_probe(struct platform_device *pdev)
{
    pr_info("my_platform_driver: probe called for device: %s\n", pdev->name);
    return 0;
}

static void my_remove(struct platform_device *pdev)
{
    pr_info("my_platform_driver: remove called for device: %s\n", pdev->name);
}

static struct platform_driver my_driver = {
    .probe = my_probe,
    .remove = my_remove,
    .driver = {
        .name = "my_platform_device",
        .owner = THIS_MODULE,
    },
};


static int __init my_device_driver_init(void)
{
    int ret;

    platform_device_register(&my_device);
    pr_info("my_platform_device: device registered\n");

    ret = platform_driver_register(&my_driver);
    if (ret)
    {
        pr_err("my_platform_driver: failed to register\n");
        platform_device_unregister(&my_device);
        return ret;
    }

    pr_info("my_platform_driver: driver registered\n");
    return 0;
}

static void __exit my_device_driver_exit(void)
{
    platform_driver_unregister(&my_driver);
    platform_device_unregister(&my_device);
    pr_info("my_platform_driver: driver and device unregistered\n");
}

module_init(my_device_driver_init);
module_exit(my_device_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhana");
MODULE_DESCRIPTION("Simple Platform Device + Driver Example");
MODULE_VERSION("1.0");

