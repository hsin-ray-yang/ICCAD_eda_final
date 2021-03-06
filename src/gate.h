/**CFile****************************************************************
  
   FileName     [gate.h]
  
   Synopsis     [functions for verilog to blif for gates]
  
   Author       [Joshua Lin, modify by Ray Yang]
  
   Date         [Started - June 28, 2020.]
  
***********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void writeXORstr(int n, int ones, int onoff, char* head, FILE * outFile)
{
    // onoff = 1, onset; onoff = 0, offset.
    // printf("Calling F(%d, %d)\n", n, ones);
    if(ones == 0){
        fprintf(outFile, "%s",head);
        for(int i = 0; i < n; i++){ fprintf(outFile, "-0"); }
        fprintf(outFile, " %d\n", onoff);
    }
    else{
        char new_head[2*n];
        for(int i = 0; i <= n-ones; i++){
            strcpy(new_head, head);
            for(int j = 0; j < i; j++){ strcat(new_head, "-0"); }
            strcat(new_head, "1-");
            writeXORstr(n-i-1, ones-1, onoff, new_head, outFile);
        }
    }
}

void const_blif(FILE * outFile)
{
    fprintf(outFile, ".names 1'b1M_gf\n1\n");
    fprintf(outFile, ".names 1'b1L_gf\n1\n");
    fprintf(outFile, ".names 1'b1M_rf\n1\n");
    fprintf(outFile, ".names 1'b1L_rf\n1\n");
    fprintf(outFile, ".names 1'b0M_gf\n");
    fprintf(outFile, ".names 1'b0L_gf\n");
    fprintf(outFile, ".names 1'b0M_rf\n");
    fprintf(outFile, ".names 1'b0L_rf\n");
}

void gate_blif(int GR, Gate g, char** IOname, int n, FILE * outFile)
{
    /* GR = 0 if revised; GR = 1 if golden */
    // gate g0 (i0, i1, i2, out);
    #define writeIOstring(i, ml) fprintf(outFile, "%s%s_%s", IOname[i], ml, GR_str)

    char* GR_str = GR ? "gf" : "rf";
    char XORhead[] = "";

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
        // MSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        for(int num_ones = 1; num_ones < n; num_ones += 2){ writeXORstr(n-1, num_ones, 1, XORhead, outFile); }
        // LSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        for(int num_ones = 0; num_ones < n; num_ones += 2){ writeXORstr(n-1, num_ones, 0, XORhead, outFile); }
        break;

    case XNOR:
        // xnor xnor0 (o, i0, i1, i2)
        // MSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        for(int num_ones = 0; num_ones < n; num_ones += 2){ writeXORstr(n-1, num_ones, 1, XORhead, outFile); }
        // LSB
        fprintf(outFile, ".names ");
        for(int i = 1; i < n; i++){
            writeIOstring(i, "M");
            fprintf(outFile, " ");
            writeIOstring(i, "L");
            fprintf(outFile, " ");
        }
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        for(int num_ones = 1; num_ones < n; num_ones += 2){ writeXORstr(n-1, num_ones, 0, XORhead, outFile); }
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
        fprintf(outFile, "00 0\n");
        break;
    
    case MUX:
        // _HMUX mux0 (o, i0, i1, s)
        assert(n == 4);
        // MSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "M");
        fprintf(outFile, " ");
        writeIOstring(2, "M");
        fprintf(outFile, " ");
        writeIOstring(3, "M");
        fprintf(outFile, " ");
        writeIOstring(3, "L");
        fprintf(outFile, " ");
        writeIOstring(0, "M");
        fprintf(outFile, "\n");
        fprintf(outFile, "1--0 1\n-11- 1\n11-- 1\n");
        // LSB
        fprintf(outFile, ".names ");
        writeIOstring(1, "L");
        fprintf(outFile, " ");
        writeIOstring(2, "L");
        fprintf(outFile, " ");
        writeIOstring(3, "M");
        fprintf(outFile, " ");
        writeIOstring(3, "L");
        fprintf(outFile, " ");
        writeIOstring(0, "L");
        fprintf(outFile, "\n");
        fprintf(outFile, "1-0- 1\n-1-1 1\n");
        break;

    default:
        printf("Error: Not acceptable gate_type!!\n");
        break;
    }
}

