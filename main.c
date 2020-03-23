#include <stdlib.h>
#include "consts.h"
#include "input.h"
#include "router.h"

int main() {
    char command_input[MAX_LINE] = {0};
    ParsedCommand *ppc;
    BitsCommand *pbc;
    int are;
    read_command(command_input);
    ppc = (ParsedCommand *) malloc(sizeof(ParsedCommand));
    pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * MAX_NUM_OF_TRANSLATION_COMMANDS);
    ppc = parse(command_input, ppc);
    /*Run first time and assign all the declaration variables to three lists A, R, E.
     *Then call to the get_are(command) and pass the output to the routing function.*/
    are=2;
    routing(ppc, pbc, are);

}
