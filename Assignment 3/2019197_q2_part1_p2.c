// Os Assignment 3
// Name - Sagar Suman, 
// Roll No. 2019197

// Question 2, part 1 - Unix domain Sockets, process B


#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>			//for sockets
#include<sys/un.h>

int main(){

	char received_num[5][4];			//received string of characterss
	int id[5];						// Corresponding Ids of strings
	int fd;							//file descriptor	

	char received_id[5][3];
	char line[60];
	int max_id = 0;
	int i, j, k;

	int fd2;
	
	fd2 = socket(AF_UNIX, SOCK_SEQPACKET,0);			// using socket, passing SOCK_SEQPACKET
	if(fd2 == -1){
		perror(" Error in socket ");
		return 1;
	}

	struct sockaddr_un p2;								// setting unix domain socket address structure
	memset(&p2, 0 , sizeof(struct  sockaddr_un));
	p2.sun_family = AF_UNIX;
	strncpy(p2.sun_path, "socket", sizeof(p2.sun_path)-1);
	
	if(connect(fd2, (const struct sockaddr *) &p2, sizeof(struct sockaddr_un)) == -1){			//connect
		perror("Error in connect");						
		return 1;
	}
	//printf("Connection successful\n");

	while(max_id < 49){
	
		if(read(fd2, line, 60) == -1){					//read
			perror("Error in reading");
			return 1;
		}
		//printf("Message is received. Message is : %s\n", line);
		
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
		if(write(fd2, line, strlen(line)+1) == -1){						//write
			perror("Error in write");
			return 1;
		}
	
	}
	
	close(fd2);							//closing socket	

	return 0;

}