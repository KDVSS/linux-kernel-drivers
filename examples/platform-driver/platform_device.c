#include <linux/module.h>
#include <linux/platform_device.h>

static struct platform_device my_device = {
    .name = "my_platform_device", // must match driver name
    .id = -1,
};

static int __init my_device_init(void)
{
    platform_device_register(&my_device);
    pr_info("my_platform_device: device registered\n");
    return 0;
}

static void __exit my_device_exit(void)
{
    platform_device_unregister(&my_device);
    pr_info("my_platform_device: device unregistered\n");
}

module_init(my_device_init);
module_exit(my_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhana");
MODULE_DESCRIPTION("Dummy platform device");

