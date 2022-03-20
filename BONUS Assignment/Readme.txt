Name - Sagar Suman
Roll no. 2019197
Os BONUS Assignment

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Part 1 - Dining Philospher problem with 2 forks.

1. In this problem, we have 5 philospher each having one plate and one forks on their left .
2. For creating the philosphers,we have used threading. We have created the array of 5 elements having type phread_t , which represents 5 threads.
3. These threads will execute the create_philospher() function for creating 5 philosphers.
4. Philosphers have two jobs, thinking and eating. For eating, they have to use two forks.
5. Each philosphers needs following forks - 
	Philospher 1 : fork 0 (left) and fork 1(right)
	Philospher 2 : fork 1 (left) and fork 2(right)
	Philospher 3 : fork 2 (left) and fork 3(right)
	Philospher 4 : fork 3 (left) and fork 4(right)
	Philospher 5 : fork 4 (left) and fork 0(right)
6. So, flow of philospher work will be as follows- 
	6.1. Philospher will think.
	6.2. After thinking, they pickup their left fork
	6.3. Then they pickup their right fork.
	6.4. Once, they have both the forks, they start eating.
	6.5. After they are done with eating, they put their left fork on table.
	6.6. Then they put their right fork on table.
7. Without process sychronization, program may result in race conditions. That is, it could be possible that two philospher will end up holding the same forks.
8. To avoid race conditions, we are using semaphores. We have created array of 5 binary semaphores (corresponding to 5 forks).
9. These semaphores will help in proper accessing the forks and avoiding the race conditions.
10.  We put sem_wait() in steps 6.2 and 6.3 , and used sem_post() in steps 6.5 and 6.6, for respective forks.

11. But, now the problem of deadlock can occur. If all philospher takes their left forks , then at step 6.3 they might get blocked (there are no forks left, all are occupied).

12. Deadlock Resolution - 
	12.1. To avoid deadlock, I have interchanged the steps 6.5 and 6.6 for 5th Philospher.
	12.2. Rest of philosphers do their jobs as usual.
	12.3. Impact - This will stop 5th philospher from taking his left fork, and instead he will first try to take his right fork. 
	12.4. Assuming all philosphers have acquired their left forks,  5th philospher will get blocked, as his right fork is same as left fork of 1st philospher (see step 5).
	12.5. So, this will eliminate 5th philospher for opting for his left fork, and his left fork can be used by 4th philospher to complete the eating. 
	12.6. After 4th philospher completes eating, he will free forks which can be used by 3rd philospher to complete eating. 
	12.7. Then 3rd philospher completes eating, he will free his forks which can be used by 2nd philospher. 
	12.8. Similarly, 2nd philospher completes eating and free his forks which is used 1st philospher. 
	12.9. Now, Once, first philospher completes eating, he will free his left fork. At this point, 5th philospher can use this fork to complete eating.
	12.10. And there will be no deadlock.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Part 2 - Dining Philospher problem with 1 forks and any one of four bowls.

1. In this problem, philosphers need to access one fork and one of the 4 bowls to eat.
2. We repeat the steps 2 and 3 of part 1.
3. Each philosphers need the following  for eating - 
	3.1. Philospher 1 : fork 0 (left) and any one of 4 bowls
	3.2. Philospher 2 : fork 1 (left) and any one of 4 bowls
	3.3. Philospher 3 : fork 2 (left) and any one of 4 bowls
	3.3. Philospher 4 : fork 3 (left) and any one of 4 bowls
	3.4. Philospher 5 : fork 4 (left) and any one of 4 bowls
4. So, flow of philospher work will be as follows -
	4.1. Philospher will think.
	4.2. After thinking, they pickup their left fork
	4.3. Then they pickup one of the four bowls.
	4.4. Once, they have one fork and one bowl, they start eating.
	4.5. After they are done with eating, they put their left fork on table.
	4.6. Then they put the bowl on table.
5. For process synchronization, we repeat  steps 7, 8, and 9 of part 1. Apart from this, we have also used one counting semaphore with value 4.
6. Counting semaphore will allows philosphers to take one of the four bowls. Once, all the four bowls get occupied, last philospher asking for bowls will get blocked.

7. Possibility of Deadlock - 	There will be NO DEADLOCK in this problem.

8. Reason - 
	8.1. Each philospher requires one fork and one of 4 bowls.
	8.2. Since, there are 5 philosphers and each have one fork with them, this will not contribute towards any deadlock. 
	8.3. Each philospher will take up their fork, use it for eating and put it down.
	8.4. Now, there are only 4 bowls on the table, and we have 5 philosphers.
	8.5. But this will also not create any deadlocks, because these 4 bowls will be used by 4 philosphers to complete the eating.
	8.6. Meanwhile, if remaining one philospher wants to access the bowls, he will get blocked, as there are no bowl for him to eat.
	8.7. Once, any one of the philospher completes eating and free one bowl, it can be used by remaining philospher to eat.
	8.8. Hence, this problem does not create any deadlock.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Part 3 - Dining Philospher problem with two forks and any one of four bowls.

1. In this problem, philosphers need both forks and one of the 4 bowls to eat.
2. We repeat the steps 2 and 3 of part 1.
3. Each philosphers need the following  for eating -
	3.1. Philospher 1 : fork 0 (left) , fork 1(right) and any one of 4 bowls
	3.2. Philospher 2 : fork 1 (left) , fork 2(right) and any one of 4 bowls
	3.3. Philospher 3 : fork 2 (left) , fork 3(right) and any one of 4 bowls
	3.4. Philospher 4 : fork 3 (left) , fork 4(right) and any one of 4 bowls
	3.5. Philospher 5 : fork 4 (left) , fork 0(right) and any one of 4 bowls
4. So, flow of philospher work will be as follows -
	4.1. Philospher will think.
	4.2. After thinking, they pickup both forks.
	4.3. Then they pickup one of the four bowls.
	4.4. Once, they have both forks and one bowl, they start eating.
	4.5. After they are done with eating, they put both the forks on table.
	4.6. Then they put the bowl on table.
5. For process synchronization, we repeat step 5 and 6 of part 2.

6. Possibility of Deadlock - Yes, Deadlock condition is possible.
	6.1. Following the step 4 above, if all philospher are going to take both the forks first, it will become similar problem as part 1.
	6.2. That is, It could be possible that all philospher have one fork, and at time of taking right fork, they all get blocked. 
	6.3. This leads to deadlock.

7. Deadlock Resolution - 
	7.1. One easy fix to avoid deadlock situation is to interchange the steps 4.2 and 4.3.
	7.2. That is, philosphers will first pickup one of the 4 bowls, then they go for picking up the forks.
	7.3. As there are only four bowls, so only four philosphers are able to proceed towards picking up of forks.
	7.4. If one remaining philospher tries to access the bowl, he will get blocked, as there are no bowl for him to eat.
	7.5. Now, four philosphers will have five forks (4 forks which are present on their left and one fork which is present on the left of blocked philospher).
	7.6. This will never create the deadlock situation. 
	7.7. As after each philospher has taken 1 fork, there is also 1 fork left, which can be used by any one of the four philospher to complete eating.
	7.8. Another important thing for avoiding deadlock is to put both the forks first, before putting the bowl on the table.
	7.9. Once, any one philospher completes eating and has put their bowl, it can be used by blocked philospher to proceed towards eating.   
	7.10. Hence, through this approach we are able to fix deadlock situation.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

