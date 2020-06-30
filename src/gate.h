/**CFile****************************************************************
  
   FileName     [gate.h]
  
   Synopsis     [functions for verilog to blif for gates]
  
   Author       [Joshua Lin]
  
   Date         [Started - June 28, 2020.]
  
***********************************************************************/
#include <stdio.h>
#include <assert.h>

typedef enum gate_type{
    NONE,
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


void gate_blif(int GR, GATE g, char** IOname, int n, FILE * outFile)
{
    /* GR = 0 if revised; GR = 1 if golden */
    // gate g0 (i0, i1, i2, out);
    #define writeIOstring(i, ml) fprintf(outFile, "%s%s_%s", IOname[i], ml, GR_str)

    char GR_str[] = GR ? "gf" : "rf";

    switch (g)
    {
    case BUF:
        // buf buf0 (o, i);
        assert(n == 2);
        // MSB
        fprintf(outFile, ".names ");
        writeIOstring(1, 'M');
        fprintf(outFile, ' ');
        writeIOstring(0, 'M');
        fprintf(outFile, '\n');
        fprintf(outFile, "1 1\n");
        // LSB
        fprintf(outFile, ".names ");
        writeIOstring(1, 'L');
        fprintf(outFile, ' ');
        writeIOstring(0, 'L');
        fprintf(outFile, '\n');
        fprintf(outFile, "1 1\n");
        break;
    
    // case NOT:
    //     // not not0 (o, i);
    //     assert(n == 2);
    //     // MSB
    //     gate_outM << getIOstring(1, 'L') << ' ' << getIOstring(0, 'M') << "\n";
    //     gate_outM << "0 1" << '\n';
    //     // LSB
    //     gate_outL << getIOstring(1, 'M') << ' ' << getIOstring(0, 'L') << "\n";
    //     gate_outL << "0 1" << '\n';
    //     break;

    // case AND:
    //     // and and0 (o, i0, i1, i2)
    //     for(int i = 1; i < n; i++){
    //         gate_outM << getIOstring(i, 'M') << ' ';
    //         gate_outL << getIOstring(i, 'L') << ' ';
    //     }
    //     gate_outM << getIOstring(0, 'M') << "\n";
    //     gate_outL << getIOstring(0, 'L') << "\n";
    //     for(int i = 1; i < n; i++){
    //         gate_outM << '1';
    //         gate_outL << '1';
    //     }
    //     gate_outM << " 1" << '\n';
    //     gate_outL << " 1" << '\n';
    //     break;

    // case OR:
    //     // or or0 (o, i0, i1, i2)
    //     for(int i = 1; i < n; i++){
    //         gate_outM << getIOstring(i, 'M') << ' ';
    //         gate_outL << getIOstring(i, 'L') << ' ';
    //     }
    //     gate_outM << getIOstring(0, 'M') << "\n";
    //     gate_outL << getIOstring(0, 'L') << "\n";
    //     for(int i = 1; i < n; i++){
    //         gate_outM << '0';
    //         gate_outL << '0';
    //     }
    //     gate_outM << " 0" << '\n';
    //     gate_outL << " 0" << '\n';
    //     break;

    // case NAND:
    //     // nand nand0 (o, i0, i1, i2)
    //     for(int i = 1; i < n; i++){
    //         gate_outM << getIOstring(i, 'L') << ' ';
    //         gate_outL << getIOstring(i, 'M') << ' ';
    //     }
    //     gate_outM << getIOstring(0, 'M') << "\n";
    //     gate_outL << getIOstring(0, 'L') << "\n";
    //     for(int i = 1; i < n; i++){
    //         gate_outM << '1';
    //         gate_outL << '1';
    //     }
    //     gate_outM << " 0" << '\n';
    //     gate_outL << " 0" << '\n';
    //     break;

    // case NOR:
    //     // nor nor0 (o, i0, i1, i2)
    //     for(int i = 1; i < n; i++){
    //         gate_outM << getIOstring(i, 'L') << ' ';
    //         gate_outL << getIOstring(i, 'M') << ' ';
    //     }
    //     gate_outM << getIOstring(0, 'M') << "\n";
    //     gate_outL << getIOstring(0, 'L') << "\n";
    //     for(int i = 1; i < n; i++){
    //         gate_outM << '0';
    //         gate_outL << '0';
    //     }
    //     gate_outM << " 1" << '\n';
    //     gate_outL << " 1" << '\n';
    //     break;

    // case XOR:
    //     // xor xor0 (o, i0, i1, i2)
    //     // TODO
    //     break;

    // case XNOR:
    //     // xnor xnor0 (o, i0, i1, i2)
    //     // TODO
    //     break;
    
    // case DC:
    //     // _DC dc0 (o, c, d)
    //     assert(n == 3);
    //     // MSB
    //     gate_outM << getIOstring(1, 'M') << ' ' << getIOstring(2, 'L') << getIOstring(0, 'M') << '\n';
    //     gate_outM << "10 1" << '\n';
    //     // LSB
    //     gate_outL << getIOstring(1, 'L') << ' ' << getIOstring(2, 'L') << getIOstring(0, 'L') << '\n';
    //     gate_outL << "1- 1" << '\n' << "-1 1" << '\n';
    //     break;
    
    // case MUX:
    //     // _HMUX mux0 (o, i0, i1, s)
    //     // TODO
    //     break;

    default:
        printf("Error: Not acceptable gate_type!!\n");
        break;
    }
}

