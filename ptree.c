#include "ptree.h"

SYSCALL_DEFINE2(ptree , struct prinfo , *buf , int , *nr){
	int fb;//Feedback
	int snr;//nr for system
	struct prinfo *sbuf;//buf for system
	int lock=0;
	//Initial system call
	if(!buf || !nr || *nr<1){
		return -EINVAL;
	}	
	sbuf = kcalloc(*nr,sizeof(struct prinfo),GFP_KERNEL);
	if(!sbuf){
		return -ENOMEM;
	}
	fb = copy_from_user(&snr,nr,sizeof(int));
	if (fb){
		return -EFAULT; 
	}
	fb = copy_from_user(sbuf,buf,sizeof(struct prinfo)* *nr);
	if(fb){
		return -EFAULT;
	}
	auto_lock(&lock);
	fb = process_tree(sbuf,&snr);
	auto_lock(&lock);
	if(!fb){
		return false;
	}
	fb = copy_to_user(nr,&snr,sizeof(int));
	if(fb){
		return -1 * EFAULT;
	}
 	fb = copy_to_user(buf,sbuf,sizeof(struct prinfo)* *nr);
	if(fb){
		return -1 * EFAULT;
	}

	kfree(sbuf);
	return fb;
}

int process_tree(struct prinfo *sbuf,int *snr){
	printk(KERN_INFO "PROCESS TREE BEGIN...\n");
	struct task_struct *cur = get_init_task();
	printk(KERN_INFO "PROCESS TREE OVER..\n");
	return 1;
}

struct task_struct *get_init_task(void){
	return &init_task;
}

int has_children(struct task_struct *task){
	struct list_head *children;
	if(!task){
		return false;
	}
	children = &task->children;
	if(list_empty(children)){
		return false;
	}
	return true;
}
	
int has_sibling(struct task_struct *task){
	struct list_head *head= &task -> parent -> children;
	if(!task){
		return false;
	}
	if(list_is_last(&task -> sibling,head)){
		return false;
	}
	return true;
}
int is_a_process(struct task_struct *task){
	if(!thread_group_empty(task)){
		if(!thread_group_leader(task)){
			return false;
		}
	}	
	return true;
}

void auto_lock(int *lock){
	if(!lock){
		read_lock(&tasklist_lock);
		*lock = 1;
	}
	else{
		read_unlock(&tasklist_lock);
		*lock = 0;
	}
	return;
}

void process_node(struct prinfo *buf,struct task_struct *task){
}

struct task_struct *get_next_node(struct task_struct *cur){
	struct task_struct *node = cur;
	return node;
}


