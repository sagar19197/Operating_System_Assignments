# 2019197, Q1-Part1 Makefile

CC = gcc

preprocessing:
	$(CC) -E 2019197_Q1part1.c -o out.i
assembly:
	$(CC) -S out.i -o out.s
object:
	$(CC) -C out.s -o out.o
executable:
	$(CC) out.i -o out 
clean:
	rm -rf out.s out.o out.i out