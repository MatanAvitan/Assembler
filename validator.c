#include "consts.h"
#include "validator.h"



/*The function gets a command and number of arguments and returs true if the command have the right operand's number*/
/*we assume the command is right and alreday checked*/
int right_count_operands(char *command, int args_num, int row) {
    if ((strcmp(command, MOV) == 0) || strcmp(command, CMP) == 0 || strcmp(command, ADD) == 0
        || strcmp(command, SUB) == 0 || strcmp(command, LEA) == 0) {
        /*command need 2 operand*/
        if (args_num != 2) {
            printf("%s %d %s", ERROR_IN_LINE, row, INCORRENT_COUNT_OPERANDS);
            return FALSE;
        }
    } else if (strcmp(command, CLR) == 0 || strcmp(command, NOT) == 0 ||
               strcmp(command, INC) == 0 || strcmp(command, DEC) == 0 ||
               strcmp(command, JMP) == 0 || strcmp(command, BNE) == 0 ||
               strcmp(command, RED) == 0 || strcmp(command, PRN) == 0 ||
               strcmp(command, JSR) == 0) {
        /*command need 1 operand*/
        if (args_num != 1) {
            printf("%s %d %s", ERROR_IN_LINE, row, INCORRENT_COUNT_OPERANDS);
            return FALSE;
        }
    } else {
        /*command need 1 operand*/
        if (args_num != 0) {
            printf("%s %d %s", ERROR_IN_LINE, row, INCORRENT_COUNT_OPERANDS);
            return FALSE;
        }
    }
    return TRUE;

}


/*The function gets a command and returns true if the command is valid and else returns false*/
int valid_command_name(char *command, int row) {
    if (strcmp(command, MOV) == 0 || strcmp(command, CMP) == 0 || strcmp(command, ADD) == 0
        || strcmp(command, SUB) == 0 || strcmp(command, LEA) == 0 || strcmp(command, CLR) == 0
        || strcmp(command, NOT) == 0 || strcmp(command, INC) == 0 || strcmp(command, DEC) == 0
        || strcmp(command, JMP) == 0 || strcmp(command, BNE) == 0 || strcmp(command, RED) == 0
        || strcmp(command, PRN) == 0 || strcmp(command, JSR) == 0 || strcmp(command, RTS) == 0
        || strcmp(command, STOP) == 0)
        return TRUE;
    printf("%s %d %s %s %s\n", ERROR_IN_LINE, row, THE_COMMAND, command, INVALID_COMMAND);
    return FALSE;
}


/*The function gets the label and checks if it is valid and returs true if the label is valid and else false*/
int valid_label(char *label, int size) {
    int length = 0, i = 0;
    if (label != NULL) {
        /*65 to 72 ot 97 to 122*/
        if ((label[0] >= CAPITAL_LETTER_START && label[0] <= CAPITAL_LETTER_END) ||
            (label[0] >= LOWER_CASE_LETTER_START || label[0] <= LOWER_CASE_LETTER_END)) {
            length = length_label(label, size);

            /*if the label is too long*/
            if (length > 31) {
                printf(ERROR_LABEL_LENGTH);
                return FALSE;
            }
            /*if the label is with letters or digits*/
            while (i != length) {
                if ((label[i] < CAPITAL_LETTER_START || label[i] > CAPITAL_LETTER_END) &&
                    (label[i] < LOWER_CASE_LETTER_START || label[i] > LOWER_CASE_LETTER_END) &&
                    (label[i] < DIGITS_START || label[i] > DIGITS_END)) {
                    printf(ERROR_LABEL_ILLEGAL_CHAR);
                    return FALSE;
                }

                i++;
            }

            return TRUE;
        } else {
            /*The label dosent start with letter*/
            printf(ERROR_LABEL_FIRST_CHAR);
            return FALSE;
        }
    }
    /*the label is null - there is not label*/
    return TRUE;
}

/*The function gets a char array and count the length*/
int length_label(char *array, int size) {
    int count = 0, i = 0;

    while (i != size) {
        /*check if there is NULL*/
        if (array[i] != 0)
            count++;
        else
            break;
        i++;
    }

    return count;
}


/*The function chekcs the right addressing members to every command and return false and true*/
int right_addressing_method_to_command(char *command, int dst_method, int src_method, int row) {
    if ((strcmp(command, MOV) == 0) || (strcmp(command, ADD) == 0) || (strcmp(command, SUB) == 0)) {
        if (dst_method == INSTANT_ADDRESSING_NO) {
            printf("%s %d %s %s\n", ERROR_IN_LINE, row, WRONG_DST_ADDRESSING_METHOD, command);
            return FALSE;
        }
    }

    if (strcmp(command, LEA) == 0) {
        if (src_method == INSTANT_ADDRESSING_NO) {
            printf("%s %d %s %s\n", ERROR_IN_LINE, row, WRONG_SRC_ADDRESSING_METHOD, command);
            return FALSE;
        }
        if (dst_method == INSTANT_ADDRESSING_NO) {
            printf("%s %d %s %s\n", ERROR_IN_LINE, row, WRONG_DST_ADDRESSING_METHOD, command);
            return FALSE;
        }
    }

    if ((strcmp(command, CLR) == 0) || (strcmp(command, NOT) == 0) || (strcmp(command, INC) == 0) ||
        (strcmp(command, DEC) == 0) || (strcmp(command, RED) == 0)) {
        if (src_method != UNKNOWN_COMMAND_NO) {
            printf("%s %d %s %s %s\n", ERROR_IN_LINE, row, THE_COMMAND, command, ILLEGAL_SRC_METHOD);
            return FALSE;
        }
        if (dst_method == INSTANT_ADDRESSING_NO) {
            printf("%s %d %s %s\n", ERROR_IN_LINE, row, WRONG_DST_ADDRESSING_METHOD, command);
            return FALSE;
        }
    }

    if ((strcmp(command, JMP) == 0) || (strcmp(command, BNE) == 0) || (strcmp(command, JSR) == 0)) {
        if (src_method != UNKNOWN_COMMAND_NO) {
            printf("%s %d %s %s %s\n", ERROR_IN_LINE, row, THE_COMMAND, command, ILLEGAL_SRC_METHOD);
            return FALSE;
        }
        if (dst_method == INSTANT_ADDRESSING_NO || dst_method == DIRECT_REGISTER_ADDRESSING_NO) {
            printf("%s %d %s %s\n", ERROR_IN_LINE, row, WRONG_DST_ADDRESSING_METHOD, command);
            return FALSE;
        }
    }

    if ((strcmp(command, PRN) == 0)) {
        if (src_method == UNKNOWN_COMMAND_NO)
            return TRUE;
    }

    return -1;
}
