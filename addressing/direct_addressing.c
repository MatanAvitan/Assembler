
#include <stdio.h>

#include "../consts.h"
#include "../utils.h"
#include "direct_addressing.h"

void run_direct_addressing(ParsedCommand *ppc, BitsCommand *pbc, int are)
{
    printf("run_direct_addressing");

    /**FIRST*/

    /*command*/
    /*0-2 bits*/
    pbc->b0 = 0;
    pbc->b1 = 0;
    pbc->b2 = 1;

    /*3-6 bits*/
    pbc->b3 = 0;
    pbc->b4 = 1;
    pbc->b5 = 0;
    pbc->b6 = 0;

    /*7-10 bits*/
    pbc->b7 = 0;
    pbc->b8 = 0;
    pbc->b9 = 0;
    pbc->b10 = 0;

    /*opcode 11-14 bits*/
    pbc->b11 = 0;
    pbc->b12 = 0;
    pbc->b13 = 0;
    pbc->b14 = 0;

    assign_command_bits(ppc,pbc);

    /*SECOND*/
    /*adress of the label - we cant know here what is the adress (3-14 bits)*/

    /*0-2 bits*/
    switch(are)
    {
    	case 0:
            (pbc+1)->b0 = 1;
    		(pbc+1)->b1 = 0;
    		(pbc+1)->b2 = 0;
    		break;
    	case 1:
    		(pbc+1)->b0 = 0;
    		(pbc+1)->b1 = 1;
    		(pbc+1)->b2 = 0;
    		break;
    	case 2:
    		(pbc+1)->b0 = 0;
    		(pbc+1)->b1 = 0;
    		(pbc+1)->b2 = 1;
    		break;
    }

    /*11-14 bits*/
    (pbc+1)->b11 = 0;
    (pbc+1)->b12 = 0;
    (pbc+1)->b13 = 0;
    (pbc+1)->b14 = 0;

    /*we dont need pbc[2]*/
}