#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhana Kondapalli");
MODULE_DESCRIPTION("Self-Binding Platform Driver (Simplified Demo).");

#define MOCK_ADDRESS 0xABCD0000
#define MOCK_SIZE    0x1000

static struct platform_device *mock_pdev;

struct peripheral_device {
    void __iomem *reg_base; 
};

static int peripheral_probe(struct platform_device *pdev)
{
    struct peripheral_device *pdata;
    struct resource *res;
    u32 status_reg = 0;

    printk(KERN_NOTICE "DRV: PROBE called.\n");

    pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
    if (!pdata) {
        printk(KERN_ERR "DRV: Failed to allocate memory.\n");
        return -ENOMEM;
    }

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        printk(KERN_ERR "DRV: Failed to get MMIO resource.\n");
        return -ENOENT;
    }

    pdata->reg_base = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(pdata->reg_base)) {
        printk(KERN_ERR "DRV: Failed to map I/O memory.\n");
        return PTR_ERR(pdata->reg_base);
    }

    platform_set_drvdata(pdev, pdata);

    printk(KERN_INFO "DRV: Mapped V-Address: %p, Physical Range: 0x%llx (Size: %llu bytes)\n",
           pdata->reg_base, (unsigned long long)res->start, (unsigned long long)resource_size(res));

    status_reg = readl(pdata->reg_base + 0x08);
    printk(KERN_INFO "DRV: Status Read: 0x%08x\n", status_reg);

    writel(0x00000001, pdata->reg_base + 0x00);
    printk(KERN_INFO "DRV: Peripheral ENABLED.\n");

    printk(KERN_NOTICE "DRV: Initialization SUCCESS.\n");

    return 0;
}

static void peripheral_remove(struct platform_device *pdev)
{
    struct peripheral_device *pdata = platform_get_drvdata(pdev);
    writel(0x00000000, pdata->reg_base + 0x00);
    printk(KERN_NOTICE "DRV: REMOVE called. Hardware disabled.\n");
}

static struct platform_driver peripheral_platform_driver = {
    .probe          = peripheral_probe,
    .remove         = peripheral_remove,
    .driver = {
        .name       = "custom-soc-peripheral", 
        .owner      = THIS_MODULE,
    },
};

static int __init simple_init(void)
{
    int ret;
    struct resource res[] = {
        [0] = {
            .start = MOCK_ADDRESS,
            .end   = MOCK_ADDRESS + MOCK_SIZE - 1,
            .flags = IORESOURCE_MEM,
        },
    };

    ret = platform_driver_register(&peripheral_platform_driver);
    if (ret) {
        printk(KERN_ERR "INIT: Failed to register driver.\n");
        return ret;
    }
    
    mock_pdev = platform_device_register_simple("custom-soc-peripheral", -1, res, 1);

    if (IS_ERR(mock_pdev)) {
        printk(KERN_ERR "INIT: Failed to register platform device.\n");
        platform_driver_unregister(&peripheral_platform_driver);
        return PTR_ERR(mock_pdev);
    }
    
    printk(KERN_INFO "INIT: Module loaded. Driver and Mock Device registered.\n");
    return 0;
}

static void __exit simple_exit(void)
{
    if (mock_pdev) {
        platform_device_unregister(mock_pdev);
    }
    platform_driver_unregister(&peripheral_platform_driver);
    printk(KERN_INFO "EXIT: Driver and Device successfully unregistered.\n");
}

module_init(simple_init);
module_exit(simple_exit);
