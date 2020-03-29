#ifndef FINAL_PROJECT_READING_TWO_LIST_H
#define FINAL_PROJECT_READING_TWO_LIST_H

#include "../parsed_command.h"
#include "../bits_command.h"
#include "../consts.h"
#include "../parsed_instruction.h"
#include "reading_two_list.h"
#include "symbols_list.h"

#define THE_LABEL "ERROR! The label "
#define NOT_DEFINED_LABEL " was never defined in the source code"
#define DOUBLE_DETEMINATION_EXTERN_ENTRY " has double determination (entry and extern)"
#define DOUBLE_DETEMINATION_LABEL " has double determination"

typedef struct ReadingTwoList {
    char label_name[MAX_INSTRUCTION_LEN];
    ParsedCommand *ppc;
    BitsCommand *pbc;
    int ppi_instruction_type;
    int row_num;
    struct ReadingTwoList *next;
} ReadingTwoList;

void add_second_reading_line(ReadingTwoList **rtl, char *label_name, ParsedCommand *ppc, ParsedInstruction *ppi,
                             BitsCommand *pbc, int row_num);

int validate_labels_at_second_running(char *filename, InstructionCount *ic, SymbolsList **psl, ReadingTwoList **rtl, int no_errors);

#endif /*FINAL_PROJECT_READING_TWO_LIST_H*/
