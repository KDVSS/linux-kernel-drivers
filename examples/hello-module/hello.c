#include <linux/module.h>
#include <linux/init.h>

static int start_init(void){
	printk(KERN_INFO "Hello, Welcome to the Kernel world!\n");
	return 0;
}

static void exit_init(void){
	printk("Bye! \n");
}
module_init(start_init);
module_exit(exit_init);

MODULE_LICENSE("GPL");
