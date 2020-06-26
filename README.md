# ICCAD_eda_final

## before start
go to [https://github.com/berkeley-abc/abc](https://github.com/berkeley-abc/abc) and make a **libabc.a** file.

## compile
run

    gcc -Wall -g -c src/demo.c -o src/demo.o
    g++ -g -o demo.out src/demo.o ../abc-master/libabc.a -lm -ldl -lreadline -lpthread
    ./demo.out ./i10.aig

ya