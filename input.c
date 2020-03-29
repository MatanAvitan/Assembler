#include <stdio.h>
#include "consts.h"

void read_command(FILE *pfile, char *command_input) {
    /** Read command from file **/
    fgets(command_input, MAX_LINE, pfile);
}