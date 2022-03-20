# 2019197, Q1-Part2 Makefile

CC = gcc

preprocessing:
	$(CC) -pthread -E 2019197_Q1part2.c -o out.i
assembly:
	$(CC) -pthread -S out.i -o out.s
object:
	$(CC) -pthread -C out.s -o out.o
executable:
	$(CC) -pthread out.i -o out 
clean:
	rm -rf out.s out.o out.i out