// Demostrates module_init() and module_exit() macros
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>		// Needed for macros

static int __init hello_2_init(void)
{
	printk(KERN_INFO "Hello world 2\n");
	return 0;
}

static void __exit hello_2_exit(void)
{
	printk(KERN_INFO "Goodbye world 2\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

// There macros are defined in init.h, used so that init_module() and cleanup_module() were not needed anymore

// Added a random licence so that make wouldn't cry
MODULE_LICENSE("GPL");
