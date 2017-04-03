CC=gcc
CFLAGS=-Wall -g

PROG=egnoramoose

all:
	$(CC) $(CFLAGS) $(PROG).c main.c -o $(PROG)

clean:
	rm -f $(PROG).o main.o $(PROG)
