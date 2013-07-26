#include "ptree.h"

SYSCALL_DEFINE2(ptree , struct prinfo , *buf , int , *nr){
	int fb;
	struct prinfo *sbuf;
	int lock=0;
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
	fb = process_tree(sbuf);
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

int process_tree(struct prinfo *sbuf){
	int counter = 0;
	printk(KERN_INFO "PROCESS TREE BEGIN...[SNR = %d]\n",snr);
	struct task_struct *root = get_init_task();
	dfs_recu_travel(root,sbuf,&counter);
	printk(KERN_INFO "PROCESS TREE OVER..\n");
	return counter;
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

void process_node(struct task_struct *task,struct prinfo *sbuf,int *counter){
    if(!is_a_process(task)) 
      return;
    printk(KERN_INFO"------------[task]------------: \n[PID]=%d\n[NAME]=%s\n[COUNTER]=%d\n",task -> pid,task->comm,*counter);
		struct prinfo new_node;
		struct task_struct *first_child;
		struct task_struct *first_sibling;
		init_node(&new_node,task);	
		if(has_children(task)){
			first_child = list_entry(
					task -> children.next,
					struct task_struct,
					sibling
					);
			new_node.first_child_pid = first_child -> pid;
		}
		if(has_sibling(task)){
			first_sibling = list_entry(
					task -> sibling.next,
					struct task_struct,
					sibling	
					);
			new_node.next_sibling_pid = first_sibling -> pid;
		}
		new_node.uid = task_uid(task);	
		strncpy(sbuf -> comm, task -> comm,64);
		sbuf[(*counter)+1] = new_node; 		
		(*counter) ++;	
}

void dfs_recu_travel(struct task_struct *_cur,struct prinfo *sbuf,int *counter){
  if((*counter) > 1 && _cur -> pid ==0)
    return;
	if((*counter)>snr){
		return;
  }
  struct task_struct *cur = _cur;
	process_node(cur,sbuf,counter);
	if(has_children(cur)){
		struct task_struct *first_child = list_entry(
							                                cur -> children.next,
							                                struct task_struct,
							                                sibling
						                            );
		dfs_recu_travel(first_child,sbuf,counter);
	}
	if(has_sibling(cur)){
	  struct task_struct *next_sibling = list_entry(
		  cur -> sibling.next,
		  struct task_struct,
		  sibling
		  );
	  dfs_recu_travel(next_sibling,sbuf,counter);
	}
	printk(KERN_INFO"DFS_RECU_TRAVEL OVER ...\n");
	
}

void init_node(struct prinfo *new_node,struct task_struct *task){
	new_node -> state = task -> state;
	new_node -> pid = task -> pid;
	new_node -> parent_pid = task -> parent -> pid;
	new_node -> first_child_pid = 0;
	new_node -> next_sibling_pid = 0;
	new_node -> uid = 0;
	printk(KERN_INFO"INIT NODE...\n");
}


