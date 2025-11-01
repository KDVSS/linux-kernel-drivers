#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simplechar"
#define MSG "Hello from the Kernel!\n"

static int major;

static int my_open(struct inode *inode, struct file *file){
	pr_info("simplechar: device opened\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file){
	pr_info("simplechar: device closed\n");
	return 0;
}


static ssize_t my_read(struct file *file, char __user *buffer, size_t len, loff_t *offset ){
	int bytes = strlen(MSG);
	if(*offset >= bytes){
		return 0;
	}
	if(copy_to_user(buffer, MSG, bytes)){
		return -EFAULT;
	}
	*offset += bytes;
	pr_info("simplechar: read called\n ");
	return bytes;
}

static ssize_t my_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset){
	char msg[100];
	if(len > 99){
		len = 99;
	}
	if(copy_from_user(msg, buffer, len)){
		return -EFAULT;
	}
	msg[len] = '\0';
	pr_info("simplechar: received from user: %s\n", msg);
	return len;
}


static struct file_operations fops = {
	.owner   = THIS_MODULE,
	.open    = my_open,
	.read    = my_read,
	.release = my_release,
	.write   = my_write,
};

static int __init simplechar_init(void){
	major = register_chrdev(0, DEVICE_NAME, &fops);
	if(major < 0){
		pr_err("simplechar: failed to register\n");
		return major;
	}
	pr_info("simplechar: registered with major number %d\n", major);
	pr_info("Create device file with: sudo mknod /dev/%s c %d 0\n", DEVICE_NAME, major);
	return 0;
}

static void __exit simplechar_exit(void){
	unregister_chrdev(major, DEVICE_NAME);
	pr_info("simplechar: unregistered\n");
}


module_init(simplechar_init);
module_exit(simplechar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhana");
MODULE_DESCRIPTION("Simple character driver - begineer example");
