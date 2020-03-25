#ifndef FINAL_PROJECT_READING_TWO_LIST_H
#define FINAL_PROJECT_READING_TWO_LIST_H

#include "../parsed_command.h"
#include "../bits_command.h"

typedef struct ReadingTwoList {
    char* label_name;
    ParsedCommand *ppc;
    BitsCommand *pbc;
    int row_num;
    struct ReadingTwoList *next;
} ReadingTwoList;

void add_second_reading_line(ReadingTwoList **rtl,char*, ParsedCommand *ppc, BitsCommand *pbc, int row_num);
void print_second_line(ReadingTwoList **);

#endif /*FINAL_PROJECT_READING_TWO_LIST_H*/
