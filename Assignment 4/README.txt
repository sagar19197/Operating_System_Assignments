Name - Sagar Suman
Roll No. 2019197
OS Assignment 4
-----------------------------------------------------------------------------------------------------------------------------------

Kernel Producer - Consumer problem

Logic - 
In this assignment we have to create kernel driven producer and consumer.
I have completed this assignment by doing following tasks.

Task 1  - Editing the kernel/sys.c file
	1. We use this file to implement our reader() and writer() system calls.
	2. In this file, we have globally declared long pointer which will point to the shared buffer, in - out counters and semaphores.
	3. Shared buffer is of size 80 bytes (representing a queue of 10 blocks, in which each block is of 8 bytes), which is being allocated memory with kmalloc.
	4. in and out counters resides in writer() and reader() system call. They are used for enqueuing or dequeuing the blocks by index. They are incremented in circular fashion.
	5. We have added three semaphores in this file. 
		5.1. First is remaining_space semaphore, it will represent remaining spaces in the the buffer.
		5.2. Second is filled_space semaphore, it will represent filled spaces in the buffer.
		5.3. Third is mutex, which is a binary semaphore for locking.
	6. We have defined a function - my_initialization() which will initialize the values of step 2.
	7. Now, lets come to implementations of reader() and writer() system call. 
	8. We have use macro SYSCALL_DEFINE1 for their implementation. Both the system calls have one parameter of long pointer.
	9. Writer() system call - 
		9.1. In this we are we are calling down() on remaining_space semaphore. Meaning, that if there are no remaining_spaces, process will go in wait-queue of semaphore.
		9.2. Similarly we are calling down() on mutex. After this process will be allowed to get into critical section.
		9.3. In critical section, we are using copy_from_user to copy the content pointed by the parameter in the shared buffer.
		9.4. We are also incrementing the in_counter in circular fashion ( modulo 10 ).
		9.5. At the exit section, we are calling up on mutex and filled_space to represent that one space has been filled.
	10. Reader() system call -
		10.1. The implementation of this system call is similar to writer system call.
		10.2. In the entry section, we are calling down on filled_space and mutex semaphores. Meaning that if there are no filled_space, process will go in wait_queue of semaphore.
		10.3. In the critical section, we are using copy_to_user to copy the content pointed by the out_counter to the parameter passed.
		10.4. FInally in the exit section, we are calling up on mutex and remaining_space to represent that one space is also remaining.


Task 2 - Editing the system call table located at - arch/x86/entry/syscalls/syscall_64.tbl
	1. Table had 447 entries in first group.
	2. We added 448-th entry of our reader() system.
	3. Next to it, at we addedd 449-th entry ofour writer() system call.

Task 3 - After editing these changes, we compiled our kernel.

Task 4 - Wrting P program to run the writer system call- 
	1. In this c file we firstly generated the 8 bytes random number with help of /dev/urandom.
	2. We completed step 1, by opening the /dev/urandom , then reading long values which is 8 bytes. And finally we close the file.
	3. We passed this 8 byte random numbers to writer() system call to add it to kernel buffer. We are using syscall() function for it to pass it to 449.
	4. After the values has been passed, we printing the numbers.

Task 5 - Writing C program to run reader system call -
	1. In this c file, we are using reader system call to receive the long values from the kernel buffer.
	2. We have used syscall function for step 1, and used parameter as 448.
