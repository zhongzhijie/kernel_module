#include <linux/kernel.h>  
#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/sched.h>  
#include <linux/list.h>  

/*************************************************************
* static是为了防止命名污染
* 在内核中的打印函数是printk，其中<0>表示该信息的等级，数字越小，级别越高
* 用module_init和module_exit宏来指定入口函数
这里，我们定义的函数被称为模块的插入和删除。只有第一个的插入函数是必要的。
目前，它们只是打印消息到内核环缓冲区（可以在用户空间通过dmesg命令访问）；
KERN_INFO是日志级别（注意，没有逗号）。__init和__exit是属性 —— 联结到函数（或者变量）的元数据片。
属性在用户空间的C代码中是很罕见的，但是内核中却很普遍。
所有标记为__init的，会在初始化后释放内存以供重用（还记得那条过去内核的那条“Freeing unused kernel memory…[释放未使用的内核内存……]”信息吗？）。
__exit表明，当代码被静态构建进内核时，该函数可以安全地优化了，不需要清理收尾。
最后，module_init()和module_exit()这两个宏将reverse_init()和reverse_exit()函数设置成为我们模块的生命周期回调函数。
实际的函数名称并不重要，你可以称它们为init()和exit()，或者start()和stop()，你想叫什么就叫什么吧。
他们都是静态声明，你在外部模块是看不到的。
事实上，内核中的任何函数都是不可见的，除非明确地被导出。然而，在内核程序员中，给你的函数加上模块名前缀是约定俗成的。
*************************************************************/
static __init int print_pid(void)  
{  
    struct task_struct *task,*p;  
    struct list_head *pos;  
    int count=0; 
        
    printk(KERN_INFO "Hello,let begin\n");  
    task=&init_task;  
    list_for_each(pos,&task->tasks)  
    {  
        p=list_entry(pos,struct task_struct,tasks);  
        count++;  
        printk("%d---->%s\n",p->pid,p->comm);  
    }  
    
    printk("the number of process is:%d\n",count);  
    
    return 0;  
}  
static __exit void print_exit(void)  
{  
    printk("<0>end!\n");  
}  

module_init(print_pid);  
module_exit(print_exit);  
MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhongzhijie");
MODULE_DESCRIPTION("Kernel Module");
MODULE_ALIAS("print pid module"); 

