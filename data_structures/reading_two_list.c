#include "../file_handler.h"
#include "reading_two_list.h"



void add_second_reading_line(ReadingTwoList **rtl, char *label_name, ParsedCommand *ppc, ParsedInstruction *ppi,
                             BitsCommand *pbc, int row_num) {
    ReadingTwoList *sl, *node, *runner;
    if (!*rtl) {
        /**First allocation**/
        sl = (ReadingTwoList *) malloc(sizeof(ReadingTwoList));
        sl->row_num = row_num;
        if (ppc != NULL) {
            sl->ppc = ppc;
        }
        if (pbc != NULL) {
            sl->pbc = pbc;
        }
        if (ppi != NULL) {
            sl->ppi_instruction_type = ppi->instruction_type;
        }
        strcpy(sl->label_name, label_name);
        sl->next = NULL;
        *rtl = sl;

    } else {
        runner = *rtl;
        while (runner->next)
            runner = runner->next;
        node = (ReadingTwoList *) malloc(sizeof(ReadingTwoList));
        node->row_num = row_num;
        if (ppc != NULL) {
            node->ppc = ppc;
        }
        if (pbc != NULL) {
            node->pbc = pbc;
        }
        if (ppi != NULL) {
            node->ppi_instruction_type = ppi->instruction_type;
        }
        strcpy(node->label_name, label_name);
        node->next = NULL;
        runner->next = node;
    }

}

int validate_labels_at_second_running(InstructionCount *ic, SymbolsList **psl, ReadingTwoList **rtl, int no_errors) {
    SymbolsList *psl_runner;
    ReadingTwoList *rtl_runner;
    psl_runner = *psl;
    rtl_runner = *rtl;
    int is_there_match = 0;
    int are;
    int no_errors_function = TRUE;

    if(double_defined_label(rtl) == FALSE)
        return FALSE;

    if(double_defined_entry_extern(psl,rtl) == FALSE)
        return FALSE;

    

    while (rtl_runner) {
        while (psl_runner) {
            if (strcmp(psl_runner->symbol, rtl_runner->label_name) == 0) {
                is_there_match = 1;
                if (psl_runner->instruction_type == EXTERN_NO) {
                    are = 0; /**Extern**/
                } else {
                    are = 1; /**Relative to the current file**/
                }
                if (rtl_runner->ppi_instruction_type != ENTRY_NO && rtl_runner->ppi_instruction_type != EXTERN_NO) {
                    /**You shouldn't edit entry or extern command in the second running**/
                    edit_existing_row_are(rtl_runner->row_num, are);
                    edit_existing_row_label_address(rtl_runner->row_num, psl_runner->row_num);
                }
                if (rtl_runner->ppi_instruction_type == EXTERN_NO) {
                    write_entry_or_extern_to_file(rtl_runner->row_num, rtl_runner->label_name, EXTERN_FILENAME);
                    edit_existing_row_are(rtl_runner->row_num, are);
                    edit_existing_row_label_address(rtl_runner->row_num, 0);
                }
                if (rtl_runner->ppi_instruction_type == ENTRY_NO) {
                    write_entry_or_extern_to_file(psl_runner->row_num, rtl_runner->label_name, ENTRY_FILENAME);

                }
                break;
            }
            if (psl_runner->next == NULL)break;
            psl_runner = psl_runner->next;
        }

        if (is_there_match == 0) {
            /**This label was never defined in the source code**/
            no_errors_function = FALSE;
            printf("%s %s %s\n", THE_LABEL, rtl_runner->label_name, NOT_DEFINED_LABEL);
        }
        is_there_match = 0;
        psl_runner = *psl;
        rtl_runner = rtl_runner->next;
    }

    if (no_errors == TRUE && no_errors_function == TRUE) {
        return TRUE;
    }
    return FALSE;
}

/*The function chekcs if the label was double detemination of extern and entry*/
int double_defined_entry_extern (SymbolsList **psl, ReadingTwoList **rtl)
{
    SymbolsList *psl_runner;
    ReadingTwoList *rtl_runner;
    psl_runner = *psl;
    rtl_runner = *rtl; 
    while(rtl_runner)
    {
        while(psl_runner)
        {
           if (strcmp(psl_runner->symbol, rtl_runner->label_name) == 0)
                if(psl_runner->instruction_type == EXTERN_NO && rtl_runner->ppi_instruction_type == ENTRY_NO)
                {
                    printf("%s %s %s\n", THE_LABEL, rtl_runner->label_name, DOUBLE_DETEMINATION_EXTERN_ENTRY);
                    return FALSE;
                }
            if (psl_runner->next == NULL)break;
            psl_runner = psl_runner->next;
        }
        if (rtl_runner->next == NULL)break;
        rtl_runner = rtl_runner->next;
    }
}

/*The function chekcs if the label was double detemination*/
int double_defined_label(ReadingTwoList **rtl)
{
     ReadingTwoList *rtl_runner_one, *rtl_runner_second;
     rtl_runner_one = *rtl;
     rtl_runner_second = rtl_runner_one;

     while(rtl_runner_one)
     {
        while(rtl_runner_second)
        {
            if (strcmp(rtl_runner_one->label_name, rtl_runner_second->label_name) == 0)
                if(rtl_runner_one->ppi_instruction_type != ENTRY_NO && rtl_runner_second->ppi_instruction_type != ENTRY_NO)
                {
                    printf("%s %s %s\n", THE_LABEL, rtl_runner_one->label_name, DOUBLE_DETEMINATION_LABEL);
                    return FALSE;
                }

            if(rtl_runner_second->next == NULL) break;
            rtl_runner_second = rtl_runner_second->next;
        }
        if(rtl_runner_one->next == NULL)break;
        rtl_runner_one = rtl_runner_one->next;
     }

     return TRUE;

}