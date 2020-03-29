#ifndef FINAL_PROJECT_VALIDATOR_H
#define FINAL_PROJECT_VALIDATOR_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>


#define ERROR_IN_LINE "ERROR! in line"
#define THE_COMMAND "the command "

/**Error messages for labela**/
#define ERROR_LABEL_FIRST_CHAR "ERROR! the label doesn't start with a letter\n"
#define ERROR_LABEL_LENGTH "ERROR! the label maximum length is 31, the label is too longer\n"
#define ERROR_LABEL_LAST_CHAR "ERROR! the label should end with ':'\n"
#define ERROR_LABEL_ILLEGAL_CHAR "ERROR! the label should include only letters and digits\n"

#define INVALID_COMMAND " is invalid"
#define INCORRENT_COUNT_OPERANDS "num of operands is incorrect\n"

#define CAPITAL_LETTER_START 65
#define CAPITAL_LETTER_END 90
#define LOWER_CASE_LETTER_START 97
#define LOWER_CASE_LETTER_END 122
#define DIGITS_START 48
#define DIGITS_END 57

#define WRONG_DST_ADDRESSING_METHOD "wrong dst addressing method to the command "
#define WRONG_SRC_ADDRESSING_METHOD "wrong src addressing method to the command "
#define ILLEGAL_SRC_METHOD " can not had src operand"


int right_count_operands(char *command, int args_num, int row);

int valid_command_name(char *command, int row);

int valid_label(char *label, int size);

int length_label(char *array, int size);

int right_addressing_method_to_command(char *command, int dst_method, int src_method, int row);

#endif /*FINAL_PROJECT_VALIDATOR_H*/
