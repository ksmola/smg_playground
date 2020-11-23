CC = gcc
CFLAGS = -Wall -g
INCLUDE = include/smg_tester.h 
LIBS = -lpthread
OBJ = smg_tester.o

smg_tester: smg_tester.o
	$(CC) ${LIBS} ${CFLAGS} -o smg_tester smg_tester.c

smg_tester.o: smg_tester.c include/smg_tester.h

.PHONY: all
all: smg_tester

.PHONY: clean
clean: 
	rm -f smg_tester.o smg_tester