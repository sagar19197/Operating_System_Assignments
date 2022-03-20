// OS Bonus Assignment 
// Name - Sagar Suman
// Roll No. 2019197


// Part 3 :- Dining Philospher problem with two forks and any one of four bowls to eat

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<semaphore.h>

//philosphers has two jobs, to think and eat
//NOTE - for eating philospher needs following - 
// Philospher 1 : fork 0 (left) , fork 1(right) and any one of 4 bowls
// Philospher 2 : fork 1 (left) , fork 2(right) and any one of 4 bowls
// Philospher 3 : fork 2 (left) , fork 3(right) and any one of 4 bowls
// Philospher 4 : fork 3 (left) , fork 4(right) and any one of 4 bowls
// Philospher 5 : fork 4 (left) , fork 0(right) and any one of 4 bowls
	
// For deadlock avoidance - 
// Asking for two forks first makes deadlock.
// So, all philosphers must get one bowl before asking for the two forks , and put two forks before before putting their bowls.
// Above will ensure, that only four philosphers eat together (because of four bowls), and these four philosphers will then have access to five forks, which will never create deadlock.


//used functions declarations - 

void* create_philospher(void* name);	//for creating philospher
void think(int philospher);		// Philosphers think
void eat(int philospher);		// Philosphers eat	
void take_leftFork(int fork);
void take_rightFork(int fork);
void put_leftFork(int fork);
void put_rightFork(int fork);
void take_bowl(int philospher);
void put_bowl(int philospher);


sem_t semaphore[5];			//five semaphores corresponding to to five forks

sem_t bowls;		// counting semaphore for bowls

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
	
	if(sem_init(&bowls,0,4) == -1){		
					//creating counting semaphore with its value initialized to 4, i.e there are 4 bowls on table
		perror("Error in creating bowls");
		return 1;
	}				
	
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

	sem_destroy(&bowls);		//destroying bowl semaphore
	
	return 0;
}

void* create_philospher(void* name){	
	int philospher = *((int*) name);
	//printf("Hi, I am philospher %d\n",philospher);
	
	// Philospher functionality- to eat and think , included conditions on eating
	
	//Deadlock avoidance by making - all philospher to take one bowl out of four bowls first before asking for two forks.

	for( ; ;){
		think(philospher);		//thinking
		take_bowl(philospher);		//taking one bowl
		take_leftFork(philospher);	// taking left fork
		take_rightFork(philospher);	// taking right fork
		eat(philospher);		//eating
		put_leftFork(philospher);	// putting left fork
		put_rightFork(philospher);	// putting right fork
		put_bowl(philospher);		//putting bowl
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

void take_bowl(int philospher){
	sem_wait(&bowls);		//bowl counting semaphore wait
	printf("Philospher %d has taken one bowl\n",philospher);
}

void put_bowl(int philospher){
	sem_post(&bowls);		//bowl signal
	printf("Philospher %d has done with his bowl\n",philospher);
}

