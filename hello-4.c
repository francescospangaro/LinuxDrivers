// Demonstrates code documentation
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "Francesco Spangaro"
#define DRIVER_DESC "Driver tutorial"

static int __init init_hello_4(void)
{
	printk(KERN_INFO "Hello 4\n");
	return 0;
}

static void __exit exit_hello_4(void)
{
	printk(KERN_INFO "Bye 4\n");
}

module_init(init_hello_4);
module_exit(exit_hello_4);


// Now for licensing, can use both defines or strings
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

// Guide is a little outdated, this was removed from the kernel entirely
//MODULE_SUPPORTED_DEVICE("testdevice");

