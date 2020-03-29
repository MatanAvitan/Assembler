#ifndef FINAL_PROJECT_PARSED_INSTRUCTION
#define FINAL_PROJECT_PARSED_INSTRUCTION

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "consts.h"
#include "data_structures/instruction_counter.h"

#define THE_INSTRUCTION "The instruction "
#define IllEGAL_INSTRUCTION_NAME " is illegal"


typedef struct LinkedList {
    int val;
    char val_for_labels[MAX_INSTRUCTION_LEN];
    struct LinkedList *next;
} LinkedList;

typedef struct ParsedInstruction {
    char label[MAX_INSTRUCTION_LEN];
    int instruction_type;
    LinkedList list;
    int members_num;
} ParsedInstruction;


int parse_instruction(InstructionCount *ic, char *command, ParsedInstruction *ppi);

int starts_with_valid_instruction(char *str);

#endif /*FINAL_PROJECT_PARSED_INSTRUCTION*/
