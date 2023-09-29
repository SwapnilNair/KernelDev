#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Nair, on Elementary");
MODULE_DESCRIPTION("This should hopefully mimic the pstree command.");


void procs_info_print(struct task_struct *task)
{
struct task_struct *task_child;  //To traverse through children 
struct list_head *list;          //Structure to traverse through the children list

		list_for_each(list,&task->children)
		{
			task_child = list_entry( list,struct task_struct,sibling);
			printk(KERN_INFO "   |_____ [%d %10s]",task_child->pid,task_child->comm);
			procs_info_print(task_child);		
						
		}
}

static int __init iterate_init(void)               
{  
       	printk(KERN_INFO "%s","Module nair loaded. Execution below.\n");   
    	procs_info_print(&init_task);
	return 0;
}               
    
static void __exit cleanup_exit(void)        
{
    printk(KERN_INFO "%s","Removing the module- Swapnil\n");
}                

module_init(iterate_init);    
module_exit(cleanup_exit);   

