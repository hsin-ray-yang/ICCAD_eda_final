/**CFile****************************************************************

  FileName    [main.c]

  Synopsis    [The main c file.]

  Author      [Ray Yang]

  Date        [Started - June 30, 2020.]

***********************************************************************/
#include "gate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
    char * filename_gf;
    char * filename_rf;
    char * filename_out;

    char ** output_gf;
    char ** output_rf;
    char ** input_gf;
    char ** input_rf;
    size_t output_gf_size;
    size_t output_rf_size;
    size_t input_gf_size;
    size_t input_rf_size;

    //////////////////////////////////////////////////////////////////////////
    // get the input file names
    if ( argc != 4 )
    {
        printf( "Wrong number of command-line arguments.\n" );
        printf( "Usage : ./xec <golden.v> <revised.v> <output>\n" );
        return 1;
    }
    filename_gf = argv[1];
    filename_rf = argv[2];
    filename_out = argv[3];

    //////////////////////////////////////////////////////////////////////////
    // open gf rf file
    FILE * gf = fopen(filename_gf,"r");

    if (gf == NULL){
        printf( "Error: read \"%s\" golden file got error\n",filename_gf);
        return 1;
    }

    FILE * rf = fopen(filename_rf,"r");

    if (rf == NULL){
        printf( "Error: read \"%s\" revise file got error\n",filename_rf);
        return 1;
    }

    //////////////////////////////////////////////////////////////////////////
    // read gf & rf file and write gf_rf.blif
    char *last_rf = strrchr(filename_rf, '/');
    size_t last_rf_size = (int)strlen(last_rf+1)-2;

    int gr_len = strlen(filename_gf) + 1 + last_rf_size + 3 + 1; // gf.v -> gf_rf.blif
    char filename_gr_blif[ gr_len ];

    memset(filename_gr_blif, '\0', gr_len);

    strncat(filename_gr_blif,filename_gf,gr_len-7-last_rf_size);
    strcat(filename_gr_blif,"_");
    strncat(filename_gr_blif,last_rf+1,last_rf_size);
    strcat(filename_gr_blif,".blif");

    FILE * gr_blif = fopen(filename_gr_blif,"w");

    fprintf(gr_blif,"# .blif file of \"%s\" and \"%s\" written by xec file.\n", filename_gf, filename_rf );

    // write first line
    char *last = strrchr(filename_gr_blif, '/');
    fprintf(gr_blif,".model %.*s\n", (int)strlen(last+1)-5,last+1 );

    write_blif(1,gr_blif,gf,&input_gf, &input_gf_size, &output_gf, &output_gf_size);
    fclose(gf);
    write_blif(0,gr_blif,rf,&input_rf, &input_rf_size, &output_rf, &output_rf_size);
    fclose(rf);

    

    // for(int i=0;i< output_gf_size;++i){
    //     printf("%s ",(output_gf)[i]);
    // }
    // printf("\n");

    // for(int i=0;i< input_gf_size;++i){
    //     printf("%s ",(input_gf)[i]);
    // }
    // printf("\n");

    for(int i=0;i< output_rf_size;++i){
        printf("%s ",(output_rf)[i]);
    }
    printf("\n");

    for(int i=0;i< input_rf_size;++i){
        printf("%s ",(input_rf)[i]);
    }
    printf("\n");


    //////////////////////////////////////////////////////////////////////////
    // start the ABC framework
    Abc_Start();
    pAbc = Abc_FrameGetGlobalFrame();

    //Cmd_CommandExecute( pAbc, Command )


    // stop the ABC framework
    Abc_Stop();

    // free FILE pointer
    fclose(gr_blif);
    return 0;
}