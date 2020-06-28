/**CFile****************************************************************
  
   FileName     [gate.h]
  
   Synopsis     [functions for verilog to blif for gates]
  
   Author       [Joshua Lin]
  
   Date         [Started - June 28, 2020]
  
***********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

typedef enum gate_type GATE;

enum gate_type{
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
};

void gate_blif(GATE g, vector<string>& IOname, fstream& out_stream)
{
    
}