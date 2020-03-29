#ifndef FINAL_PROJECT_INSTRUCTION_ROUTER_H
#define FINAL_PROJECT_INSTRUCTION_ROUTER_H

#include "parsed_instruction.h"
#include "bits_command.h"
#include "consts.h"
#include "data_structures/instruction_counter.h"

int instruction_router(char *filename, InstructionCount *ic, ParsedInstruction *ppi, BitsCommand *pbc, int);

#endif /*FINAL_PROJECT_INSTRUCTION_ROUTER_H*/
