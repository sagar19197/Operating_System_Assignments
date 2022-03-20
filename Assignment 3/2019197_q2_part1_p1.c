// Os Assignment 3
// Name - Sagar Suman, 
// Roll No. 2019197

// Question 2, part 1 - Unix domain Sockets, process A


#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>			//for sockets
#include<sys/un.h>


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

	int fd, fd2;						//for socket
	char send_string[60];

	unlink("socket");			//remove the previous socket
	
	fd = socket(AF_UNIX, SOCK_SEQPACKET,0);			// using socket , passing SOCK_SEQPACKET
	if(fd == -1){
		perror(" Error in socket ");
		return 1;
	}

	struct sockaddr_un p1;								// setting unix domain socket address structure
	memset(&p1, 0 , sizeof(struct  sockaddr_un));
	p1.sun_family = AF_UNIX;
	strncpy(p1.sun_path, "socket", sizeof(p1.sun_path)-1);
	
	if(bind(fd, (const struct sockaddr *) &p1, sizeof(struct sockaddr_un)) == -1){			//using bind
		perror("Error in bind ");
		return 1;
	}

	if(listen(fd,2) == -1){						//listen , backlog is 2
		perror("Error in listen");
		return 1;
	}

	printf("Waiting to accept connection\n");

	fd2 = accept(fd, NULL, NULL);				//accept
	if(fd2 == -1){
		perror("Error in accept");
		return 1;
	}
	
	printf("Connection established\n");

	int count = 0, count_rec;					//starting with 0 index
	while(count<49){
									//creating the string with 5 random number string and their IDs(indexes)
		if(count+4>49){
			printf("ERROR, index recieved may exceed length of array");
			return 1;
		}
		sprintf(send_string,"%s %s %s %s %s %d %d %d %d %d ",arr[count],arr[count+1],arr[count+2],arr[count+3],arr[count+4],count,count+1,count+2,count+3,count+4);
		//printf("Preparing send_string - %s\n", send_str);	
	
		if(write(fd2, send_string, strlen(send_string)+1) == -1){						//write
			perror("Error in write");
			return 1;
		} 		
		printf("Message sent successfully.\n");
	
		if(read(fd2, send_string, 60) == -1){						//read
			perror("Error in reading");
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

	close(fd2);					//closing sockets
	close(fd);
	unlink("socket");				//unlinking
	
	return 0;
}