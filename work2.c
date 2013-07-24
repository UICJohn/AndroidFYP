#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "work2.h"
#include "../goldfish/include/linux/prinfo.h"

int main(int argc, char** argv){
  	int nr = DEFAULT_SIZE;
	int fb;//Feedback from syscall
	struct prinfo *buf;
	if(argc > 1){
		if(!(nr = is_Num(argv[1]))){
			nr = DEFAULT_SIZE;
		}
	}
	printf("Assign size of %d...\n",nr);
	buf = calloc(nr,sizeof(struct prinfo));
	if(!buf){
		printf("Could not allocate buffer for buf!\b");
		exit(-1);
	}
	printf("SYSTEM CALL\n");
	fb = syscall(223,buf,&nr);
	printf("Feedback = %d",fb);
	return 0;
}

int is_Num(char* element){
	char* temp=element;
	if(temp!=NULL){
		while(*temp){
			if(!isdigit(*temp))return 0;
			temp++;
		}
		return atoi(element);
	}
	else return 0;
}
