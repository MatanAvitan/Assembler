#include <stdio.h>
#include "consts.h"

void read_command(char *command_input) {
    /* Read command from stdin */
    putchar('$');
    fgets(command_input, MAX_LINE, stdin);
}