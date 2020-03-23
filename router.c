#include <stdlib.h>
#include <string.h>

#include "router.h"
#include "addressing/instant_addressing.h"
#include "addressing/direct_addressing.h"
#include "addressing/indirect_register_addressing.h"
#include "addressing/direct_register_addressing.h"


void routing(ParsedCommand *ppc, BitsCommand *pbc, int are) {
    char temp[4], *token, *seps_instanst = "#", *seps_indirect_register = "*";
    char *arg = (char *) malloc(sizeof(char *));
    strcpy(arg, ppc->src);
    if (ppc->args_num == 1) {
        /**just jmp or prn**/
        strcpy(arg, ppc->dst);
    }

    /**Instant Address**/
    if (ppc->src_addressing_method == INSTANT_ADDRESSING_NO || ppc->dst_addressing_method == INSTANT_ADDRESSING_NO) {
        if (command_instant_address(ppc->command) == TRUE) {
            run_instant_addressing(ppc, pbc, are);
        }
    }


    /**indirect register address**/
    if (command_direct_and_indirect_register_address(ppc->command) == TRUE) {
        strcpy(arg, ppc->src);
        if (ppc->args_num == 1) {
            strcpy(arg, ppc->dst);
            if (command_indirect_register_address_dst_arg_only(ppc->command) == FALSE)
                strcpy(arg, NULL);
        }
        if (arg[0] == '*') {
            token = strtok(arg, seps_indirect_register);
            strcpy(temp, token);
            if (compare_register(temp) == TRUE) {
                run_indirect_register_addressing(ppc, pbc, are);
                return;
            }

        }

    }

    /**direct address**/
    /*TODO: we need to check if the label is already or will defined*/
    /*right command for direct address*/
    if (command_direct_and_indirect_register_address(ppc->command) == TRUE) {
        strcpy(arg, ppc->src);
        if (ppc->args_num == 1) {
            if (command_direct_address_dst_arg_only(ppc->command) == TRUE)
                strcpy(arg, ppc->dst);
            else
                strcpy(arg, NULL);
        }
        if (compare_register(arg) == FALSE) {
//            run_direct_addressing(ppc, pbc, are);
            /*TODO: we need to check if the label is already or will defined*/
            return;
        }
    }

    /**direct register address**/
    if (command_direct_register_address(ppc->command) == TRUE) {
        if (ppc->args_num == 1) {
            strcpy(arg, ppc->dst);
            if (command_indirect_register_address_dst_arg_only(ppc->command) == FALSE) {
                strcpy(arg, NULL);
            }
        } else if (ppc->args_num == 2) {
            strcpy(arg, ppc->src);
        }
        if (compare_register(arg) == TRUE) {
            run_direct_register_addressing(ppc, pbc, are);
            return;
        }
    }
    free(arg);
    /*if we here - none of the option is correct - the sentence isn't correct*/
}


/**auxiliary functions**/

int to_decimal(char *number) {
    int int_number;
    int_number = atoi(number);

    if (int_number == 0)
        return FALSE;
    return TRUE;
}

int compare_register(char *cmp) {
    if (((strcmp(cmp, R1)) == 0) || ((strcmp(cmp, R2)) == 0) || ((strcmp(cmp, R3)) == 0) ||
        ((strcmp(cmp, R4)) == 0) || ((strcmp(cmp, R5)) == 0) || ((strcmp(cmp, R6)) == 0) ||
        ((strcmp(cmp, R7)) == 0))
        return TRUE;
    return FALSE;
}

int command_instant_address(char *command) {
    if ((strcmp(command, MOV)) == 0 || (strcmp(command, CMP)) == 0 || (strcmp(command, ADD)) == 0
        || (strcmp(command, SUB)) == 0 || (strcmp(command, PRN)) == 0)
        return TRUE;
    return FALSE;
}

int command_direct_and_indirect_register_address(char *command) {
    if (((strcmp(command, MOV)) == 0) || ((strcmp(command, CMP)) == 0) || ((strcmp(command, ADD)) == 0) ||
        ((strcmp(command, SUB)) == 0) || ((strcmp(command, LEA)) == 0) || ((strcmp(command, CLR)) == 0) ||
        ((strcmp(command, NOT)) == 0) || ((strcmp(command, INC)) == 0) || ((strcmp(command, DEC)) == 0) ||
        ((strcmp(command, JMP)) == 0) || ((strcmp(command, BNE)) == 0) || ((strcmp(command, RED)) == 0) ||
        ((strcmp(command, PRN)) == 0) || ((strcmp(command, JSR)) == 0))
        return TRUE;
    return FALSE;
}

int command_indirect_register_address_dst_arg_only(char *command) {
    if (((strcmp(command, CLR)) == 0) || ((strcmp(command, LEA)) == 0) ||
        ((strcmp(command, NOT)) == 0) || ((strcmp(command, INC)) == 0) || ((strcmp(command, DEC)) == 0) ||
        ((strcmp(command, JMP)) == 0) || ((strcmp(command, BNE)) == 0) || ((strcmp(command, RED)) == 0) ||
        ((strcmp(command, PRN)) == 0) || ((strcmp(command, JSR)) == 0))
        return TRUE;
    return FALSE;
}

int command_direct_register_address(char *command) {
    if (((strcmp(command, MOV)) == 0) || ((strcmp(command, CMP)) == 0) || ((strcmp(command, ADD)) == 0) ||
        ((strcmp(command, SUB)) == 0) || ((strcmp(command, LEA)) == 0) || ((strcmp(command, CLR)) == 0) ||
        ((strcmp(command, NOT)) == 0) || ((strcmp(command, INC)) == 0) || ((strcmp(command, DEC)) == 0) ||
        ((strcmp(command, RED)) == 0) || ((strcmp(command, PRN)) == 0))
        return TRUE;
    return FALSE;
}

int command_direct_address_dst_arg_only(char *command) {
    if (((strcmp(command, CLR)) == 0) ||
        ((strcmp(command, NOT)) == 0) || ((strcmp(command, INC)) == 0) || ((strcmp(command, DEC)) == 0) ||
        ((strcmp(command, JMP)) == 0) || ((strcmp(command, BNE)) == 0) || ((strcmp(command, RED)) == 0) ||
        ((strcmp(command, PRN)) == 0) || ((strcmp(command, JSR)) == 0))
        return TRUE;
    return FALSE;
}