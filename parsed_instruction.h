#ifndef FINAL_PROJECT_PARSED_INSTRUCTION
#define FINAL_PROJECT_PARSED_INSTRUCTION

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "consts.h"

typedef struct LinkedList {
    int val;
    struct LinkedList *next;
} LinkedList;

typedef struct ParsedInstruction {
    char label[MAX_INSTRUCTION_LEN];
    int instruction_type;
    LinkedList list;
    int members_num;
} ParsedInstruction;


void parse_instruction(char *command, ParsedInstruction *ppi);

#endif /*FINAL_PROJECT_PARSED_INSTRUCTION*/
