#include <stdio.h>
#include <stdlib.h>
#include "instruction_sentences.h"

void run_instruction_sentences(ParsedInstruction *ppi, BitsCommand *pbc)
{
    if(ppi->instrction_type == DATA_NO || ppi->instrction_type == STRING_NO)
    {
        int i = 0, binary_arg;
        char*  temp_arg;
        LinkedList *temp_head = ppi->list;
        while(temp_head != NULL)
        {   
            temp_arg = temp_head->val;

            /*checks id dec_to_binary works becuase the type parameter*/
            binary_arg = dec_to_binary(&temp_head); /*not sure*/
            assign_arg_to_all_bits(pbc+i, binary_arg);
            write_command_to_file(pbc+i);
            temp_head = temp_head->next;
            i++;
        }
        /*if the label is exsist - put into the label the first arg*/
        if(ppi->label == NULL)
        {
           /*put itno the label at the table*/ 
        }  
    }
    /*entry or extren methos*/
    else
    {
        if(ppi->instrction_type == ENTRY_NO)
        {
            /*entery code*/
        }
        else
        {
            /*extern cose*/
        }

        /*add puls one to counter*/
    }
}

void assign_arg_to_all_bits(BitsCommand *pbc, int binary_arg) {
	pbc->b0 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b1 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b2 = binary_arg % 10;
    binary_arg = binary_arg / 10;   

    pbc->b3 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b4 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b5 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b6 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b7 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b8 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b9 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b10 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b11 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b12 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b13 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b14 = binary_arg % 10;
}

