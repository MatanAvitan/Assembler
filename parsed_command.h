#ifndef FINAL_PROJECT_PARSED_COMMAND_H
#define FINAL_PROJECT_PARSED_COMMAND_H

#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "validator.h"

typedef struct ParsedCommand {
    char command[20];
    char prefix[MAX_ARG_SIZE];
    char src[MAX_ARG_SIZE];
    int src_addressing_method;
    char dst[MAX_ARG_SIZE];
    int dst_addressing_method;
    int args_num;
} ParsedCommand;


ParsedCommand *parse(char *, ParsedCommand *);


#endif //FINAL_PROJECT_PARSED_COMMAND_H