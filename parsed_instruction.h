#ifndef FINAL_PROJECT_PARSED_INSTRUCTION
#define FINAL_PROJECT_PARSED_INSTRUCTION

typedef struct ParsedInstruction{
    char label[MAX_INSTRUCTION_LEN];
    int instruction_addressing_method;
    LinkedList list;
    int members_num;
} ParsedInstruction;

typedef struct LinkedList{
    char *val;
    LinkedList next;
}LinkedList;


#include "consts.h"

ParsedInstruction *parse(char *, ParsedInstruction *);


#endif /*FINAL_PROJECT_PARSED_INSTRUCTION*/
