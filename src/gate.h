/**CFile****************************************************************
  
   FileName     [gate.h]
  
   Synopsis     [functions for verilog to blif for gates]
  
   Author       [Joshua Lin, modify by Ray Yang]
  
   Date         [Started - June 28, 2020.]
  
***********************************************************************/
#include <string.h>
#include <stdio.h>

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
    return ret+1;
}

void print_detail(FILE * gf_blif, char * ptr, Header header,Gate gate) {
    // clear space and count # parameters
    size_t para_num;
    ptr = strtok(ptr, ";");
    para_num =del_sp(ptr);

    char * header_name[7] = {"no_use_d", "no_use_m",".inputs", ".outputs", "no_use_w", "no_use_g", ".end"};
    char * gate_type_name[11] = {"DEFAULT_GATE", "AND", "OR", "NAND", "NOR", "NOT", "BUF", "XOR", "XNOR", "DC", "MUX"};

    if ( header==GATE ) {
        ptr = strtok(ptr, ")");
        char *name = strtok (ptr, "(");
        char *entry[para_num];
        char *p = strtok (NULL, ",");
        int i = 0;
        while (p != NULL)
        {
            entry[i++] = p;
            p = strtok (NULL, ",");
        }
        fprintf(gf_blif, ".names (%s ==> %s) ",gate_type_name[gate],name);
        for (int i=0;i<para_num-1;++i){
            fprintf(gf_blif, "%s ", entry[i]);
        }
        fprintf(gf_blif, "%s\n", entry[para_num-1]);
    }
    else if ( header==INPUT || header==OUTPUT ){
        char *entry[para_num];
        char *p = strtok (ptr, ",");
        int i = 0;
        while (p != NULL)
        {
            entry[i++] = p;
            p = strtok (NULL, ",");
        }

        fprintf(gf_blif, "%s ", header_name[header]);
        for (int i=0;i<para_num-1;++i){
            fprintf(gf_blif, "%s ", entry[i]);
        }
        fprintf(gf_blif, "%s\n", entry[para_num-1]);
    }
    else if ( header==END ){
        fprintf(gf_blif, "%s\n", header_name[header]);
    }
    return;
}