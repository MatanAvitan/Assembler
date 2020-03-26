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


void instruction_router(InstructionCount *ic, ParsedInstruction *ppi, BitsCommand *pbc) {
    int i = 0;
    char covert_binary[MAX_BITS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int temp_arg;
    LinkedList *temp_head;
    if (ppi->instruction_type == DATA_NO || ppi->instruction_type == STRING_NO) {
        temp_head = &ppi->list;
        while (temp_head != NULL) {
            temp_arg = temp_head->val;
            if (dec_to_binary(temp_arg, MAX_BITS, covert_binary)) {
                assign_arg_to_all_bits(pbc + i, covert_binary);
                write_command_to_file(ic, pbc + i, BIN_FILENAME);
                ic->dc ++;
                ic->row = START_ROW_NUM + ic->ic + ic->dc;
            }
            temp_head = temp_head->next;
            i++;
        }

    }
    if (ppi->instruction_type == ENTRY_NO) {
        write_entry_or_extern_to_file(ic, ppi, ENTRY_FILENAME);
        ic->ic++;
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
    } else if (ppi->instruction_type == EXTERN_NO) {
        write_entry_or_extern_to_file(ic, ppi, EXTERN_FILENAME);
        ic->ic++;
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
    }
}
