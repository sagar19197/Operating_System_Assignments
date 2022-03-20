// Os Assignment 3
// Name - Sagar Suman, 
// Roll No. 2019197

// Question 2, part 3 - Message Queues, process B


#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<mqueue.h>			//for POSIX message queue


int main(){
	
	char received_num[5][4];			//received string of characterss
	int id[5];						// Corresponding Ids of strings
	int fd;							//file descriptor	

	char received_id[5][3];
	char line[60];
	int max_id = 0;
	int i, j, k;

	mqd_t p1_qd;			//queue descriptor for p1
	mqd_t p2_qd;			//queue descriptor for p2

	p2_qd = mq_open("/p2_queue",O_RDONLY);		//using mq_open to create p2 
	if(p2_qd == -1){
		perror("Error in mq_open ");
		return 1;
	}	
	
	p1_qd = mq_open("/p1_queue", O_WRONLY);		//using mq_open to open p1
	if(p1_qd == -1){
		perror("Error in mq_open of p1");
		return 1;
	}
	
	while(max_id < 49){
	
		if(mq_receive(p2_qd,line, 60 , NULL) == -1){						//using mq_receive to receive 5 random strings from p1 
			perror("ERROR in mq_receive");
			return 1;
		}
	
		//printf("MESSAGE RECEIVED. Message is : %s \n",line);
		
		i = 0;
		j = 0;
		k = 0;
		while(line[i] != '\0'){
			if(line[i] != ' '){
				if(j < 5){
					received_num[j][k] = line[i];
					k++;
				}
				else{
					received_id[j-5][k] = line[i];
					k++;
				}
			}
			else{
				if( j < 5){
					received_num[j][k] = '\0';
					j++;
					k = 0;
				}
				else{
					received_id[j-5][k] = '\0';
					id[j-5] = atoi(received_id[j-5]);
					j++;
					k=0;
					
				}
			}
			i++;
		} 
								
										//printing the 5 received strings and thier ids
		for(int i =0;i<5;i++){
			printf("Random String received from P1: %s and its ID is : %d\n", received_num[i],id[i]);
		}

											// Finding highest ID- 
		for(int i =0;i<5;i++){
			if(max_id < id[i]){
				max_id = id[i];
			} 
		}
		
		sprintf(line,"%d",max_id);
		if(mq_send(p1_qd,line, strlen(line)+1 , 0) == -1){						//using mq_send
			perror ("ERROR in mq_send");
			return 1;
		}
		//printf("MESSAGE SENT SUCCESSFULLY\n");

	}
	
	return 0;
}
