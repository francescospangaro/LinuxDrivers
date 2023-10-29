// Multi filed modules -> part 1.
#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "Hello half world\n");
	return 0;
}

MODULE_LICENSE("GNU");
