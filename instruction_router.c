#include "instruction_router.h"
#include "utils.h"
#include "file_handler.h"


void assign_arg_to_all_bits(BitsCommand *pbc, int binary_arg) {
    pbc->b0 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b1 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b2 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b3 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b4 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b5 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b6 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b7 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b8 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b9 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b10 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b11 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b12 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b13 = binary_arg % 10;
    binary_arg = binary_arg / 10;

    pbc->b14 = binary_arg % 10;
}


void instruction_router(ParsedInstruction *ppi, BitsCommand *pbc) {
    int i = 0, binary_member;
    int temp_arg;
    LinkedList *temp_head;
    if (ppi->instruction_type == DATA_NO || ppi->instruction_type == STRING_NO) {
        temp_head = &ppi->list;
        while (temp_head != NULL) {
            temp_arg = temp_head->val;
            /*checks id dec_to_binary works because the type parameter*/
            binary_member = dec_to_binary(temp_arg);
            assign_arg_to_all_bits(pbc + i, binary_member);
            write_command_to_file(pbc + i);
            temp_head = temp_head->next;
            i++;
        }

    }

    if (strcmp(ppi->instruction_type, ENTRY_NO) == 0) {

    } else if (strcmp(ppi->instruction_type, EXTERN_NO) == 0) {

    }
}
