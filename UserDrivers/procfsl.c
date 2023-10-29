// Crate a "file" in proc
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>	// Necessary since we are using proc fs

#define procfs_name "helloworld"

// This holds info about the /proc file
struct proc_dir_entry *our_proc_file;

// Initialize the proc fs file
// 	For a full description, look up Example 5-1 in The Linux Kernel Programming Guide (free online)
int procfile_read(char *buffer,
		  char **buffer_location,
		  off_t offset, int buffer_length, int *eof, void *data)
{
	int ret;
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);

	// We give all of our info in one go, so if the user asks if there's more, the standard answer is no
	// Important since the standard read from the library would continue to issue that is has no more
	// information, or until its buffer is filled.
	if(offset > 0){
		// Finished our read, return 0
		ret = 0;
	}else{
		// Fill the buffer, then return buffer size
		ret = sprintf(buffer, "Helloworld!\n");
	}
	return ret;
}

int init_module(void)
{
	our_proc_file = create_proc_entry(procfs_name, 0644, NULL);
	if(our_proc_file == NULL){
		remove_proc_entry(procfs_name, &proc_root);
		printk(KERN_ALERT "Error: could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
	}

	our_proc_file->read_proc	= procfile_read;
	our_proc_file->owner		= THIS_MODULE;
	our_proc_file->mode		= S_IFREG | S_IRUGO;
	our_proc_file->uid		= 0;
	our_proc_file->gid		= 0;
	our_proc_file->size		= 37;

	printk(KERN_INFO "/proc/%s created\n", procfs_name);
	return 0;
}

void cleanup_module()
{
	remove_proc_entry(procfs_name, &proc_root);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}

MODULE_LICENSE("GNU");
