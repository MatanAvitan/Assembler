#include "instruction_router.h"
#include "utils.h"
#include "file_handler.h"


void assign_arg_to_all_bits(BitsCommand *pbc, char *binary_arg) {
    pbc->b0 = binary_arg[MAX_BITS - 1];
    pbc->b1 = binary_arg[MAX_BITS - 2];
    pbc->b2 = binary_arg[MAX_BITS - 3];
    pbc->b3 = binary_arg[MAX_BITS - 4];
    pbc->b4 = binary_arg[MAX_BITS - 5];
    pbc->b5 = binary_arg[MAX_BITS - 6];
    pbc->b6 = binary_arg[MAX_BITS - 7];
    pbc->b7 = binary_arg[MAX_BITS - 8];
    pbc->b8 = binary_arg[MAX_BITS - 9];
    pbc->b9 = binary_arg[MAX_BITS - 10];
    pbc->b10 = binary_arg[MAX_BITS - 11];
    pbc->b11 = binary_arg[MAX_BITS - 12];
    pbc->b12 = binary_arg[MAX_BITS - 13];
    pbc->b13 = binary_arg[MAX_BITS - 14];
    pbc->b14 = binary_arg[MAX_BITS - 15];
}


int instruction_router(char *filename, InstructionCount *ic, ParsedInstruction *ppi, BitsCommand *pbc, int no_errors) {
    /**Router for the instruction command,
     * routes between the predefined instruction: data, string, entry and extern**/

    int i = 0;
    int no_error_function = TRUE;
    char covert_binary[MAX_BITS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int temp_arg;
    LinkedList *temp_head;
    if (ppi->instruction_type == DATA_NO || ppi->instruction_type == STRING_NO) {
        temp_head = &ppi->list;
        while (temp_head != NULL) {
            temp_arg = temp_head->val;
            if (dec_to_binary(temp_arg, MAX_BITS, covert_binary)) {
                assign_arg_to_all_bits(pbc + i, covert_binary);
                ic->row = START_ROW_NUM + ic->ic + ic->dc;
                write_command_to_file(ic, pbc + i, filename);
                ic->dc++;
                ic->row = START_ROW_NUM + ic->ic + ic->dc;
            } else {
                no_error_function = FALSE;
                printf("%s %d %s\n", THE_NUMBER, temp_arg, TOO_BIG_NUMBER);
            }
            temp_head = temp_head->next;
            i++;
        }

    }
    if (no_errors == TRUE && no_error_function == TRUE)
        return TRUE;
    return FALSE;
    /**Else we got an entry or extern which will be handled by the second reading**/
}
