#ifndef FINAL_PROJECT_PARSED_INSTRUCTION
#define FINAL_PROJECT_PARSED_INSTRUCTION

#include "consts.h"

typedef struct ParsedInstruction
{
    char prefix[MAX_ARG_SIZE];
    int instruction_addressing_method;
    char args[70];
    int args_num;
} ParsedInstruction;

ParsedInstruction *parse(char *, ParsedInstruction *);


#endif /*FINAL_PROJECT_PARSED_INSTRUCTION*/