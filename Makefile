CC=g++
CFLAGS=-c
OPTFLAGS=-O3
DBGFLAGS=-g
LIBFLAGS=../abc-master/libabc.a -lm -ldl -lreadline -lpthread

all : bin/xec

bin/xec : main.o
	$(CC) -g -o $@ $< $(LIBFLAGS)

main.o : src/main.c src/gate.h
	gcc -Wall $(DBGFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o bin/*