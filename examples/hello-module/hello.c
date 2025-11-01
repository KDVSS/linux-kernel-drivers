#include <linux/module.h>
#include <linux/init.h>

static int start_init(void){
	printk(KERN_INFO "Hello, Welcome to the Kernel world!\n");
	return 0;
}

void end_init(){
	printk("Bye! \n");
}
module_init(start_init);
module_exit(end_init);

MODULE_LICENSE("GPL");
