CC=gcc
CFLAGS=-I.

smg_tester:
	$(CC) -o smg_tester smg_tester.c

clean: 
	rm -f smg_tester