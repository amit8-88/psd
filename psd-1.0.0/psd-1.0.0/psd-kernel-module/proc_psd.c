#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/seq_file.h>
#include<linux/task_io_accounting_ops.h>
#include<linux/fdtable.h>
#include<linux/file.h>
#include<linux/fs_struct.h>
#include<linux/types.h>
#include<linux/spinlock.h>
#include<linux/signal.h>
#include<linux/mm_types.h>
#include<linux/resource.h>
static LIST_HEAD(mydrv_list);  /* List Head */
static struct proc_dir_entry *entry = NULL ; 
static struct proc_dir_entry *parent = NULL ; 
static struct task_struct *pd = &init_task;

static void *
mydrv_seq_start(struct seq_file *seq, loff_t *pos)
{
  
  loff_t off = 0;
 
  struct task_struct *task;
 
    for_each_process(task)
  {
	if(*pos==off++) 
		{
                        printk("in start : success %d\n",*pos);
                        return task;
    		}
  }
  printk("in seq_start : over\n");
  return NULL;
}



static void *
mydrv_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
  struct task_struct *task= ((struct task_struct *)v);

  struct list_head *n = list_entry(task->tasks.next,struct task_struct, tasks);
  ++*pos; 

   printk("in seq_next :%d\n",*pos);
   return (n !=pd) ?
   list_entry(task->tasks.next,struct task_struct, tasks) : NULL;
}



static int
mydrv_seq_show(struct seq_file *seq, void *v)
{
   int ret, one;
struct	mm_struct *myptr=NULL;
long *st=NULL;

	
	
   const struct task_struct *p = ((struct task_struct *)v);
   char buf[128];
   memset(buf,0,128);
   printk("in seq_show \n");
	st=(long*)(p->stack);
	myptr=p->mm;
	//if(myptr==NULL)
	//myptr->task_size=0;
	
	//myptr=p->files;
	//files=p->files;	
	//read_lock(p->files->file_lock);
        //one=p->files->next_fd;
        //read_unlock(p->files->file_lock);	        
       //myptr=p->files;
       
//   sprintf(buf,"PID=%d Open_Fds=%lu MaxFDS=%lu CMDNAME=%s\n",p->pid,p->blocked.sig[0],p->blocked.sig[1], p->comm);
sprintf(buf,"PID=%d Stack_Address=%lu No_Files=%d State=%u Priority=%d Static_Priority=%d CMDNAME=%s\n", p->pid,*st, p->files->fdt->max_fds,p->state, p->prio,p->static_prio, p->comm);
   ret = seq_printf(seq,buf);
   printk(KERN_INFO "the return value of seq_printf is %d\n", ret);
   return 0;
}



static void
mydrv_seq_stop(struct seq_file *seq, void *v)
{

 
   printk("in seq_stop:\n");
}


static struct seq_operations mydrv_seq_ops = {
   .start = mydrv_seq_start,
   .next   = mydrv_seq_next,
   .stop   = mydrv_seq_stop,
   .show   = mydrv_seq_show,
};



static int
mydrv_seq_open(struct inode *inode, struct file *file)
{
   
   printk("we are in mydrv_seq_open\n");   //1
 
   return seq_open(file, &mydrv_seq_ops);
}


static struct file_operations mydrv_proc_fops = {
   .owner    = THIS_MODULE,    //this macro will provide the ptr to our module object
   .open     = mydrv_seq_open, /* User supplied */  //passing addresses of functions 
                                                    //to function pointers
   .read     = seq_read,       /* Built-in helper function */
   .llseek   = seq_lseek,       /* Built-in helper function */
   .release  = seq_release,    /* Built-in helper funciton */
};


static int __init
mydrv_init(void)
{
   

  int i;



 
  parent= proc_mkdir("psd",NULL);

  entry = create_proc_entry("pinfo", S_IRUSR, parent);//a file is created 
  
  if (entry) {
  
   entry->proc_fops = &mydrv_proc_fops; 
  }
  else 
  {
	return -EINVAL;
  }
  
 
  printk("we are in init function of the module\n");  //2
  return 0;
}

void mydrv_exit(void)
{
 
 
   remove_proc_entry("pinfo",parent);
   remove_proc_entry("psd", NULL);
   printk("mydrv_exit just executed\n");    //3

}

module_init(mydrv_init);
module_exit(mydrv_exit);
