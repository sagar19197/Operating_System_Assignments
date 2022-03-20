// Os Assignment 3
// Name - Sagar Suman, 
// Roll No. 2019197

// Question 2, part 3 - Message Queues, process A
  

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<mqueue.h>			//for POSIX message queue

int main(){
	
									//generating array of 50 random strings
	char arr[50][4];				//taking length of strings as 3
	int num;

	char alpha[26] ="abcdefghijklmnopqrstuvwxyz";
	for(int i=0 ; i<50 ; i++){
		for(int j =0;j<3;j++){
			num = rand()%26;
			arr[i][j] = alpha[num];
		}
		arr[i][3] = '\0';
	}
	
	mqd_t p1_qd;			//queue descriptor for p1
	mqd_t p2_qd;			//queue descriptor for p2

	char send_string[60];	

	struct mq_attr p1_attributes;		//for attributes of first message queue for p1
	p1_attributes.mq_maxmsg = 1;		// for max numbers of messages
	p1_attributes.mq_msgsize = 50;			//for maximum message size
	
	p1_qd = mq_open("/p1_queue", O_CREAT | O_RDONLY , 0666, &p1_attributes);		//using mq_open to create p1 queue descriptor 
	if(p1_qd == -1){
		perror("Error in mq_open ");
		return 1;
	} 
		
	struct mq_attr p2_attributes;		//for attributes of second message queue for p2
	p2_attributes.mq_maxmsg = 1;		// for max numbers of messages
	p2_attributes.mq_msgsize = 50;			//for maximum message size
	
	p2_qd = mq_open("/p2_queue",O_CREAT | O_WRONLY , 0666, &p2_attributes);		//using mq_open to create p2 queue descriptor
	if(p2_qd == -1){
		perror("Error in mq_open of p2");
		return 1;
	}
	
	int count = 0, count_rec;					//starting with 0 index
	while(count<49){
									//creating the string with 5 random number string and their IDs(indexes)
		if(count+4>49){
			printf("ERROR, index recieved may exceed length of array");
			return 1;
		}
		sprintf(send_string,"%s %s %s %s %s %d %d %d %d %d ",arr[count],arr[count+1],arr[count+2],arr[count+3],arr[count+4],count,count+1,count+2,count+3,count+4);
		//printf("Preparing send_string - %s\n", send_str);	
		
		if(mq_send(p2_qd,send_string, strlen(send_string)+1 , 0) == -1){						//using mq_send to send string to p2_qd
			perror ("ERROR in mq_send");
			return 1;
		}
		printf("MESSAGE SENT SUCCESSFULLY\n");
	

		if(mq_receive(p1_qd,send_string, 60 , NULL) == -1){						//using mq_receive for receiving highest id
			perror("ERROR in mq_receive");
			return 1;
		}
		
		count_rec  = atoi(send_string);
		printf("MESSAGE RECEIVED. Highest ID received : %d \n",count_rec);
		
		if(count+4 == count_rec){
			count = count_rec;
		}
		else{
			printf("Not a correct Acknowledgement\n");
			return 1; 
		}
		
		count++;		//for next five
	}
	
	
	if(mq_close(p1_qd) == -1){												//closing p1_qd
		perror("Error in mq_close");
		return 1;
	}
	
	if(mq_unlink("/p1_queue") == -1){										//unlinking p1
		perror("Error in mq_unlink");
		return 1;
	}

	if(mq_close(p2_qd) == -1){												//closing p2_qd
		perror("Error in mq_close");
		return 1;
	}
	
	if(mq_unlink("/p2_queue") == -1){										//unlinking p2
		perror("Error in mq_unlink");
		return 1;
	}

	
	return 0;
}