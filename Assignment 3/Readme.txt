Name - Sagar Suman
Roll no. 2019197
Os Assignment 3.

Answer 2 -
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Part 1 -Implementation of mechanism using Unix domain sockets.

Functionality of P1 (server) -
1. To start with, we are generating 50 random strings of length 3. For storing this I am using a 2D character array of dimensions 50 X 3.
2. We remove socket, which could be already present by the same name of socket, we are going to use.
3. Then we use socket(), to create the socket. We are passing SOCK_SEQPACKET as the parameter in this, to transfer packets.
4. We intialize the unix domain socket address structure.
5. Followed by this, we use bind(), to bind the socket to the specific port number.
6. Then we are using listen(), to listen to any request for connect.
7. After it, we encounter accept(), which will block the process until it gets request from P2 (client).
8. Once it gets connection request from p2, program resumes.
9. We take a variable count, and intitialize it to 0. Program at this stage, enters into the while loop, which will stop if counts>=49.
10. In the while loop, We are creating a string, which contains 5 random strings from index count to count+4, followed by their indexes as IDs.
11. Then with the help of write(), we are sending this string to P2.
12. With the help of read(), we are receiving the highest ID sent by P2 as acknowledgement.
13. We are storing the ID we receive in count_rec. If this count_rec is equal to count+4 then that means right acknowlegment is acquired. We increase the count by one. 
14. After the while loop, we are closing the sockets and unlinking the socket we used.

Functionality of P2 (client) -
1. In this, we are using socket(), to create another socket for the purpose of connecting it to P1.
2. We then use connect(), to send the connection request to P1.
3. Once, P1 receives and accepts this request, connection gets established.
4. After this, we are defining a variable max_id as 0 and running the while loop until max_id becomes 49.
5. In the while loop, we are receving the message sent by P1 by the the help of read(), we get this message as string.
6. We have then created the sort of tokenizer, which we will separate the five random random strings and their ids. We are storing it,
7. After that, we are printing the received random string along with their ids.
8. For sending the acknowledgement, we find the maximum id among the ids, and send it to P1 with the help of write().
9. We update the max_id defined in step 4 by the value we received in step 8.
10. At the end of while loop, we are closing the socket. 

Part 2 - Implementation of mechanism using FIFO.

Functioality of P1 -
1. First step is same as of P1 in part 1.
2. We are using mkfifo(), to create the file named q_fifo.
3. We do the same step as we did in step 9 and step 10 in P1 part 1.
4. In this while loop, we are opening the file in write only mode and send the string with the help of write() . We then close the file descriptor.
5. We then open it for read only mode and receive the highest ID sent by P2 with the help of read(). We close the file descriptor.
6. We repeat the step 13 of P1 part1.

Functionality of P2 - 
1. We start this, by doing the step 4 of P2 part 1.
2. In the while loop, corresponding to the step 4 of above functionality of P1, we are opening the file in read only mode and receiving the string with the help of read(). Close the file descriptor.
3. We are repeating the work done as per the step 6 and step 7 of P2 part 1. FInd the highest id.
4. Corresponding to the step 5 of above functionality of P1, we are opening the file in write only mode and sending the highest id with the help of write(). Close the file descriptor.
5. Repeat the step 9 of P2 part 1.


Part 3 - Implementation of mechanism using Message queues

Functioality of P1 -
1. First step is same as of P1 in part 1.
2. We using mq_open() to create a two message queue descriptor. One with write only mode and another with read only mode.
3. We do the same step as we did in step 9 and step 10 in P1 part 1.
4.  In this while loop, we are sending the string to first file descriptor (one with write only mode) using mq_send().
5. Then we use mq_receive() to receive the highest from second file descriptor (one with read only mode).
6. We repeat the step 13 of P1 part1.
7. Finally, close the file descriptors and unliking the message queues.

Functionality of P2 -
1. Similar to step 2 of P1 of this part, we create two message queue descriptor. One which was created with write only mode in P1, now should be opened with read only mode.
2. SImilar for other file descriptor,  One which was created with read only mode in P1, now should be opened with write only mode.
3. Repeat the step of P2 part 1.
4. FIle descriptor which was opened in step1, receives the string with help of mq_receive(). 
5. We are repeating the work done as per the step 6 and step 7 of P2 part 1. Find the highest id.
6. FIle descriptor which was opened in step2, sends the highest id with help of mq_send().
7. Repeat step 9 of P2 part 1.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

