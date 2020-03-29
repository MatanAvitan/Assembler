#ifndef FINAL_PROJECT_VALIDATOR_H
#define FINAL_PROJECT_VALIDATOR_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FAILED_TO_FETCH_COMMAND "Failed to fetch a command\n"
#define ILLEGAL_COMMA "Illegel comma\n"
#define MISSING_COMMA "Missing comma\n"
#define MULTI_COMMAS "Multiple consecutive commas\n"
#define NOT_AN_INTEGER "Invalid set member – not an integer\n"
#define SET_MEMBERS_TERMINATIONS_ERROR "List of set members is not terminated correctly\n"
#define OUT_OF_RANGE_MSG "Invalid set member – value out of range\n"
#define EXTRA_PARAMS_WAS_FOUND "Extraneous text after end of command\n"
#define UNFILLED_PARAMS_WAS_FOUND "You did'nt provide all the params for the command\n"
#define WRONG_NUMBER_OF_PARAMS "The number of sets you have entered does'nt suits the command\n"
#define FAILED_TO_FETCH_COMMAND "Failed to fetch a command\n"
#define COMMAND_NOT_FOUND "Invalid command – command not found\n"
#define UNDEFINED_SET_NAME "Undefined set name\n"
#define SET_MEMBERS_TERMINATIONS_ERROR "List of set members is not terminated correctly\n"
#define OUT_OF_RANGE_MSG "Invalid set member – value out of range\n"
#define EMPTY_SET "‫‪The‬‬ ‫‪set‬‬ ‫‪is‬‬ ‫‪empty\n‬‬"


#define ERROR_IN_LINE "ERROR! in line"
#define THE_COMMAND "the command "

/*error messange - label*/
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

#define WORONG_DST_ADDRESSING_METHOD "wrong dst addressing method to the command "
#define WORONG_SRC_ADDRESSING_METHOD "wrong src addressing method to the command "
#define ILLGAL_SRC_METHOD " can not had src operand"


int validate_commas(char *command);

int right_count_operands(char* command, int args_num, int row);

int valid_command_name(char* command, int row);

int right_instruction_count_operand(int instruction_type, int members_num, int row);

int valid_label(char* label);

int length_label (char* array);

int right_addressing_method_to_command(char* command, int dst_method, int src_method, int row);

/*int right_count_operands_instruction(ParsedInstruction *ppi);*/

#endif /*FINAL_PROJECT_VALIDATOR_H*/
