#include <stdlib.h>
#include "consts.h"
#include "input.h"
#include "command_router.h"
#include "parsed_instruction.h"
#include "instruction_router.h"
#include "data_structures/symbols_list.h"
#include "data_structures/reading_two_list.h"
#include "utils.h"

extern ic;

int main() {
    char command_input[MAX_LINE] = {0};
    ParsedCommand *ppc;
    ParsedInstruction *ppi;
    BitsCommand *pbc;
    SymbolsList *sl = {0};
    ReadingTwoList *rtl = {0};
    int are, is_entry_or_extern = 0;
    read_command(command_input);
    ppc = (ParsedCommand *) malloc(sizeof(ParsedCommand));
    ppc = parse(command_input, ppc);
    while (strcmp(ppc->command, STOP) != 0) {
        if (strcmp(ppc->command, TERMINATE) == 0) {
            if (strlen(ppc->prefix) != 0 || starts_with_valid_instruction(command_input)) {
                /**If the command parser failed to parse the command maybe it's an instruction sentence**/
                ppi = (ParsedInstruction *) malloc(sizeof(ParsedInstruction));
                /**The command parser already caught the label**/
                strcpy(ppi->label, ppc->prefix);
                parse_instruction(command_input, ppi);
                if (ppi->members_num == 0) {
                    /**Parsing error**/
                    /**Fetch command**/
                    read_command(command_input);
                    continue;
                } else {
                    /**We have a valid instruction sentence command**/
                    if (strlen(ppi->label) != 0) {
                        if (strlen(ppi->list.val_for_labels) != 0) {
                            is_entry_or_extern = 1;
                        }
                        add_symbol(&sl, ppi->label, ic, ppi->instruction_type, ppi->list.val, ppi->list.val_for_labels,
                                   is_entry_or_extern);
                    }
                    pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * ppi->members_num);
                    instruction_router(ppi, pbc);
                    /**todo: free() dont forget to free all**/
                    /**Fetch command**/
                    read_command(command_input);
                    ppc = parse(command_input, ppc);
                    free(ppi);
                    free(pbc);
                    continue;
                }
            } else {
                /**We got stop command**/
                break;
            }
        } else {
            /**Regular command**/
            pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * MAX_NUM_OF_TRANSLATION_COMMANDS);
            /**Run first time and assign all the declaration variables to three lists A, R, E.
             *Then call to the get_are(command) and pass the output to the command_router function.**/
            are = 2;
            command_router(ppc, pbc, are, &rtl);
            read_command(command_input);
            ppc = parse(command_input, ppc);
        }

    }
    if (ppc) {
        free(ppc);
    }
    validate_labels_at_second_running(&sl, &rtl);
    /*TODO: add an conditional if there are error until here - and just than make_hex_file*/
//    create_hex_file(ic, HEX_FILENAME);
}
