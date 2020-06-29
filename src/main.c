/**CFile****************************************************************

  FileName    [main.c]

  Synopsis    [The main c file.]

  Author      [Ray Yang]

  Date        [Started - June 30, 2020.]

***********************************************************************/
#include "gate.h"
#include <stdio.h>
#include <string.h>


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
    // open gf file
    FILE * gf = fopen(filename_gf,"r");
    if (gf == NULL){
        printf( "Error: read \"%s\" file got error\n",filename_gf);
        return 1;
    }

    //////////////////////////////////////////////////////////////////////////
    // read gf file and write gf.blif

    int gf_len = strlen(filename_gf) + 3 + 1; // .v -> .blif
    char filename_gf_blif[ gf_len ];

    memset(filename_gf_blif, '\0', gf_len);
    strncat(filename_gf_blif,filename_gf,gf_len-5);
    strcat(filename_gf_blif,"blif");
    FILE * gf_blif = fopen(filename_gf_blif,"w");
    // // printf("after concate : %s\nlength = %d\n", filename_gf_blif,strlen(filename_gf));

    fprintf(gf_blif,"# .blif file of \"%.*s\" written by xec file.\n", gf_len-4, filename_gf );


    char *last = strrchr(filename_gf_blif, '/');
    fprintf(gf_blif,".model %.*s\n", (int)strlen(last+1)-5,last+1 );
    char * line = NULL;
    char * ptr = NULL;
    size_t len = 0;
    ssize_t read;
    
    ssize_t ret;
    

    while ((read = getdelim(&line, &len,';', gf)) != -1) {
        // fprintf(gf_blif,"%s", line);
        ptr = line;
        Header header = DEFAULT_HEADER;
        while (1) {
            if (strncmp(ptr, "\n", 1) == 0 ) {
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
        // fprintf(gf_blif,"%s\n", ptr);
        if (strncmp(ptr, "module", 6) ==0) {
            header = MODULE;
            ptr += 11;
            ptr = strtok(ptr, ")");
            fprintf(gf_blif,"MODULE :\n%s\n", ptr);
        }
        else if (strncmp(ptr, "input", 5) ==0) {
            header = INPUT;
            ptr += 6;
            ptr = strtok(ptr, ";");
            fprintf(gf_blif,"INPUT :\n%s\n", ptr);
        }
        else if (strncmp(ptr, "output", 6) ==0) {
            header = OUTPUT;
            ptr += 7;
            ptr = strtok(ptr, ";");
            fprintf(gf_blif,"OUTPUT :\n%s\n", ptr);
        }
        else if (strncmp(ptr, "wire", 4) ==0) {
            header = WIRE;
            ptr += 5;
            ptr = strtok(ptr, ";");
            fprintf(gf_blif,"WIRE :\n%s\n", ptr);
        }
        else if (strncmp(ptr, "endmodule", 4) ==0) {
            header = END;
            fprintf(gf_blif,".end\n");
        }
        else {      // gate
            header = GATE;
            Gate gate = DEFAULT_GATE;
            if (strncmp(ptr, "and", 3) ==0) {
                gate = AND;
                ptr += 4;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"AND :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "or", 2) ==0) {
                gate = OR;
                ptr += 3;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"OR :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "nand", 4) ==0) {
                gate = NAND;
                ptr += 5;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"NAND :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "nor", 3) ==0) {
                gate = NOR;
                ptr += 4;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"NOR :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "not", 3) ==0) {
                gate = NOT;
                ptr += 4;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"NOT :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "buf", 3) ==0) {
                gate = BUF;
                ptr += 4;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"BUF :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "xor", 3) ==0) {
                gate = XOR;
                ptr += 4;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"XOR :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "xnor", 4) ==0) {
                gate = XNOR;
                ptr += 5;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"XNOR :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "_DC", 3) ==0) {
                gate = DC;
                ptr += 4;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"DC :\n%s\n", ptr);
            }
            else if (strncmp(ptr, "_HMUX", 5) ==0) {
                gate = MUX;
                ptr += 6;
                ptr = strtok(ptr, ";");
                fprintf(gf_blif,"MUX :\n%s\n", ptr);
            }
        }
        
    }

    //////////////////////////////////////////////////////////////////////////
    // start the ABC framework
    Abc_Start();
    pAbc = Abc_FrameGetGlobalFrame();

    //Cmd_CommandExecute( pAbc, Command )


    // stop the ABC framework
    Abc_Stop();

    // free FILE pointer
    fclose(gf);
    fclose(gf_blif);
    return 0;
}