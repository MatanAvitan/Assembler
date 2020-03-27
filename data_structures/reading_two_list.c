#include "../file_handler.h"


void add_second_reading_line(ReadingTwoList **rtl, char *label_name, ParsedCommand *ppc, ParsedInstruction *ppi,
                             BitsCommand *pbc, int row_num) {
    ReadingTwoList *sl, *node, *runner;
    if (!*rtl) {
        /**First allocation**/
        sl = (ReadingTwoList *) malloc(sizeof(ReadingTwoList));
        sl->row_num = row_num;
        sl->ppc = ppc;
        sl->pbc = pbc;
        if(ppi != NULL)
        {
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
        node->ppc = ppc;
        node->pbc = pbc;
        node->ppi_instruction_type = ppi->instruction_type;
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

    while (rtl_runner) {
        while (psl_runner) {
            if (strcmp(psl_runner->symbol, rtl_runner->label_name) == 0) {
                /**The label was used and actually defined**/
                is_there_match = 1;

                if (psl_runner->instruction_type == EXTERN_NO) {
                    are = 0; /**Extern**/
                } else {
                    are = 1; /**Relative**/
                }
                edit_existing_row_are(rtl_runner->row_num, are);
                edit_existing_row_label_address(rtl_runner->row_num, psl_runner->row_num);
                if (rtl_runner->ppi_instruction_type == ENTRY_NO) {
                    write_entry_or_extern_to_file(ic, rtl_runner->label_name, ENTRY_FILENAME);
                    ic->ic++;
                    ic->row = START_ROW_NUM + ic->ic + ic->dc;
                } else if (rtl_runner->ppi_instruction_type == EXTERN_NO) {
                    write_entry_or_extern_to_file(ic, rtl_runner->label_name, EXTERN_FILENAME);
                    ic->ic++;
                    ic->row = START_ROW_NUM + ic->ic + ic->dc;
                }
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
        if (rtl_runner->next == NULL)break;
        rtl_runner = rtl_runner->next;
    }

    if(no_errors == TRUE && no_errors_function == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}
