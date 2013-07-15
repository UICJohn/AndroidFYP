#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "work2.h"
#include "../goldfish/include/linux/prinfo.h"

int main(int argv,char** argc){
  	int nr = DEFAULT_SIZE;
	struct prinfo *buf;
	if(argv > 1){
		if(!(nr = is_Num(argc[1]))){
			nr = DEFAULT_SIZE;
		}
	}
	printf("Assign size of %d\n",nr);
	buf = calloc(nr,sizeof(struct prinfo));
	if(!buf){
		printf("Could not allocate buffer for buf!\b");
		exit(-1);
	}
	
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
