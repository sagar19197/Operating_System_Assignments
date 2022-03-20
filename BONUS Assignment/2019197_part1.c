// OS Bonus Assignment 
// Name - Sagar Suman
// Roll No. 2019197


// Part 1 :- Dining Philospher problem with two forks to eat


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<semaphore.h>

//philosphers has two jobs, to think and eat
//NOTE - for eating philospher needs following forks
// Philospher 1 : fork 0 (left) and fork 1(right)
// Philospher 2 : fork 1 (left) and fork 2(right)
// Philospher 3 : fork 2 (left) and fork 3(right)
// Philospher 4 : fork 3 (left) and fork 4(right)
// Philospher 5 : fork 4 (left) and fork 0(right)
	
// For deadlock avoidance - 
// Philospher 5 takes his right fork first and then his left fork.


//used functions declarations - 

void* create_philospher(void* name);	//for creating philospher
void think(int philospher);		// Philosphers think
void eat(int philospher);		// Philosphers eat	
void take_leftFork(int fork);
void take_rightFork(int fork);
void put_leftFork(int fork);
void put_rightFork(int fork);

sem_t semaphore[5];			//five semaphores corresponding to to five forks

int binary_semaphores(){
			// using 5 semaphores for 5 forks
	for(int i=0;i<5;i++){
		if(sem_init(&semaphore[i],0,1) == -1){
			perror("Error in creating semaphores");
			return -1;
		}
	}
	return 0;
}



int main(){
					
	if(binary_semaphores() == -1){
		return 1;
	}	
					// creating 5 philosphers
	pthread_t philosphers[5];
	int arr[5];
	
	for(int i=1; i<=5;i++){
		printf("Hi, I am philospher %d\n", i);
	}

	for(int i=1; i<=5; i++){
		//printf("Creating philospers jobs %d\n",i);
		arr[i-1] = i;
		if(pthread_create(&philosphers[i-1], NULL, &create_philospher, (void*) &arr[i-1]) != 0){
			perror("Error in creating philospher");
			return 1;
		}
		
	}
	
							//joining
	for(int i=0; i<5; i++){
		if(pthread_join(philosphers[i], NULL) != 0){
			perror("Error in joining");
			return 1;
		}
	}

	for(int i=0;i<5;i++){		//destroying semaphores
		sem_destroy(&semaphore[i]);
	}

	return 0;
}

void* create_philospher(void* name){	
	int philospher = *((int*) name);
	//printf("Hi, I am philospher %d\n",philospher);
	
	// Philospher functionality- to eat and think , included conditions on eating
	
	//Deadlock avoidance by making - 5th philospher take his right fork followed by left fork. Rest of philospher will take their left and follwed by right fork.

	if(philospher!=5){		// rest of philospher
		for( ; ;){
			think(philospher);		//thinking
			take_leftFork(philospher);	// taking left fork
			take_rightFork(philospher);	// taking right fork
			eat(philospher);		//eating
			put_leftFork(philospher);	// putting left fork
			put_rightFork(philospher);	// putting right fork
		}
	}
	else{				// Philospher 5
		for( ; ;){
			think(philospher);		//thinking
			take_rightFork(philospher);	// taking right fork
			take_leftFork(philospher);	// taking left fork
			eat(philospher);		//eating
			put_rightFork(philospher);	// putting right fork
			put_leftFork(philospher);	// putting left fork
		}
	}
}


void think(int philospher){
	printf("Philospher %d is thinking\n",philospher);
}


void eat(int philospher){
	printf("Philospher %d is eating\n",philospher);
}


void take_leftFork(int fork){
	sem_wait(&semaphore[fork-1]); // semaphore wait
	printf("Philospher %d has taken his left fork %d\n",fork,fork-1);
}


void take_rightFork(int fork){
	
	sem_wait(&semaphore[fork%5]); // semaphore wait
	printf("Philospher %d has taken his right fork %d\n",fork,fork%5);
}


void put_leftFork(int fork){
	
	printf("Philospher %d has done using his left fork %d\n",fork,fork-1);
	sem_post(&semaphore[fork-1]); // semaphore signal
}

void put_rightFork(int fork){
	
	printf("Philospher %d has done using  his right fork %d\n",fork,fork%5);
	sem_post(&semaphore[fork%5]); // semaphore signal
}
