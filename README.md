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
For `xec`:

    ./bin/xec <golden.v> <revise.v> <output_path> 
    
The program will create a result.blif in current directory and output file in the path we give.
