# Sagar Suman, 2019197
# OS assignmet 3, Ques 2 -makefile

# Just type "make" in terminal.

# Output files for three parts are under the following. 

# For part 1 : Unix Domain socket
#	P1 :- 	./socket_p1
 #	P2 :- 	./socket_p2

# For part 2 : FIFO
#	P1 :- 	./fifo_p1
 #	P2 :- 	./fifo_p2

# For part 3 : Message Queues
#	P1 :- 	./mq_p1
 #	P2 :- 	./mq_p2


# Each of output file in corresponding parts should be executed in separate terminals.


CC = gcc

all: socket_p1 socket_p2 fifo_p1 fifo_p2 mq_p1 mq_p2

socket_p1: 2019197_q2_part1_p1.c
	$(CC) 2019197_q2_part1_p1.c -o socket_p1

socket_p2: 2019197_q2_part1_p2.c
	$(CC) 2019197_q2_part1_p2.c -o socket_p2

fifo_p1: 2019197_q2_part2_p1.c
	$(CC) 2019197_q2_part2_p1.c -o fifo_p1

fifo_p2: 2019197_q2_part2_p2.c
	$(CC) 2019197_q2_part2_p2.c -o fifo_p2

mq_p1: 2019197_q2_part3_p1.c
	$(CC) 2019197_q2_part3_p1.c -o mq_p1 -lrt

mq_p2: 2019197_q2_part3_p2.c
	$(CC) 2019197_q2_part3_p2.c -o mq_p2 -lrt

clean:
	rm -rf socket_p1 socket_p2 q2_fifo fifo_p1 fifo_p2 mq_p1 mq_p2



   