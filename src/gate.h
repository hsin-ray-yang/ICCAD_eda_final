/**CFile****************************************************************
  
   FileName     [gate.h]
  
   Synopsis     [functions for verilog to blif for gates]
  
   Author       [Joshua Lin, modify by Ray Yang]
  
   Date         [Started - June 28, 2020.]
  
***********************************************************************/
#include <stdio.h>
#include <string.h>
#include <assert.h>

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

void gate_blif(int GR, Gate g, char** IOname, int n, FILE * outFile)
{
    /* GR = 0 if revised; GR = 1 if golden */
    // gate g0 (i0, i1, i2, out);
    #define writeIOstring(i, ml) fprintf(outFile, "%s%s_%s", IOname[i], ml, GR_str)

    char* GR_str = GR ? "gf" : "rf";

    switch (g)
    {
    case BUF:
        // buf buf0 (o, i);
        assert(n == 2);
        // MSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "M");
        fprintf(outFile, " ");
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        fprintf(outFile, "1 1\n");
        // LSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "L");
        fprintf(outFile, " ");
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        fprintf(outFile, "1 1\n");
        break;
    
    case NOT:
        // not not0 (o, i);
        assert(n == 2);
        // MSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "L");
        fprintf(outFile, " ");
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        fprintf(outFile, "0 1\n");
        // LSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "M");
        fprintf(outFile, " ");
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        fprintf(outFile, "0 1\n");
        break;

    case AND:
        // and and0 (o, i0, i1, i2)
        // MSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "1");
        }
        fprintf(outFile, " 1\n");
        // LSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "1");
        }
        fprintf(outFile, " 1\n");
        break;

    case OR:
        // or or0 (o, i0, i1, i2)
        // MSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "0");
        }
        fprintf(outFile, " 0\n");
        // LSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "0");
        }
        fprintf(outFile, " 0\n");
        break;

    case NAND:
        // nand nand0 (o, i0, i1, i2)
        // MSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "1");
        }
        fprintf(outFile, " 0\n");
        // LSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "1");
        }
        fprintf(outFile, " 0\n");
        break;

    case NOR:
        // nor nor0 (o, i0, i1, i2)
        // MSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "0");
        }
        fprintf(outFile, " 1\n");
        // LSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        for(int i = 1; i < n; i++){
            fprintf(outFile, "0");
        }
        fprintf(outFile, " 1\n");
        break;

    case XOR:
        // xor xor0 (o, i0, i1, i2)
        // TODO
        break;

    case XNOR:
        // xnor xnor0 (o, i0, i1, i2)
        // TODO
        break;
    
    case DC:
        // _DC dc0 (o, c, d)
        assert(n == 3);
        // MSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "M");
        fprintf(outFile, " ");
        writeIOstring(2, "L");
        fprintf(outFile, " ");
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        fprintf(outFile, "10 1\n");
        // LSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "L");
        fprintf(outFile, " ");
        writeIOstring(2, "L");
        fprintf(outFile, " ");
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        fprintf(outFile, "1- 1\n-1 1\n");
        break;
    
    case MUX:
        // _HMUX mux0 (o, i0, i1, s)
        // TODO
        break;

    default:
        printf("Error: Not acceptable gate_type!!\n");
        break;
    }
}

//*************************************************************
// int del_sp(char* str)
//*************************************************************
// delete all space, \n, tab in the string,
// return numbers of sub-string saparated by ',' in the string.
///////////////////////////////////////////////////////////////
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

//***************************************************************************
// void print_detail(FILE * gf_blif, char * ptr, Header header,Gate gate)
//***************************************************************************
// Input :
//      gf_blif : destination to print on.
//      ptr     : origin string of verilog file.
//      header  : type of header.
//      gate    : type of gate.(if header is not GATE, then gate is useless)
//      
// print formal .blif style string on FILE* gf_blif
/////////////////////////////////////////////////////////////////////////////
void print_detail(FILE * gf_blif, char * ptr, Header header,Gate gate) {
    // clear space and count number of parameters
    size_t para_num;
    ptr = strtok(ptr, ";");
    para_num =del_sp(ptr);

    char * header_name[7] = {"no_use_d", "no_use_m",".inputs", ".outputs", "no_use_w", ".names", ".end"};
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
        gate_blif(1, gate, entry, para_num, gf_blif);
    }
    else if ( header==INPUT || header==OUTPUT ){
        char *entry[para_num];
        char *p = strtok (ptr, ",");
        int i = 0;
        while (p != NULL) {
            entry[i++] = p;
            p = strtok (NULL, ",");
        }

        fprintf(gf_blif, "%s ", header_name[header]);
        for (int i=0;i<para_num-1;++i) {
            fprintf(gf_blif, "%s ", entry[i]);
        }
        fprintf(gf_blif, "%s\n", entry[para_num-1]);
    }
    else if ( header==END ){
        fprintf(gf_blif, "%s\n", header_name[header]);
    }
    return;
}
