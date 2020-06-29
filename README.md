# ICCAD_eda_final

## before start
go to [https://github.com/berkeley-abc/abc](https://github.com/berkeley-abc/abc) and make a **libabc.a** file.

## compile
For `demo.out`:

    gcc -Wall -g -c src/demo.c -o src/demo.o
    g++ -g -o demo.out src/demo.o ../abc-master/libabc.a -lm -ldl -lreadline -lpthread
    
For `xec`:

    make

## execute
For `demo.out`:

    ./demo.out <input_file>

For `xec`:

    ./bin/xec <input.v> <output.blif>