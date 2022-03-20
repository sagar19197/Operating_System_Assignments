// OS - Assignment 2, Ques 1-
// Sagar Suman, 2019197


// main program -

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

void *shared_mem;							//global variable for shared memory for string from ST

static void S1_handler(int signo, siginfo_t *siginfo, void *u){			//Signal Handler for SIGTERM signal
	int value  = siginfo -> si_int;
	//printf("Reciever got : %d\n",value);
	if(value == -1){
		printf("Recieved from ST:  %s\n",(char*) shared_mem);			// for printing string recieved from ST
	}
	else{
		printf("Recieved from SR: Random number is : %d\n",value);		// for printing random number recieved from SR
	}

}

int main(){
	
	int shm_id;										
	shm_id = shmget((key_t) 2019197, 1024, 0666);		//finding shm_id of shared memory with key 2019197 and read and write permission
	shared_mem = shmat(shm_id, NULL, 0);			//attaching process to shared memory
	

	//creating child process S1- 
	
	char *path;
	char *arg1;
	char c[20];
	pid_t S1_pid;						//for S1 pid
	S1_pid = fork();						//FORK system call to create S1
	
	if(S1_pid>=0){
		if(S1_pid == 0){					//child process S1
			//printf("Hello, I am S1, signal registration done\n");
			
			struct sigaction signal_act;			
			signal_act.sa_sigaction = &S1_handler;
			signal_act.sa_flags = SA_SIGINFO;
			if(sigaction(SIGTERM, &signal_act, NULL) == -1){		//Signal registration
				printf("ERROR");
				exit(0);
			}
			while(1){
				pause();				//pause
			}
		}
		else{							//parent process, pid>0
			sleep(2);					//making sure signal registration is done
	
			pid_t sr_pid;
			sr_pid = fork();						// Creating first child SR
			if(sr_pid >=0){
				if(sr_pid == 0){					// SR
					path = "SR_function";
					sprintf(c,"%d",S1_pid); 
					arg1  = c;
					//printf("SR going to call Execl, PID of S1= %d\n",S1_pid);
					execl(path,path,arg1,NULL);		// Execl system call for SR_Function
				}
				else{								//ST
					path = "ST_function";
					sprintf(c,"%d",S1_pid); 
					arg1  = c;
					//printf("ST going to call Execl, PID of S1= %d\n",S1_pid);
					execl(path,path,arg1,NULL);		// Execl system call for ST_function
				}
			}
			else{
				perror("Fork failed error");		//error handling
				return 1;
			}	
		}
	}
	else{						
		perror("Fork failed error");		//error handling
		return 1;
	}
	
	return 0;
}
