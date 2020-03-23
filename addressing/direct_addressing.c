
#include <stdio.h>

#include "../consts.h"
#include "../utils.h"
#include "direct_addressing.h"

void run_direct_addressing(ParsedCommand *ppc, BitsCommand *pbc, int are)
{
    /**FIRST*/

    int i = 0;

    /**First command**/
    assign_first_command(ppc, pbc, are);
    

    /*SECOND*/
   
    /*0-2 bits*/
    are = 1;
    assign_are_bits(pbc+1,are);
  
    /*adress of the label - we cant know here what is the adress (3-14 bits)*/

    /*11-14 bits*/
    (pbc+1)->b11 = 0;
    (pbc+1)->b12 = 0;
    (pbc+1)->b13 = 0;
    (pbc+1)->b14 = 0;

    /*we dont need pbc[2]*/
    for (; i < ppc->args_num + 1; i++) {
        /**Write the command to the bin file**/
        write_command_to_file(pbc + i);
    }
}