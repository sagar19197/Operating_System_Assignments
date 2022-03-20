// OS Assignment 4
// Sagar Suman, 2019197

// PRODUCER CODE -


#define _GNU_SOURCE
#include<sys/syscall.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){

	int n  = 8;
	long rand_no;
	int fd;
	long res;
	if((fd = open("/dev/urandom" , O_RDONLY)) >= 0 ){ 	//open /dev/random for reading random number
		while(1)
		{
		if(read(fd, &rand_no , sizeof(long)) >= 0){ 			// read number
			
			res = syscall( 449 , &rand_no);					//449 is the writer() system call				
			
			if(res < 0){
				printf("SOMETHING BAD HAPPENED ");
				return -1;
			} 	
			else{
				printf("Producer has produced : %lu\n", rand_no);			//printing
			}
	
		}
		else{
			printf("ERROR IN READ !!");
			return -1;
		}
		}

	}
	else{
		perror(" ERROR in OPEN !!");
		return -1;
	}

	close(fd);

	return 0;
}
