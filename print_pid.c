#include <linux/kernel.h>  
#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/sched.h>  
#include <linux/list.h>  

/*************************************************************
* static��Ϊ�˷�ֹ������Ⱦ
* ���ں��еĴ�ӡ������printk������<0>��ʾ����Ϣ�ĵȼ�������ԽС������Խ��
* ��module_init��module_exit����ָ����ں���
������Ƕ���ĺ�������Ϊģ��Ĳ����ɾ����ֻ�е�һ���Ĳ��뺯���Ǳ�Ҫ�ġ�
Ŀǰ������ֻ�Ǵ�ӡ��Ϣ���ں˻����������������û��ռ�ͨ��dmesg������ʣ���
KERN_INFO����־����ע�⣬û�ж��ţ���__init��__exit������ ���� ���ᵽ���������߱�������Ԫ����Ƭ��
�������û��ռ��C�������Ǻܺ����ģ������ں���ȴ���ձ顣
���б��Ϊ__init�ģ����ڳ�ʼ�����ͷ��ڴ��Թ����ã����ǵ�������ȥ�ں˵�������Freeing unused kernel memory��[�ͷ�δʹ�õ��ں��ڴ桭��]����Ϣ�𣿣���
__exit�����������뱻��̬�������ں�ʱ���ú������԰�ȫ���Ż��ˣ�����Ҫ������β��
���module_init()��module_exit()�������꽫reverse_init()��reverse_exit()�������ó�Ϊ����ģ����������ڻص�������
ʵ�ʵĺ������Ʋ�����Ҫ������Գ�����Ϊinit()��exit()������start()��stop()�������ʲô�ͽ�ʲô�ɡ�
���Ƕ��Ǿ�̬�����������ⲿģ���ǿ������ġ�
��ʵ�ϣ��ں��е��κκ������ǲ��ɼ��ģ�������ȷ�ر�������Ȼ�������ں˳���Ա�У�����ĺ�������ģ����ǰ׺��Լ���׳ɵġ�
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

