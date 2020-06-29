CC=g++
CFLAGS=-std=c++11 -c
OPTFLAGS=-std=c++11 -O3
DBGFLAGS=-g
LIBFLAGS=../abc-master/libabc.a -lm -ldl -lreadline -lpthread

all : bin/xec

bin/xec : main.o
	$(CC) $(DBGFLAGS) $(OPTFLAGS) -o $@ $< $(LIBFLAGS)

main.o : src/main.cpp src/gate.h
	$(CC) -Wall $(DBGFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o bin/*