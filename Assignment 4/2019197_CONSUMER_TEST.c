// OS Assignment 4
// Sagar Suman, 2019197

// CONSUMER CODE -


#define _GNU_SOURCE
#include<sys/syscall.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){
	
	long rand_no, res;	
	
	while(1)
	{
		res = syscall( 448 , &rand_no);					//449 is the reader() system call				
			
		if(res < 0){
			printf("SOMETHING BAD HAPPENED ");
			return -1;
		} 	
		else{
			printf("Cosumer has consumed : %lu\n", rand_no);			//printing
		}
	}

	return 0;
}