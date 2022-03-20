/* SAGAR SUMAN,2019197 - Assignment1*/
/* Ques 1 part 1*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

void Avg_sec(char sec);		//declaring function which will parse csv file and calulate
								// average of assignments of section sec


int main(){						//main 
	int stat;
	pid_t pid;					//for process id
	pid = fork();				//FORK system call
	if(pid>=0){
		if(pid == 0){			//child process
			Avg_sec('A');				//calling function for section A
			exit(0);					//EXIT system call
		}
		else{							//parent process, pid>0
			
			waitpid(pid,&stat,0);		//WAITPID system call- if pid>0 (parent process) will wait for child 
										//having specified pid to terminate, 
			Avg_sec('B');				//calling function for section B
		}
	}
	else{						
		perror("Fork failed error");		//error handling
		return 1;
	}
	return 0;
}


void Avg_sec(char sec){				//defining function
	
	int file;
	file = open("student_record.csv", O_RDONLY);		//OPEN system call
	
	if(file==-1){				//file not exist
		perror("FILE NOT FOUND");
		exit(1);
	}
	
	char line[150];		//line
	char value[20];	//for substring in line
	int number;		//for number by converting substring into int
	int n = 98;
	int line_length = 50;
	
	int assignments[6] = {0,0,0,0,0,0};		//6 assignments array;
	char section = sec;							//desired section
	
	if(read(file,line,130)<=0){		//handling empty file 
		printf(" Empty file \n");
		exit(1);
	}

	lseek(file,n,SEEK_SET); 			// LSEEK System call - removing label titles	
	
	int i;						//for traversing
	int j; 						//for extracting value
	int items;					//diffrent items in line
	int desired ;		//for desired section
	int total = 0;					//for total number of students in desired section
	
	while(read(file,line,line_length)){		//READ system call 
		i = 0;				
		j = 0; 				
		items = 0;				
		desired = 1;		
		
		while(line[i]!='\n'){
			if(desired!=-1){
				if(line[i]!=','){
						value[j] = line[i];
						j++;
				}
				else{
					value[j] = '\0';
					if(items == 1){
						if(value[0] != section){
							desired =-1;
						}
						else{
							total++;
						}
					}
					if(items>1){
						number = atoi(value);
						assignments[items-2] = assignments[items-2]+number;
					}
					items++;
					//printf("%d\n",number);
					j = 0;
				}
			}		
			i++;
		}
		if(desired!=-1){
		value[j]='\0';
		number = atoi(value);
		assignments[5] = assignments[5]+number;
		//printf("%d\n",number);
		}
		n = n+i+1;
		lseek(file,n,SEEK_SET);	//setting head pointer for reading next lines

		//line[i] = '\0';
		//printf("%s\n",line);
	}
	close(file);		//CLOSE system call 
	
	if(total ==0){
		printf("No entries is present in the File\n");
		exit(1);
	}
	
	//printing results -	
	printf("For section %c average marks in assignment 1 is :%3.5f\n" ,section,(1.0*assignments[0])/total);
	printf("For section %c average marks in assignment 2 is :%3.5f\n" ,section,(1.0*assignments[1])/total);
	printf("For section %c average marks in assignment 3 is :%3.5f\n" ,section,(1.0*assignments[2])/total);
	printf("For section %c average marks in assignment 4 is :%3.5f\n" ,section,(1.0*assignments[3])/total);
	printf("For section %c average marks in assignment 5 is :%3.5f\n" ,section,(1.0*assignments[4])/total);
	printf("For section %c average marks in assignment 6 is :%3.5f\n" ,section,(1.0*assignments[5])/total);
}
