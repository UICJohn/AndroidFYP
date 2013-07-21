#include "ptree.h"

SYSCALL_DEFINE2(ptree,struct prinfo,*buf,int,*nr){
	int fb;//Feedback
	int *snr;//nr for system
	struct prinfo *sbuf;//buf for system
	//Initial system call
	if(!buf || !nr || *nr<1){
		return -EINVAL;
	}	
	sbuf = kcalloc(*nr,sizeof(struct prinfo),GFP_KERNEL);
	if(!sbuf){
		return -ENOMEM
	}
	fb = copy_from_user(snr,nr,size_of(int));
	if (fb){
		return -EFAULT; 
	}
	fb = copy_from_user(sbuf,buf,size_of(struct prinfo));
	if(fb){
		return -EFAULT;
	}

	fb = process_tree();
	if(!fb){
		return false;
	}
	return fb;
}

int process_tree(){
	return 1;
}
	
