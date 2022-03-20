Name - Sagar Suman
Roll no. 2019197
Os Assignment 1.

Queston 1 -
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Part 1 - Using fork() system call to create process.

Working - 
1. In main(), we call the fork() system call to create child process along with parent process.and store its return value in pid variable.
2. For succesful fork() pid shoud greater than or equal to 0, its value less than zero signifies that fork() is failed and we have returned error in this case and return 1.
3. For pid = 0 signifies it is a child process , and pid !=0 signifies it is a parent process with child's process id being pid. 
4. After calling fork(), child and parent processes will be running, they enters into the block of pid>=0.
5. In case of parent process (pid!=0), it will first encounter waitpid() system call and it will wait for child process to get terminate.
6. In case of child process, Avg_sec function is called with parameter 'A'. After returning from the function, child process will exit with exit system call.
7. Then, parent process will resume, and execute Avg_sec function with parameter 'B'. After it has executed the function, our program gets completed.

About Avg_sec function-
1.This function takes character as an argument, which is used to do the required operation for desired section. 
2. It will open the file with open system call and store its return value in file descriptor variable. It its return value is -1, then file does not exist and we return error
3. We check whether file is empty or not by reading first 130 bytes in the file by read system call. Read system call return number of bytes red, if this is equal to or less then 0, then file is empty and we exit with print message.
4. For reading the file, we remove the labels of the column by placing head pointer to 98 bytes with help of lseek system call.
5. Then we are reading line by line with read system (with passing parameter as line width) call until no character is present. In each call, we are traversing the characters.
6. we are maintaining a buffer, and in each traversal we are adding character in this buffer until we found comma or newline character.
7. if we encounter comma, then we will convert the buffer. After first comma we will get section (which we will decide further processing) so we will extract it. 
If section is desired section then after second comma we will convert all buffers into numbers.
8. if we encounter newline, we will place head pointer to the next position to this character. and we again start reading.
9. We have created two variables - total and array of assignments. total will store no. of students in section and array of assignments will store sum of assignments in desired section
which are extracted in step 7.
10. Finally,we are closing the file with close system call and printing the averages of different sections.

System calls-
1. fork() system call - no arguments passed. For expected value and error handling refer to the point 1,2,3 of Working.
2. exit(0) system call - used after completion of child process,argument passed is 0 which indcates success.
3. open("student_record.csv", O_RDONLY) system call used for opening the student_record file. Second paramenter tells the permission as Read onlymode. 
	Error handling - point 2 of About Avg_sec function.
4. Read system call - parameters : (int file_descriptor, void *buf, size_t count) - reads up to count bytes fom file_descriptor into buffer buf. 
5. Lseek system call  - parameters:(int file_descriptor,int offset,int whence) - where we have used SEEK_SET as whence for setting head pointer to read.
6. close(file) system call- parameter : int file_descriptor, used for closing the file.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Part2 - Using Threads.

Working - 
1. We have defined the structure for particular section that contains section,total students and total assignment marks.
2. We have made two sections using above structure- sectionA and sectionB.
3. We then create a thread using pthread_create function and passed void pointer function(Avg_sec) and parameters. Here in parameter we have passd
	void pointer which points to sectionA.
4. We store the return value of pthread_create function in variable c, c is equal to 0 depicts unable to create thread and we exit from it.
5. After doing step 3, we actually have two threads- one that is created and another one is main(). So, main will also work as thread.
6. thread created in step 3 execute the Avg_sec function for section A. In main() we have called Avg_sec for section B.  
7. Main() will wait for other thread to get compeleted by pthread_join system call.
8. In Avg_sec function we have passed pointers as parameter. In the Avg_sec function we have modified the value which these pointers point.
9. After pthread_join, we have sectionA and sectionB which got modified in step 8. With the help of these structures value we finally print average ofassingment across all sections. 
  
About Avg_sec function -
1. This function is almost same as Avg_sec function which was defined in previous part. It has very few changes.
2. In this function we are passing void pointer to structure as parameter.
3.  It is mainly done to store the value in to these memory locations by call by refrence methods.
4. For each structure parameter, we are using its section for desired section. We are modifying its value total students and sum of assignments which was computed in this function.
5. All the rest of things related to reading,etc are same as previous part.

System calls - same as previous part.
