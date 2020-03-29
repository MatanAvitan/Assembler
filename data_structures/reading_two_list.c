#include "../file_handler.h"


void add_second_reading_line(ReadingTwoList **rtl, char *label_name, ParsedCommand *ppc, ParsedInstruction *ppi,
                             BitsCommand *pbc, int row_num) {
    /**The function gets the parameter to add a line to second round. create a new node of ReadingTwoList**/

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


int validate_labels_at_second_running(char *filename, InstructionCount *ic, SymbolsList **psl, ReadingTwoList **rtl,
                                      int no_errors) {
    /**This function ran on the second round. ran over the symbol list and thr reading two list and changes the lines**/
    SymbolsList *psl_runner;
    ReadingTwoList *rtl_runner;
    int is_there_match;
    int are;
    int no_errors_function = TRUE;
    char entry_filename[MAX_LINE];
    char extern_filename[MAX_LINE];
    psl_runner = *psl;
    rtl_runner = *rtl;
    is_there_match = 0;
    strcpy(entry_filename, filename);
    strcpy(extern_filename, filename);
    strcat(entry_filename, ENTRY_FILENAME_EXT);
    strcat(extern_filename, EXTERN_FILENAME_EXT);
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
                    edit_existing_row_are(filename, rtl_runner->row_num, are);
                    edit_existing_row_label_address(filename, rtl_runner->row_num, psl_runner->row_num);
                }
                /*if extern - you should write to extern file and change the line to 0 address*/
                if (psl_runner->instruction_type == EXTERN_NO) {
                    write_entry_or_extern_to_file(rtl_runner->row_num, rtl_runner->label_name, extern_filename);
                    edit_existing_row_are(filename, rtl_runner->row_num, are);
                    edit_existing_row_label_address(filename, rtl_runner->row_num, 0);
                }
                /*if entry - only write to the entry file*/
                if (rtl_runner->ppi_instruction_type == ENTRY_NO) {
                    write_entry_or_extern_to_file(psl_runner->row_num, rtl_runner->label_name, entry_filename);

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
