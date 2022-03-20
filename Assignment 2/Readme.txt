Name - Sagar Suman
Roll no. 2019197
Os Assignment 2.

Answer 1 -
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Approach and logic- 
To solve this problem, we have three files - 2019197_main.c, 2019197_SR_function.c and ST_function.c.

Functioning or logic of main file - 2019197_main.c :-

1. In this file, firstly we use fork() system call to create child process. We store its pid in local variable S1_pid. 
2. In the child process, we are doing signal registration for SIGTERM signal using sigaction. 
3. After registration, we enter the infinite loop for pause system call. It will pause the process, and revoke every time when SIGTERM signal is catched. 
4. In the parent process, we are then creating one more child process SR.
5. In SR, we are using execl system call to exceute SR_function executable file. We have passed the pid of S1 to SR_function by the help of arguments of execl system call.
6. Now we are using the parent process for functioning of ST.
7. In ST, we are using execl system call to exceute ST_function executable file. We have passed the pid of S1 to ST_function by the help of arguments of execl system call.
8. In case of failiur of process creating with fork, i.e. pid<0 , we are printing error message. 
9. In this process, we are also attaching shared memory for retreiving the string from ST_function. 
9. Signal handler of S1 - S1_handler :-
10.1. This handler will be envoked when S1 recieves SIGTERM signal.
10.2. In this, we are cheking the value of received integer from sigqueue.
10.3. ST_function will send -1. So if -1 is recieved, we will print the string from shared memory.
10.4. Else, we are printing the random integer which is receieved from SR_function. 


Functioning or logic of SR_function :-

1. In this file, we are firstly retrieving the PID of S1.
2. We registerd the signal handler for SIGALRM signal. We are using setitimer to generate the SIGALRM signal for every 1 sec.
3. After recieving the signal, we are using pause() to suspend the signal for next signal.
4. Signal will envoke signal handler. In Signal handler, we are using inline assembly for rdrand to generate random number.
5. With the help of sigqueue, random number generated and SIGTERM signal is sended to Process S1 (by pid of S1). 

Functioning or logic of ST_function :- 

1. We are following 1,2,3 steps of SR_function. 
2. In 4th step , instead of rdrand, in inline assembly we are using rdtsc to generate number. We then transformed this number to date and time format and stored into string.
3. Since we can not send string or string pointer to S1 through sigueue. (Reason- as deferencing of pointer will report segmentation fault, because of unaccessible memory address.)
4. We are using shared memory to tackle this problem.
5. We created shared memory and attached to ST_function. Then in shared memory we are copying our string.
6. Through sigqueue, we are sending -1 to S1 and SIGTERM signal. S1 can use -1 to know, that it is sended from ST_function and proceed accordingly.
