#ifndef FINAL_PROJECT_PARSED_INSTRUCTION
#define FINAL_PROJECT_PARSED_INSTRUCTION

#include "consts.h"

typedef struct ParsedInstruction
{
    char label[MAX_ARG_SIZE];
    int instruction_addressing_method;
    char* args[MAX_LINE];
    int args_num;
} ParsedInstruction;

ParsedInstruction *parse(char *, ParsedInstruction *);


#endif /*FINAL_PROJECT_PARSED_INSTRUCTION*/
