// Creates a read-only device that sais how many times a file has been opened
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	// For put_user

// These are prototypes, they would normally go in a .h file
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_close(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev"	// Device name as it appears in /proc/devices
#define BUF_LEN 80		// Max length of the message from the device


// Since global variables are static, they are global from within the file
static int Major;		// Major number assigned to our device driver
static int Device_Open = 0;	// Tells us if the device is open and lets us control multiple accesses to it
static char msg[BUF_LEN];	// The msg the device will give when asked
static char *msg_ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_close
};

// Called on module load
int init_module(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if(Major < 0){
		printk(KERN_ALERT "Registering char device vailed with %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "I was assigned major number %d. Talk to\n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return SUCCESS;
}

// Called on module unload
void cleanup_module(void)
{
// POST NOTE: all what's written below needed to change, since unregister_chrdev was changed to be a void instead of an int
/*	// Unregister the device
	int ret = unregister_chrdev(Major, DEVICE_NAME);
	if(ret < 0)
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
*/
// End post note
	unregister_chrdev(Major, DEVICE_NAME);
	// Still need to unregister the device though
}

// Called when a process tries to open the device file
//	E.G. "cat /dev/mycharfile"
static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	if(Device_Open)
		return -EBUSY;
	Device_Open++;
	sprintf(msg, "I already told you %d times!\n", counter++);
	msg_ptr = msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

// Called when a process closes the device file
static int device_close(struct inode *inode, struct file *file)
{
	Device_Open--;	// Now ready for next caller

	// Decrement the usage count, else one you opened the file, you'll never get rid of this module
	module_put(THIS_MODULE);
	return SUCCESS;
}

// Called when a process, with the dev file already open, tries to read from it
static ssize_t device_read(struct file *filp,	// That's why we include fs.h
			   char *buffer,	// Buffer to be filled with data
			   size_t length,	// Buffer length
			   loff_t *offset)
{
	// Number of bytes actuually written into the buffer
	int bytes_read = 0;

	// If we are at the end of the message, return 0, signifying EOF
	if(*msg_ptr == 0)
		return SUCCESS;

	// Finally, put data into the buffer
	while(length && *msg_ptr){
		// The buffer is in the user data segment, not the kernel one
		// this means that '*' assignments won't work.
		// We need to use put_user, which copied data from the kernel
		// data segment to the user data segment
		put_user(*(msg_ptr++), buffer++);
		length--;
		bytes_read++;
	}
	// MOST read functions return the number of bytes put into the buffer
	return bytes_read;
}

// Called when a process writes to dev file: echo "hi" > /dev/hello
static ssize_t device_write(struct file *filp,
			    const char *buff,
			    size_t len,
			    loff_t *off)
{
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;
}


MODULE_LICENSE("GNU");	// So that make stops crying
