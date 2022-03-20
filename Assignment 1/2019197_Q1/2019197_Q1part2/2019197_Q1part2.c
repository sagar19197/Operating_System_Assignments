/* Sagar Suman, 2019197 Q1-PART2 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>		

void Avg_sec(void *desired_section);			//declaring function

struct section{								//defining sections structure
	char section;
	int total_student;
	int assignment1,assignment2,assignment3,assignment4,assignment5,assignment6;
};


int main(){
	
	struct section sectionA;		//section A
	struct section sectionB;		//section B
	
	sectionA.section = 'A';
	sectionB.section = 'B';

	pthread_t thread;				//thread variable
	
	void *ptr = &sectionA;		//creating void pointer for A
	int c = pthread_create(&thread,NULL,(void *)&Avg_sec,ptr);		//thread
	if(c){
		perror("Unable to create thread");
		exit(1);
	}
	void *ptr2 = &sectionB;				//treating  main as another thread 
	Avg_sec(ptr2);		
	pthread_join(thread,NULL);		//wait for thread to complete
	
	//using above calulated value to calculate average across section
	
	int total = sectionA.total_student + sectionB.total_student;
	int assignments[6];
	assignments[0] = sectionA.assignment1 + sectionB.assignment1;
	assignments[1] = sectionA.assignment2 + sectionB.assignment2;
	assignments[2] = sectionA.assignment3 + sectionB.assignment3;
	assignments[3] = sectionA.assignment4 + sectionB.assignment4;
	assignments[4] = sectionA.assignment5 + sectionB.assignment5;
	assignments[5] = sectionA.assignment6 + sectionB.assignment6;	
	
	//printing results -	
	printf("For both sections average marks in assignment 1 is :%3.5f\n" ,(1.0*assignments[0])/total);
	printf("For both sections average marks in assignment 2 is :%3.5f\n" ,(1.0*assignments[1])/total);
	printf("For both sections average marks in assignment 3 is :%3.5f\n" ,(1.0*assignments[2])/total);
	printf("For both sections average marks in assignment 4 is :%3.5f\n" ,(1.0*assignments[3])/total);
	printf("For both sections average marks in assignment 5 is :%3.5f\n" ,(1.0*assignments[4])/total);
	printf("For both sections average marks in assignment 6 is :%3.5f\n" ,(1.0*assignments[5])/total);
	
	return 0;
}


void Avg_sec(void *desired_section){				//defining function
	
	struct section *sec = (struct section *) desired_section;	//pointer variable
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
	char section = sec->section;							//desired section
	
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
	
	sec -> total_student = total;		
	sec -> assignment1 = assignments[0];
	sec -> assignment2 = assignments[1];
	sec -> assignment3 = assignments[2];
	sec -> assignment4 = assignments[3];
	sec -> assignment5 = assignments[4];
	sec -> assignment6 = assignments[5];
	
	//printing results -	
	printf("For section %c average marks in assignment 1 is :%3.5f\n" ,section,(1.0*assignments[0])/total);
	printf("For section %c average marks in assignment 2 is :%3.5f\n" ,section,(1.0*assignments[1])/total);
	printf("For section %c average marks in assignment 3 is :%3.5f\n" ,section,(1.0*assignments[2])/total);
	printf("For section %c average marks in assignment 4 is :%3.5f\n" ,section,(1.0*assignments[3])/total);
	printf("For section %c average marks in assignment 5 is :%3.5f\n" ,section,(1.0*assignments[4])/total);
	printf("For section %c average marks in assignment 6 is :%3.5f\n" ,section,(1.0*assignments[5])/total);
}
