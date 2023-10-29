// Multi filed modules -> Part 2.
#include <linux/module.h>
#include <linux/kernel.h>

void cleanup_module()
{
	printk(KERN_INFO "Already gone, bye half world\n");
}
