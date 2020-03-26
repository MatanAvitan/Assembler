#ifndef FINAL_PROJECT_READING_TWO_LIST_H
#define FINAL_PROJECT_READING_TWO_LIST_H

#include "../parsed_command.h"
#include "../bits_command.h"
#include "../consts.h"
#include "reading_two_list.h"
#include "symbols_list.h"

#define THE_LABEL "ERROR! The label "
#define NOT_DEFINED_LABEL " was never defined in the source code"

typedef struct ReadingTwoList {
    char label_name[MAX_INSTRUCTION_LEN];
    ParsedCommand *ppc;
    BitsCommand *pbc;
    int row_num;
    struct ReadingTwoList *next;
} ReadingTwoList;

void add_second_reading_line(ReadingTwoList **rtl, char *, ParsedCommand *ppc, BitsCommand *pbc, int row_num);

int validate_labels_at_second_running(SymbolsList **psl, ReadingTwoList **rtl, int no_errors);

#endif /*FINAL_PROJECT_READING_TWO_LIST_H*/
