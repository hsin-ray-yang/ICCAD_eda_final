/**CFile****************************************************************
  
   FileName     [gate.h]
  
   Synopsis     [functions for verilog to blif for gates]
  
   Author       [Joshua Lin, modify by Ray Yang]
  
   Date         [Started - June 28, 2020.]
  
***********************************************************************/
#include <string.h>

typedef enum gate_type{
    DEFAULT_GATE = 0,
    AND,
    OR,
    NAND,
    NOR,
    NOT,
    BUF,
    XOR,
    XNOR,
    DC,
    MUX
}Gate;

typedef enum header_type{
    DEFAULT_HEADER = 0,
    MODULE,
    INPUT,
    OUTPUT,
    WIRE,
    GATE,
    END
}Header;

int del_sp(char* str) {
    char *p = str;
    char *q = str;
    int ret =0;
    while(*q!='\0') {
        if (*q == ',') {
            ++ret;
        }
        if ((*q != '\x09')&&(*q != '\n')&&(*q != ' ')) {
            *p++ = *q;
        }
        q++;
    }
    *p='\0';
    return ret;
}