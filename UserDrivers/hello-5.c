#include <linux/module.h>
#include <linux/moduleparam.h>	// Used to pass arguments to modules (via the module_param() macro)
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
// MODULE_CREATOR("Francesco Spangaro");

static short int myShort = 1;
static int myInt = 500;
static long int myLong = 9999;
static char *myString = "hello";
static int myIntArray[2] = {-1, -1};
static int arr_argc = 0;

/*
	module_param(foo, int, n);
	foo is the parameters name
	int is it's data type
	n is the "permission bits"
	needed for exposing params in sysfs (if non zero) at a larger stage
*/

module_param(myShort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myShort, "A short int");

module_param(myInt, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myInt, "An int");

module_param(myLong, long, S_IRUSR);
MODULE_PARM_DESC(myLong, "A long int");

module_param(myString, charp, 0000);
MODULE_PARM_DESC(myString, "A string");


/*
	module_param_array(name, type, n, perm);
	name: the parameters name
	type: is it's data type
	n: is a pointer to the value that will store the number of elements in the array, which will be
		initialized by the user at module loading time
	perm: permission bits
*/

module_param_array(myIntArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myIntArray, "An array of integers");

static int __init hello_5_init(void)
{
	int i;
	printk(KERN_INFO "Hello 5\n==================\n");
	printk(KERN_INFO "myShort is a short integer %hd\n", myShort);
	printk(KERN_INFO "myInt is an integer %d\n", myInt);
	printk(KERN_INFO "myLong is a long integer %ld\n", myLong);
	printk(KERN_INFO "myString is a string %s\n", myString);
	for(i = 0; i < (sizeof(myIntArray) / sizeof(int)); i++)
	{
		printk(KERN_INFO "myIntArray[%d] = %d\n", i, myIntArray[i]);
	}
	printk(KERN_INFO "Got %d arguments for myIntArray \n", arr_argc);
	return 0;
}

static void __exit hello_5_exit(void)
{
	printk(KERN_INFO "Bye world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);


