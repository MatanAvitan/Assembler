#include "symbols_list.h"

void add_symbol(SymbolsList **psl, char *symbol, InstructionCount *ic, int instruction_type, int first_value,
                char *first_value_for_entry_or_extern, int is_entry_or_extern, int is_labeled_command) {
    /**Add symbol to the symbol list for validating in the second reading of the binary file**/

    SymbolsList *sl, *node, *runner;
    if (!*psl) {
        /**First allocation**/
        sl = (SymbolsList *) malloc(sizeof(SymbolsList));
        strcpy(sl->symbol, symbol);
        if(instruction_type != EXTERN_NO)
        {
          sl->row_num = ic->row;  
        }
        else
        {
            sl->row_num = 0;
        }
        
        sl->instruction_type = instruction_type;
        if (is_entry_or_extern) {
            strcpy(sl->first_value_for_entry_or_extern, first_value_for_entry_or_extern);
        } else
            sl->first_value = first_value;
        sl->is_labeled_command = is_labeled_command;
        sl->next = NULL;
        *psl = sl;
    } else {
        runner = *psl;
        while (runner->next)runner = runner->next;
        node = (SymbolsList *) malloc(sizeof(SymbolsList));
        strcpy(node->symbol, symbol);
        if(instruction_type != EXTERN_NO)
        {
            node->row_num = ic->row;
        }
        else
        {
            node->row_num = 0;
        }  
        node->instruction_type = instruction_type;
        if (is_entry_or_extern) {
            strcpy(node->first_value_for_entry_or_extern, first_value_for_entry_or_extern);
        } else
            node->first_value = first_value;
        node->is_labeled_command = is_labeled_command;
        node->next = NULL;
        runner->next = node;
    }
}