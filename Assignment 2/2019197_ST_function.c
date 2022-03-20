// OS - Assignment 2, Ques 1-
// Sagar Suman, 2019197

// ST_function

#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<time.h>
#include<string.h>


pid_t S1_pid;									//global variable for pid of S1
uint64_t clock_cycle,time1;
uint32_t eax,edx;
int day,hour,min,sec, time0;
time_t time2;	
void *shared_mem;							//global variable for shared memory
char send_string[150];						//global variable for date-time string 


static void ST_handler(int signo){		//definition of  ST signal handler
														// Inline assembly
	asm volatile("rdtsc\n\t"							// RDTSC 
					:"=a" (eax), "=d" (edx)
					:
					:
					);
	
	clock_cycle = (uint64_t)eax | (((uint64_t) edx) <<32);	//random number obtained from rdtsc
	time1 = (clock_cycle/2.4)*0.000000001;
	time0 = time1;
	day = time0/86400;
	time0 = time0 - (day*86400);
	hour = time0/3600;
	time0 = time0 - (hour*3600);
	min = time0/60;
	time0 = time0 - (min*60);
	sec = time0;
	time(&time2);
	sprintf(send_string,"Time elapsed : %d Days, %d Hours, %d Minutes, %d Seconds since the Reboot. Current date and time : %s",day,hour,min,sec,ctime(&time2));
	//printf("In ST : %s\n",send_string);
	
	strcpy(shared_mem, send_string);		//Writting string to share memory
	union sigval data;
	data.sival_int = -1;
	sigqueue(S1_pid, SIGTERM, data);					//sigqueue sending -1 to S1 
	  
}



int main(int argc, char *argv[]){				//main function
	
	int shm_id;
	shm_id = shmget((key_t) 2019197, 1024, 0666|IPC_CREAT);		//creating shared memory with key 2019197 and read and write permission
	shared_mem = shmat(shm_id, NULL, 0);							//attaching process to shared memory
	
	if(argc >1){								
		S1_pid = atoi(argv[1]);
		if(S1_pid< 0){							//error handling
			return 1;
		}
	}
	else{
		return 1;						//error handling
	}  
	//printf("PID of S1 recieved in ST= %d\n", S1_pid);
	if(signal(SIGALRM, ST_handler) == SIG_ERR){		//Signal registration
		printf("ERROR");
		exit(1);
	}

	struct itimerval timer;				
	timer.it_value.tv_sec = 1;					//time 1 sec
	timer.it_value.tv_usec = 0.000001;		// time in micro second
	
	timer.it_interval = timer.it_value;
																	
	if(setitimer(ITIMER_REAL, &timer, NULL) == -1){		// setitimer
		perror("ERROR");
		exit(1);
	}
	while(1){
		pause();											//pause
	}
	return 0;
}
