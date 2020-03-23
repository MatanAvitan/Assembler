#include <stdlib.h>
#include "consts.h"
#include "input.h"
#include "command_router.h"
#include "parsed_instruction.h"
#include "instruction_router.h"


int main() {
    char command_input[MAX_LINE] = {0};
    ParsedCommand *ppc;
    ParsedInstruction *ppi;
    BitsCommand *pbc;
    int are;
    read_command(command_input);
    ppc = (ParsedCommand *) malloc(sizeof(ParsedCommand));
    ppc = parse(command_input, ppc);
    if ((strcmp(ppc->command, TERMINATE) == 0) && (ppc->prefix != NULL)) {
        /**If the command parser failed to parse the command maybe it's an instruction sentence**/
        ppi = (ParsedInstruction *) malloc(sizeof(ParsedInstruction));
        /**The command parser already caught the label**/
        strcpy(ppi->label, ppc->prefix);
        parse_instruction(command_input, ppi);
        if (ppi->members_num == 0) {
            /**Parsing error**/
            printf("Failed to parse the given command");
            return 0;
        } else {
            /**We have a valid instruction sentence command**/
            pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * ppi->members_num);
            instruction_router(ppi, pbc);
            /**todo: free() dont forget to free all**/
            return 1;
        }
    }
    pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * MAX_NUM_OF_TRANSLATION_COMMANDS);
    /**Run first time and assign all the declaration variables to three lists A, R, E.
     *Then call to the get_are(command) and pass the output to the command_router function.**/
    are = 2;
    command_router(ppc, pbc, are);
}
