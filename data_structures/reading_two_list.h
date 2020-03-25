#ifndef FINAL_PROJECT_READING_TWO_LIST_H
#define FINAL_PROJECT_READING_TWO_LIST_H

#include "../parsed_command.h"
#include "../bits_command.h"

typedef struct ReadingTwoList {
    ParsedCommand *ppc;
    BitsCommand *pbc;
    int row_num;
    struct symbols_list *next;
} ReadingTwoList;

void add_second_line_reading(ReadingTwoList **ptl, ParsedCommand *ppc, BitsCommand *pbc, int row_num);

#endif /*FINAL_PROJECT_READING_TWO_LIST_H*/
