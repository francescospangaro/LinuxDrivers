// Created by following The Linux Kernel Module Programming Guide
#include <linux/module.h>	// Needed by all modules
#include <linux/kernel.h>	// Needed for KERN_INFO

int init_module(void)
{
	printk(KERN_INFO "Hello world 1\n");
	return 0;	// If the return value != 0, then the module couldn't be loaded
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1\n");
}

// KERN_INFO is the printk priority value

// This I added to update the guide, since now make won't build if there is no MODULE_LICENCE()
MODULE_LICENSE("GPL");