void miter_blif(char** outNames, int n, FILE * outFile)
{
    // miters
    for(int i = 0; i < n; i++){
        fprintf(outFile, ".names %1$sM_gf %1$sL_gf %1$sM_rf %1$sL_rf %1$s\n", outNames[i]);
        fprintf(outFile, "1-0- 1\n-0-1 1\n");
    }
    // big or
    fprintf(outFile, ".names ");
    for(int i = 0; i < n; i++){ fprintf(outFile, "%s ", outNames[i]); }
    fprintf(outFile, "IU\n");
    for(int i = 0; i < n; i++){ fprintf(outFile, "0"); }
    fprintf(outFile, " 0\n");
}

void input_blif(char** inNames, int n, FILE * outFile)
{
    for(int i = 0; i < n; i++){
        fprintf(outFile, ".names %1$s %1$sM_gf\n1 1\n", inNames[i]);
        fprintf(outFile, ".names %1$s %1$sL_gf\n1 1\n", inNames[i]);
        fprintf(outFile, ".names %1$s %1$sM_rf\n1 1\n", inNames[i]);
        fprintf(outFile, ".names %1$s %1$sL_rf\n1 1\n", inNames[i]);
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
        if ((*q != '\x09')&&(*q != '\n')&&(*q != ' ')&&(*q != '\r')) {
            *p++ = *q;
        }
        q++;
    }
    *p='\0';
    return ret+1;
}

//************************************************************************************************
// int print_detail(int GR, FILE * gr_blif, char * ptr, Header header,Gate gate,char *** outputs)
//************************************************************************************************
// Input :
//      GR      : golden(1) or revise(0), revise(0) doesn't print INPUT/OUTPUT
//      gr_blif : destination to print on.
//      ptr     : origin string of verilog file.
//      header  : type of header.
//      gate    : type of gate.(if header is not GATE, then gate is useless)
//      outputs : pointer of 2d char array.(if header is not OUTPUT, then gate is useless)
//
// Return :
//      para_num : number of parameter of an entry.
//      
// print formal .blif style string on FILE* gr_blif
//////////////////////////////////////////////////////////////////////////////////////////////////
int print_detail(int GR, FILE * gr_blif, char * ptr, Header header,Gate gate,char *** outputs) {
    // clear space and count number of parameters
    size_t para_num = 0;
    ptr = strtok(ptr, ";");
    para_num =del_sp(ptr);

    // char * header_name[7] = {"no_use_d", "no_use_m",".inputs", ".outputs", "no_use_w", ".names", ".end"};
    // char * gate_type_name[11] = {"DEFAULT_GATE", "AND", "OR", "NAND", "NOR", "NOT", "BUF", "XOR", "XNOR", "DC", "MUX"};

    if ( header==GATE ) {
        ptr = strtok(ptr, ")");
        // char *name = strtok (ptr, "(");
        strtok (ptr, "(");
        char *entry[para_num];
        char *p = strtok (NULL, ",");
        int i = 0;
        while (p != NULL)
        {
            entry[i++] = p;
            p = strtok (NULL, ",");
        }
        gate_blif(GR, gate, entry, para_num, gr_blif);
    }
    else if ( ( header==OUTPUT || header==INPUT ) ) {
        char **entry = (char **)malloc(para_num * sizeof(char *));
        char *p = strtok (ptr, ",");
        int i = 0;
        while (p != NULL) {
            (entry)[i] = (char *)malloc((strlen(p)+1) * sizeof(char));
            strcpy((entry)[i] , p);
            p = strtok (NULL, ",");
            ++i;
        }
        if ( GR==1 ) {
            if ( header==INPUT ) {
                fprintf(gr_blif, ".inputs ");
                for (int i=0;i<para_num-1;++i) {
                    fprintf(gr_blif, "%s ", (entry)[i]);
                }
                fprintf(gr_blif, "%s\n", (entry)[para_num-1]);
            }
            else {
                fprintf(gr_blif, ".outputs IU\n");
            }
        }
        *outputs = entry;
    }
    else if ( header==END && GR==0 ){
        // fprintf(gr_blif, "%s\n", header_name[header]);
    }
    return para_num;
}

