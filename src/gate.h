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



void gate_blif(bool GR, GATE g, std::vector<std::string>& IOname, std::fstream& outFile)
{
    /* GR = 0 if revised; GR = 1 if golden */
    // gate g0 (i0, i1, i2, out);
    #define getIOstring(i, ml) IOname.at(i) << ml << '_' << GR_str

    std::string GR_str = GR ? "gf" : "rf";
    std::stringstream gate_outM, gate_outL;
    gate_outM << ".names ";
    gate_outL << ".names ";

    int n = IOname.size();

    switch (g)
    {
    case BUF:
        // BUF buf0 (o, i);
        assert(n == 2);
        // MSB
        gate_outM << getIOstring(1, 'M') << ' ' << getIOstring(0, 'M') << "\n";
        gate_outM << "1 1" << '\n';
        // LSB
        gate_outL << getIOstring(1, 'L') << ' ' << getIOstring(0, 'L') << "\n";
        gate_outL << "1 1" << '\n';
        break;
    
    case NOT:
        // NOT not0 (o, i);
        assert(n == 2);
        // MSB
        gate_outM << getIOstring(1, 'L') << ' ' << getIOstring(0, 'M') << "\n";
        gate_outM << "0 1" << '\n';
        // LSB
        gate_outL << getIOstring(1, 'M') << ' ' << getIOstring(0, 'L') << "\n";
        gate_outL << "0 1" << '\n';
        break;

    case AND:
        // AND and0 (o, i0, i1, i2)
        for(int i = 1; i < n; i++){
            gate_outM << getIOstring(i, 'M') << ' ';
            gate_outL << getIOstring(i, 'L') << ' ';
        }
        gate_outM << getIOstring(0, 'M') << "\n";
        gate_outL << getIOstring(0, 'L') << "\n";
        for(int i = 1; i < n; i++){
            gate_outM << '1';
            gate_outL << '1';
        }
        gate_outM << " 1" << '\n';
        gate_outL << " 1" << '\n';
        break;

    case OR:
        // OR or0 (o, i0, i1, i2)
        for(int i = 1; i < n; i++){
            gate_outM << getIOstring(i, 'M') << ' ';
            gate_outL << getIOstring(i, 'L') << ' ';
        }
        gate_outM << getIOstring(0, 'M') << "\n";
        gate_outL << getIOstring(0, 'L') << "\n";
        for(int i = 1; i < n; i++){
            gate_outM << '0';
            gate_outL << '0';
        }
        gate_outM << " 0" << '\n';
        gate_outL << " 0" << '\n';
        break;

    case NAND:
        // NAND nand0 (o, i0, i1, i2)
        for(int i = 1; i < n; i++){
            gate_outM << getIOstring(i, 'L') << ' ';
            gate_outL << getIOstring(i, 'M') << ' ';
        }
        gate_outM << getIOstring(0, 'M') << "\n";
        gate_outL << getIOstring(0, 'L') << "\n";
        for(int i = 1; i < n; i++){
            gate_outM << '1';
            gate_outL << '1';
        }
        gate_outM << " 0" << '\n';
        gate_outL << " 0" << '\n';
        break;

    case NOR:
        // NAND nand0 (o, i0, i1, i2)
        for(int i = 1; i < n; i++){
            gate_outM << getIOstring(i, 'L') << ' ';
            gate_outL << getIOstring(i, 'M') << ' ';
        }
        gate_outM << getIOstring(0, 'M') << "\n";
        gate_outL << getIOstring(0, 'L') << "\n";
        for(int i = 1; i < n; i++){
            gate_outM << '0';
            gate_outL << '0';
        }
        gate_outM << " 1" << '\n';
        gate_outL << " 1" << '\n';
        break;
    
    case DC:
        // _DC dc0 (o, c, d)
        assert(n == 3);
        // MSB
        gate_outM << getIOstring(1, 'M') << ' ' << getIOstring(2, 'L') << getIOstring(0, 'M') << '\n';
        gate_outM << "10 1" << '\n';
        // LSB
        gate_outL << getIOstring(1, 'L') << ' ' << getIOstring(2, 'L') << getIOstring(0, 'L') << '\n';
        gate_outL << "1- 1" << '\n' << "-1 1" << '\n';
        break;

    default:
        break;
    }

    outFile << gate_outM.str() << gate_outL.str();
}
