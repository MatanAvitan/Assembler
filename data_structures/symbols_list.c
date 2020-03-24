#include "symbols_list.h"

void add_symbol(SymbolsList **psl, char *symbol, int row_num, int instruction_type, int first_value,
                char *first_value_for_entry_or_extern, int is_entry_or_extern) {
    SymbolsList *sl, *node, *runner;
    if (!*psl) {
        /**First allocation**/
        sl = (SymbolsList *) malloc(sizeof(SymbolsList));
        strcpy(sl->symbol, symbol);
        sl->row_num = row_num;
        sl->instruction_type = instruction_type;
        if (is_entry_or_extern)
            strcpy(sl->first_value_for_entry_or_extern, first_value_for_entry_or_extern);
        else
            sl->first_value = first_value;
        sl->next = NULL;
        *psl = sl;
    } else {
        runner = *psl;
        while (runner->next)runner = runner->next;
        node = (SymbolsList *) malloc(sizeof(SymbolsList));
        strcpy(node->symbol, symbol);
        node->row_num = row_num;
        node->instruction_type = instruction_type;
        if (is_entry_or_extern)
            strcpy(sl->first_value_for_entry_or_extern, first_value_for_entry_or_extern);
        else
            sl->first_value = first_value;
        node->next = NULL;
        runner->next = node;
    }
}