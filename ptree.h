#ifndef PTREE_H_
#define PTREE_H_

#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <asm-generic/errno-base.h>
#include <linux/stddef.h> /* for true and false */
#include <asm/uaccess.h>

int snr;


/*
**function
*/
int process_tree(struct prinfo *sbuf);
int has_children(struct task_struct *task);
int has_sibling(struct task_struct *task);
void auto_lock(int *lock);
struct task_struct *get_init_task(void);
void process_node(struct task_struct *task,struct prinfo *sbuf,int *counter);
int is_a_process(struct task_struct *task);
void init_node(struct prinfo *new_node , struct task_struct *task);
void dfs_recu_travel(struct task_struct *cur,struct prinfo *sbuf,int *counter);
#endif
