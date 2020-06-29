/**CFile****************************************************************

  FileName    [main.cpp]

  Synopsis    [The main cpp file.]

  Author      [Joshua Lin]

  Date        [Started - June 29, 2020.]

***********************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "gate.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

#if defined(ABC_NAMESPACE)
namespace ABC_NAMESPACE
{
#elif defined(__cplusplus)
extern "C"
{
#endif

// procedures to start and stop the ABC framework
// (should be called before and after the ABC procedures are called)
void   Abc_Start();
void   Abc_Stop();

// procedures to get the ABC framework and execute commands in it
typedef struct Abc_Frame_t_ Abc_Frame_t;

Abc_Frame_t * Abc_FrameGetGlobalFrame();
int    Cmd_CommandExecute( Abc_Frame_t * pAbc, const char * sCommand );

#if defined(ABC_NAMESPACE)
}
using namespace ABC_NAMESPACE;
#elif defined(__cplusplus)
}
#endif

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [The main() procedure.]

  Description [This procedure compiles into a stand-alone program for 
  DAG-aware rewriting of the AIGs. A BLIF or PLA file to be considered
  for rewriting should be given as a command-line argument. Implementation 
  of the rewriting is inspired by the paper: Per Bjesse, Arne Boralv, 
  "DAG-aware circuit compression for formal verification", Proc. ICCAD 2004.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int main( int argc, char** argv )
{

    // variables
    Abc_Frame_t * pAbc;
    //char Command[1000];
    fstream input_gf, input_rf, blif_out, output;
    vector<string> IOnames;

    //////////////////////////////////////////////////////////////////////////
    // ===== read file ===== //
    // if (argc == 4) {
    //     input_gf.open(argv[1], ios::in);
    //     input_rf.open(argv[2], ios::in);
    //     output.open(argv[3], ios::out);
    //     if (!input_gf) {
    //         cerr << "Cannot open the input file \"" << argv[1]
    //              << "\". The program will be terminated..." << endl;
    //         exit(1);
    //     }
    //     if (!input_rf) {
    //         cerr << "Cannot open the input file \"" << argv[2]
    //              << "\". The program will be terminated..." << endl;
    //         exit(1);
    //     }
    //     if (!output) {
    //         cerr << "Cannot open the output file \"" << argv[3]
    //              << "\". The program will be terminated..." << endl;
    //         exit(1);
    //     }
    // }
    // else{
    //     cerr << "Usage: ./xec <golden.v> <revesed.v> <output>" << endl;
    //     exit(1);
    // }
    input_rf.open(argv[1], ios::in);
    blif_out.open(argv[2], ios::out);

    IOnames.push_back("input");
    IOnames.push_back("output");

    gate_blif(NOT, IOnames, blif_out);

    //////////////////////////////////////////////////////////////////////////
    // start the ABC framework
    Abc_Start();
    pAbc = Abc_FrameGetGlobalFrame();

    //Cmd_CommandExecute( pAbc, Command )


    // stop the ABC framework
    Abc_Stop();
    return 0;
}