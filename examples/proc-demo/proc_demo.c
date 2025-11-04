// proc_demo.c
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_NAME "hello_proc"

static int count = 0;
static struct proc_dir_entry *proc_entry;

/* seq_file show function — called when user reads /proc/hello_proc */
static int proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "Hello from kernel! Count = %d\n", count);
	count++;
	return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_show, NULL);
}

/* Use proc_ops (newer kernels) instead of file_operations */
static const struct proc_ops proc_fops = {
	.proc_open    = proc_open,
	.proc_read    = seq_read,
	.proc_lseek   = seq_lseek,
	.proc_release = single_release,
};

static int __init proc_demo_init(void)
{
	proc_entry = proc_create(PROC_NAME, 0444, NULL, &proc_fops);
	if (!proc_entry) {
		pr_err("proc-demo: failed to create /proc/%s\n", PROC_NAME);
		return -ENOMEM;
	}
	pr_info("proc-demo: /proc/%s created\n", PROC_NAME);
	return 0;
}

static void __exit proc_demo_exit(void)
{
	if (proc_entry)
		proc_remove(proc_entry);
	pr_info("proc-demo: /proc/%s removed\n", PROC_NAME);
}

module_init(proc_demo_init);
module_exit(proc_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhana");
MODULE_DESCRIPTION("Simple procfs demo: /proc/hello_proc increments a counter on read");
MODULE_VERSION("1.0");

