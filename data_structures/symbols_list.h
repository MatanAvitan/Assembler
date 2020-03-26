#ifndef FINAL_PROJECT_SYMBOLS_LIST_H
#define FINAL_PROJECT_SYMBOLS_LIST_H

#include <stdlib.h>
#include "string.h"
#include "../consts.h"


typedef struct SymbolsList {
    char symbol[MAX_INSTRUCTION_LEN];
    int row_num;
    int instruction_type;
    int first_value;
    char first_value_for_entry_or_extern[MAX_INSTRUCTION_LEN];
    struct symbols_list *next;
} SymbolsList;

void add_symbol(SymbolsList **psl, char *symbol, int row_num, int instruction_type, int first_value,
                char *first_value_for_entry_or_extern, int is_entry_or_extern);

int is_alreday_defined(SymbolsList **pls, char* symbol, int instruction_type);

#endif //FINAL_PROJECT_SYMBOLS_LIST_H
