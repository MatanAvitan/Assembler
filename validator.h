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
#define STOP_INPUT "Hope you had a good time in my calculator :)\n‬‬"

int validate_commas(char *command);