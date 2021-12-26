CC = gcc
FLAGS = -std=c99 -pthread -w -pipe -O2 -Wextra -Werror -Wall -Wno-sign-compare -pedantic -lm

all: run

run: libbtree.so mainStat.o mainDyn.o
	$(CC) $(FLAGS) -o run-static mainStat.o -L. -lbtree -Wl,-rpath,.
	$(CC) $(FLAGS) -o run-dynamic mainDyn.o -ldl

mainStat.o: mainStat.c
	$(CC) -c $(FLAGS) mainStat.c

mainDyn.o: mainDyn.c
	$(CC) -c $(FLAGS) mainDyn.c

btree.o: btree.c
	$(CC) -c -fPIC $(FLAGS) btree.c

libbtree.so: btree.o
	$(CC) $(FLAGS) -shared -o libbtree.so btree.o

clean:
	rm -f *.o run-static run-dynamic *.o
