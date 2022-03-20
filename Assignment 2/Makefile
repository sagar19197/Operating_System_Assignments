# Sagar Suman, 2019197
# OS assignmet 2, Ques 1 -makefile

# Output will be in  ./ans1
# Just type 'make all' in Terminal

CC = gcc

all: SR_function ST_function ans1

ST_function: 2019197_ST_function.c
	$(CC) 2019197_ST_function.c -o ST_function

SR_function: 2019197_SR_function.c
	$(CC) 2019197_SR_function.c -o SR_function

ans1: 2019197_main.c
	$(CC) 2019197_main.c -o ans1

clean:
	rm -rf SR_function ST_function ans1