void write_blif(int GR, FILE * gr_blif, FILE * gr_v, char *** inputs , size_t * input_size, char *** outputs , size_t * output_size) {
    // read gr file
    char * line = NULL;
    char * ptr = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getdelim(&line, &len,';', gr_v)) != -1) {
        ptr = line;
        Header header = DEFAULT_HEADER;
        Gate gate = DEFAULT_GATE;
        while (1) {
            if (strncmp(ptr, "\x09", 1) == 0 ) {    // delete "tab"
                // printf("%p\n", ptr);
                ptr += 1;
                continue;
            }
            if (strncmp(ptr, " ", 1) == 0 ) {       // delete " "
                // printf("%p\n", ptr);
                ptr += 1;
                continue;
            }
            if (strncmp(ptr, "\r", 1) == 0 ) {      // delete "\r"
                // printf("%p\n", ptr);
                ptr += 1;
                continue;
            }
            if (strncmp(ptr, "\n", 1) == 0 ) {      // delete "\n"
                // printf("%p\n", ptr);
                ptr += 1;
                continue;
            }
            if (strncmp(ptr, "//", 2) == 0) {   // delete "//"
                strtok_r(ptr, "\n",&ptr);
                continue;
            } 
            if (strncmp(ptr, "/*", 2) == 0) {   // delete "/* */"
                strtok_r(ptr, "*/",&ptr);
                continue;
            }
            break;
        }
        if (strncmp(ptr, "module", 6) ==0) {
            // header = MODULE;
            // ptr += 11;
            // ptr = strtok(ptr, ")");
            continue;
        }
        else if (strncmp(ptr, "input", 5) ==0) {
            header = INPUT;
            ptr += 6;
        }
        else if (strncmp(ptr, "output", 6) ==0) {
            header = OUTPUT;
            ptr += 7;
        }
        else if (strncmp(ptr, "wire", 4) ==0) {
            header = WIRE;
            ptr += 5;
        }
        else if (strncmp(ptr, "endmodule", 4) ==0) {
            header = END;
        }
        else {      // gate
            header = GATE;
            if (strncmp(ptr, "and", 3) ==0) {
                gate = AND;
                ptr += 4;
            }
            else if (strncmp(ptr, "or", 2) ==0) {
                gate = OR;
                ptr += 3;
            }
            else if (strncmp(ptr, "nand", 4) ==0) {
                gate = NAND;
                ptr += 5;
            }
            else if (strncmp(ptr, "nor", 3) ==0) {
                gate = NOR;
                ptr += 4;
            }
            else if (strncmp(ptr, "not", 3) ==0) {
                gate = NOT;
                ptr += 4;
            }
            else if (strncmp(ptr, "buf", 3) ==0) {
                gate = BUF;
                ptr += 4;
            }
            else if (strncmp(ptr, "xor", 3) ==0) {
                gate = XOR;
                ptr += 4;
            }
            else if (strncmp(ptr, "xnor", 4) ==0) {
                gate = XNOR;
                ptr += 5;
            }
            else if (strncmp(ptr, "_DC", 3) ==0) {
                gate = DC;
                ptr += 4;
            }
            else if (strncmp(ptr, "_HMUX", 5) ==0) {
                gate = MUX;
                ptr += 6;
            }
            else {
                printf("ERRRRRRROR : read an unknown gate, \"%s\"",ptr);
            }
            
        }

        if (header == OUTPUT) {
            *output_size = print_detail(GR,gr_blif,ptr,header,gate,outputs);
        }
        else if (header == INPUT) {
            *input_size = print_detail(GR,gr_blif,ptr,header,gate,inputs);
        }
        else {
            print_detail(GR,gr_blif,ptr,header,gate,NULL);
        }  
        
    }

    // for(int i=0;i< output_size;++i){
    //     printf("%s ",(outputs)[i]);
    // }
    // printf("\n");
    return;

}
