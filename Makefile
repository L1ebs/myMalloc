CC=gcc
CFLAGS=-Wall

all: memgrind

memgrind: memgrind.o mymalloc.o
	gcc -Wall -o memgrind memgrind.o mymalloc.o

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

mymalloc.o: mymalloc.c mymalloc.h
	gcc -Wall -c mymalloc.c

clean:
	rm -f memgrind *.o
