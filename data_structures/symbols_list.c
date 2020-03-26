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
        {
            strcpy(sl->first_value_for_entry_or_extern, first_value_for_entry_or_extern);
        }
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
        {
            strcpy(sl->first_value_for_entry_or_extern, first_value_for_entry_or_extern);
        }
        else
            sl->first_value = first_value;
        node->next = NULL;
        runner->next = node;
    }
}


/*TODO: add this function to the second reading function to check all the symobol before checking the labels that mentioned in the file*/
/*just for entry or extern*/
/*The function gets a symbols_list head, the name of the symbol and instruction_type*/
int is_alreday_defined(SymbolsList **psl, char* symbol, int instruction_type)
{
    SymbolsList *runner;
    if(!*psl) return TRUE;
    else
    {
        runner = *psl;
        while(runner->next)
        {
            /*if the label is alreday defined*/
            if(strcmp(symbol, runner->symbol) == 0)
                if(instruction_type != runner->instruction_type)
                {
                    printf("ERROR! label alreday defined\n");
                    return FALSE;
                }
            runner = runner->next;
        }
        return TRUE;
    }
}