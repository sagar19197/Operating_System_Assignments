// Os Assignment 3
// Name - Sagar Suman, 
// Roll No. 2019197

// Question 2, part 2 - FIFO process A  


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>

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
	
	if(mkfifo("q2_fifo",0777) == -1  && errno!= EEXIST){		//mkfifo - file named q2_fifo 
		printf("file can not be created\n");
		return 1;
	}
	
	int count = 0,count_rec;					//starting with 0 index
	char send_str[50];
	int fd,len;							//file descriptor
	while(count<49){
									//creating the string with 5 random number string and their IDs(indexes)
		if(count+4>49){
			printf("ERROR, index recieved may exceed length of array");
			return 1;
		}
		sprintf(send_str,"%s %s %s %s %s %d %d %d %d %d ",arr[count],arr[count+1],arr[count+2],arr[count+3],arr[count+4],count,count+1,count+2,count+3,count+4);
		//printf("%s\n", send_str);
		fd = open("q2_fifo", O_WRONLY);			//opening with Write only
		if(fd == -1){
			printf("Error");
			return 1;
		}
		
		if(count+4<10){				//length of string is 29
			len = 31;
		}
		else{
			len = 36;
		}
		if(write(fd , send_str , len) ==-1){		//writting
			printf("Error in writting");
			return 1;
		}
		
		printf("Sending next 5 strings from ID: %d\n",count);
		close(fd);					//closing
		
									// for receiving highest ID from p2
		
		fd = open("q2_fifo", O_RDONLY);			//opening with read only
		if(fd == -1){
			printf("Error");
			return 1;
		}					
		if(read(fd, &count_rec, sizeof(int)) == -1){		//reading
			printf("ERROR");
			return 1;
		}	
		
		close(fd);					//closing
		printf("Recieved highest ID from P2 : %d\n", count);
		if(count+4 == count_rec){
			count = count_rec;
		}
		else{
			printf("Not a correct Acknowledgement\n");
			return 1; 
		}
		count++;
	}	
	
	return 0;
}