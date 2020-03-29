#include <stdlib.h>
#include <string.h>

#include "command_router.h"
#include "addressing/instant_addressing.h"
#include "addressing/direct_addressing.h"
#include "addressing/indirect_register_addressing.h"
#include "addressing/direct_register_addressing.h"
#include "data_structures/reading_two_list.h"


int command_router(InstructionCount *ic, ParsedCommand *ppc, BitsCommand *pbc, int are,
                   ReadingTwoList **rtl,
                   SymbolsList **psl, int no_errors) {
    char *arg = (char *) malloc(sizeof(char *));
    int no_error_function = TRUE;

    /**integity checks**/

    /*valid command name*/
    if (valid_command_name(ppc->command) == FALSE) {
        no_error_function = FALSE;
        return FALSE;
    }

    /*right count operands*/
    if (right_count_operands(ppc->command, ppc->args_num) == FALSE) {
        no_error_function = FALSE;
        return FALSE;
    }

    /*right addressing method*/
    if (right_addressing_method_to_command(ppc->command, ppc->dst_addressing_method, ppc->src_addressing_method) ==
        FALSE) {
        return FALSE;
    }

    strcpy(arg, ppc->src);
    if (ppc->args_num == 1) {
        /**just jmp or prn**/
        strcpy(arg, ppc->dst);
    }

    if (ppc->args_num == 0) {
        none_operand(ppc, pbc);
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
        write_command_to_file(ic, pbc, BIN_FILENAME);
        ic->ic++;
        ic->row = START_ROW_NUM + ic->dc + ic->ic;
        return TRUE;
    }

    /**Instant Address**/
    if (ppc->src_addressing_method == INSTANT_ADDRESSING_NO || ppc->dst_addressing_method == INSTANT_ADDRESSING_NO) {
        if (command_instant_address(ppc->command) == TRUE) {
            run_instant_addressing(ic, ppc, pbc, are, rtl);
        }
        if (no_errors == TRUE && no_error_function == TRUE)
            return TRUE;
        return FALSE;
    }

    /**direct address**/
    /*TODO: we need to check if the label is already or will defined*/
    /*right command for direct address*/
    if (command_direct_and_indirect_register_address(ppc->command) == TRUE) {
        if (ppc->args_num == 1) {
            if (compare_register(ppc->dst) == FALSE) {
                run_direct_addressing(ic, ppc, pbc, are, rtl);
                if (no_errors == TRUE && no_error_function == TRUE)
                    return TRUE;
                return FALSE;
            }
        } else if (ppc->args_num == 2) {
            if (compare_register(ppc->src) == FALSE &&
                compare_register(ppc->dst) == FALSE) {
                run_direct_addressing(ic, ppc, pbc, are, rtl);
                if (no_errors == TRUE && no_error_function == TRUE)
                    return TRUE;
                return FALSE;
            }
        }
    }

    /**indirect register address**/
    if (ppc->src_addressing_method == INDIRECT_REGISTER_ADDRESSING_NO &&
        ppc->dst_addressing_method == INDIRECT_REGISTER_ADDRESSING_NO) {
        /**Two indirect registers**/
        if (command_direct_and_indirect_register_address(ppc->command) == TRUE) {
            if (compare_register(ppc->src) == FALSE) {
                /*Invalid source register name*/
                printf("%s %s %s\n", THE_REGISTER, ppc->src, INVALID_REGISTER_NAME);
                no_error_function = FALSE;
            }
            if (compare_register(ppc->dst) == FALSE) {
                /*Invalid source register name*/
                printf("%s %s %s\n", THE_REGISTER, ppc->dst, INVALID_REGISTER_NAME);
                no_error_function = FALSE;
            }
        } else {
            /*invalid command for the following indirect registers*/
            printf("%s %s %s\n", THE_COMMMAND, ppc->command, INVALID_COMMAND_INDIRECT);
            no_error_function = FALSE;
        }
        run_indirect_register_addressing(ic, ppc, pbc, are, rtl);
        if (no_errors == TRUE && no_error_function == TRUE)
            return TRUE;
        return FALSE;
    } else if (ppc->dst_addressing_method == INDIRECT_REGISTER_ADDRESSING_NO) {
        if (command_indirect_register_address_dst_arg_only(ppc->command) == TRUE) {
            /**Only dst is indirect register**/
            if (ppc->dst_addressing_method == INDIRECT_REGISTER_ADDRESSING_NO) {
                if (compare_register(ppc->dst) == FALSE) {
                    /*Invalid source register name*/
                    printf("%s %s %s\n", THE_REGISTER, ppc->dst, INVALID_REGISTER_NAME);
                    no_error_function = FALSE;
                } else {
                    run_indirect_register_addressing(ic, ppc, pbc, are, rtl);
                    if (no_errors == TRUE && no_error_function == TRUE)
                        return TRUE;
                    return FALSE;
                }
            }

        }
    } else {
        if (ppc->src_addressing_method == INDIRECT_REGISTER_ADDRESSING_NO) {
            if (compare_register(ppc->src) == FALSE) {
                /*Invalid source register name*/
                printf("%s %s %s\n", THE_REGISTER, ppc->src, INVALID_REGISTER_NAME);
                no_error_function = FALSE;
            } else {
                run_indirect_register_addressing(ic, ppc, pbc, are, rtl);
                if (no_errors == TRUE && no_error_function == TRUE)
                    return TRUE;
                return FALSE;
            }
        }

    }

    /**direct register address**/
    if (ppc->src_addressing_method == DIRECT_REGISTER_ADDRESSING_NO &&
        ppc->dst_addressing_method == DIRECT_REGISTER_ADDRESSING_NO) {
        /**Two indirect registers**/
        if (command_direct_register_address(ppc->command) == TRUE) {
            if (compare_register(ppc->src) == FALSE) {
                printf("%s %s %s\n", THE_REGISTER, ppc->src, INVALID_REGISTER_NAME);
                no_error_function = FALSE;
            }
            if (compare_register(ppc->dst) == FALSE) {
                printf("%s %s %s\n", THE_REGISTER, ppc->dst, INVALID_REGISTER_NAME);
                no_error_function = FALSE;
            }
        } else {
            /*invalid command for the following indirect registers*/
            printf("%s %s %s\n", THE_COMMMAND, ppc->command, INVALID_COMMAND_INDIRECT);
            no_error_function = FALSE;
        }
        run_direct_register_addressing(ic, ppc, pbc, are, rtl);
        if (no_errors == TRUE && no_error_function == TRUE)
            return TRUE;
        return FALSE;
    } else if (ppc->dst_addressing_method == DIRECT_REGISTER_ADDRESSING_NO) {
        if (command_direct_address_dst_arg_only(ppc->command) == TRUE) {
            /**Only dst is indirect register**/
            if (ppc->dst_addressing_method == DIRECT_REGISTER_ADDRESSING_NO) {
                if (compare_register(ppc->dst) == FALSE) {
                    printf("%s %s %s\n", THE_REGISTER, ppc->dst, INVALID_REGISTER_NAME);
                    no_error_function = FALSE;
                }
            }
        }
        run_direct_register_addressing(ic, ppc, pbc, are, rtl);
        if (no_errors == TRUE && no_error_function == TRUE)
            return TRUE;
        return FALSE;
    } else {
        if (ppc->src_addressing_method == DIRECT_REGISTER_ADDRESSING_NO) {
            if (compare_register(ppc->src) == FALSE) {
                printf("%s %s %s\n", THE_REGISTER, ppc->src, INVALID_REGISTER_NAME);
                no_error_function = FALSE;
            } else {
                run_direct_register_addressing(ic, ppc, pbc, are, rtl);
                if (no_errors == TRUE && no_error_function == TRUE)
                    return TRUE;
                return FALSE;
            }
        }

    }
    free(arg);
    /*if we here - none of the option is correct - the sentence isn't correct*/
}


/**auxiliary functions**/

/*just for stop and rts*/
void none_operand(ParsedCommand *ppc, BitsCommand *pbc) {
    int are = 2;
    assign_first_command(ppc, pbc, are);
    pbc->b3 = 0;
    pbc->b4 = 0;
    pbc->b5 = 0;
    pbc->b6 = 0;
    pbc->b7 = 0;
    pbc->b8 = 0;
    pbc->b9 = 0;
    pbc->b10 = 0;
}


int compare_register(char *cmp) {
    if (((strcmp(cmp, R0)) == 0) || ((strcmp(cmp, R1)) == 0) || ((strcmp(cmp, R2)) == 0) || ((strcmp(cmp, R3)) == 0) ||
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