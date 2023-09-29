#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Nair, on Elementary");
MODULE_DESCRIPTION("This should hopefully mimic the pstree command.");

struct task_struct *task;        //Struct from sched to read all the tasks
struct task_struct *task_child;  //To traverse through children 
struct list_head *list;          //Structure to traverse through the children list


void procs_info_print(void)
{
	for_each_process(task)
	{	printk(KERN_INFO "\n  [%d%18s]--\n",task->pid,task->comm);
		list_for_each(list,&task->children)
		{
			task_child = list_entry( list,struct task_struct,sibling);
			printk(KERN_INFO "\t\t\t\t   |_____ [%d %s]",task_child->pid,task_child->comm);
		}
	
	//printk("-"); //Testing, doesnt look good
	}

}

static int __init iterate_init(void)               
{  
       	printk(KERN_INFO "%s","LOADING MODULE\n");   
    	procs_info_print();
	return 0;

}               
    
static void __exit cleanup_exit(void)        
{
    printk(KERN_INFO "%s","REMOVING MODULE\n");
}                

module_init(iterate_init);    /*    Load Module MACRO    */
module_exit(cleanup_exit);    /*    Remove Module MACRO    */

