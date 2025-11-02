#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>

#define GPIO_PIN 3  /* GPIO number on Raspberry Pi header (Pin 11) */

static struct gpio_desc *button_gpiod;
static unsigned int irq_number;

/* ---------- Interrupt Handler ---------- */
static irqreturn_t button_irq_handler(int irq, void *dev_id)
{
    pr_info("irq-demo: Interrupt occurred on GPIO %d (IRQ %d)\n", GPIO_PIN, irq);
    return IRQ_HANDLED;
}

/* ---------- Module Init ---------- */
static int __init irq_demo_init(void)
{
    int result;

    pr_info("irq-demo: Initializing module...\n");

    /*
     * Request the GPIO line as input using the GPIO descriptor API.
     * gpiod_get() looks up the GPIO by its numeric ID from the base chip.
     */
    button_gpiod = gpio_to_desc(GPIO_PIN);
    if (!button_gpiod) {
        pr_err("irq-demo: Failed to get descriptor for GPIO %d\n", GPIO_PIN);
        return -ENODEV;
    }

    gpiod_direction_input(button_gpiod);

    /* Map GPIO to IRQ */
    irq_number = gpiod_to_irq(button_gpiod);
    if (irq_number < 0) {
        pr_err("irq-demo: Failed to map GPIO to IRQ\n");
        return irq_number;
    }

    /* Request IRQ on both edges */
    result = request_irq(irq_number, button_irq_handler,
                         IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                         "irq_demo_handler", NULL);
    if (result) {
        pr_err("irq-demo: Cannot request IRQ %d\n", irq_number);
        return result;
    }

    pr_info("irq-demo: IRQ %d registered for GPIO %d\n", irq_number, GPIO_PIN);
    pr_info("irq-demo: Trigger GPIO %d manually to test.\n", GPIO_PIN);
    return 0;
}

/* ---------- Module Exit ---------- */
static void __exit irq_demo_exit(void)
{
    free_irq(irq_number, NULL);
    pr_info("irq-demo: Module unloaded. Freed IRQ %d\n", irq_number);
}

/* ---------- Module Macros ---------- */
module_init(irq_demo_init);
module_exit(irq_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhana Venkata Siva Sai Kondapalli");
MODULE_DESCRIPTION("Simple GPIO IRQ Demo (modern kernel, Raspberry Pi)");
MODULE_VERSION("2.0");

