/**CFile****************************************************************
  
   FileName     [gate.h]
  
   Synopsis     [functions for verilog to blif for gates]
  
   Author       [Joshua Lin]
  
   Date         [Started - June 28, 2020.]
  
***********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <assert.h>

typedef enum gate_type{
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
}GATE;

void gate_blif(GATE g, std::vector<std::string>& IOname, std::fstream& outFile)
{
    // gate g0 (i0, i1, i2, out);

    std::stringstream gate_outM, gate_outL;
    gate_outM << ".names ";
    gate_outL << ".names ";

    switch (g)
    {
    case BUF:
        // BUF b0 (i0, o);
        assert(IOname.size() == 2);
        // MSB
        gate_outM << IOname.at(0) << "M " << IOname.at(1) << "M\n";
        gate_outM << "1 1" << '\n';
        // LSB
        gate_outL << IOname.at(0) << "L " << IOname.at(1) << "L\n";
        gate_outL << "1 1" << '\n';
        break;
    
    case NOT:
        // NOT n0 (i0, o);
        assert(IOname.size() == 2);
        // MSB
        gate_outM << IOname.at(0) << "L " << IOname.at(1) << "M\n";
        gate_outM << "0 1" << '\n';
        // LSB
        gate_outL << IOname.at(0) << "M " << IOname.at(1) << "L\n";
        gate_outL << "0 1" << '\n';
        break;

    default:
        break;
    }

    outFile << gate_outM.str() << gate_outL.str();
}