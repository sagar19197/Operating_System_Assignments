// OS - Assignment 2, Ques 1-
// Sagar Suman, 2019197

// SR_function

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>

pid_t S1_pid;									//global variable for pid of S1

static void SR_handler(int signo){		//definition of  SR signal handler
	int a;
	__asm__ volatile(						//inline assembly
	"rdrand %0"							// RDRAND
	:"=r" (a)
	:
	:"cc"
	);
	
	if(a<0){
		a = a*(-1);
	}
	union sigval data;
	data.sival_int = a;
	//printf("In SR, Random of number is :%d\n",a);
	sigqueue(S1_pid, SIGTERM, data);					//sigqueue
}

int main(int argc, char* argv[]){						//main function
	int num;
	if(argc >1){								
		S1_pid = atoi(argv[1]);
		if(S1_pid< 0){							//error handling
			return 1;
		}
	}
	else{
		return 1;						//error handling
	}  
	//printf("PID of S1 recieved in SR= %d\n", S1_pid);
	if(signal(SIGALRM, SR_handler) == SIG_ERR){		//Signal registration
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
		pause();					//pause
	}
	return 0;
}
