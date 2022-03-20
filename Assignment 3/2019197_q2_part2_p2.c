// Os Assignment 3
// Name - Sagar Suman, 
// Roll No. 2019197

// Question 2, part 2 - FIFO process B  

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
	
	char received_num[5][4];			//received string of characterss
	int id[5];						// Corresponding Ids of strings
	int fd;							//file descriptor	

	char received_id[5][3];
	char line[50];
	int max_id = 0;
	int i, j, k;
	while(max_id < 49){
		
		fd = open("q2_fifo",O_RDONLY);			//open with read only
		if(fd == -1){
			printf("Error");
			return 1;
		}
		
		if(read(fd, line , 36) == -1){		//reading
			printf("ERROR");
			return  1;
		}
		//printf("%s\n",line);
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
		close(fd);				//closing

		
		fd = open("q2_fifo",O_WRONLY);		//open with write only
		if(fd == -1){
			printf("Error");
			return 1;
		}
													//writting
		if(write(fd, &max_id , sizeof(int)) == -1){
			printf("ERROR");
			return 1;
		}
		close(fd);									//closing
		//printf("WRITTEN  highest as :%d \n",max_id);
		
	
	}

	return 0;
}

