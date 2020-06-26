/**CFile****************************************************************

  FileName    [demo.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [ABC as a static library.]

  Synopsis    [A demo program illustrating the use of ABC as a static library.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: demo.c,v 1.00 2005/11/14 00:00:00 alanmi Exp $]

***********************************************************************/

#include <stdio.h>
#include <time.h>

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
int main( int argc, char * argv[] )
{

    // variables
    Abc_Frame_t * pAbc;
    char Command[1000];
    clock_t  clk, clkend;

    //////////////////////////////////////////////////////////////////////////
    // start the ABC framework
    Abc_Start();
    pAbc = Abc_FrameGetGlobalFrame();

    while(1){
        printf("\n------------------------------------------------------");
        printf("\n------------------------------------------------------\n>> ");
        fgets(Command,1000,stdin);
        printf("%s\n",Command );
        clk = clock();
        if ( Cmd_CommandExecute( pAbc, Command ) )
        {
            fprintf( stdout, "Cannot execute command \"%s\".\n", Command );
        }
        clkend = clock() - clk;
        printf("---------\nuse %.3f seconds.\n",(float)clkend/1000 );
    }


    // stop the ABC framework
    Abc_Stop();
    return 0;
}

