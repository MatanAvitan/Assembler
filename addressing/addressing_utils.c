#include "addressing_utils.h"


int to_opcode(char *command) {
    int opcode = UNKNOWN_COMMAND_NO;
    if (strcmp(command, MOV) == 0) {
        opcode = MOV_NO;
    } else if (strcmp(command, CMP) == 0) {
        opcode = CMP_NO;
    } else if (strcmp(command, SUB) == 0) {
        opcode = SUB_NO;
    } else if (strcmp(command, ADD) == 0) {
        opcode = ADD_NO;
    } else if (strcmp(command, LEA) == 0) {
        opcode = LEA_NO;
    } else if (strcmp(command, CLR) == 0) {
        opcode = CLR_NO;
    } else if (strcmp(command, NOT) == 0) {
        opcode = NOT_NO;
    } else if (strcmp(command, INC) == 0) {
        opcode = INC_NO;
    } else if (strcmp(command, DEC) == 0) {
        opcode = DEC_NO;
    } else if (strcmp(command, JMP) == 0) {
        opcode = JMP_NO;
    } else if (strcmp(command, BNE) == 0) {
        opcode = BNE_NO;
    } else if (strcmp(command, RED) == 0) {
        opcode = RED_NO;
    } else if (strcmp(command, PRN) == 0) {
        opcode = PRN_NO;
    } else if (strcmp(command, JSR) == 0) {
        opcode = JSR_NO;
    } else if (strcmp(command, RTS) == 0) {
        opcode = RTS_NO;
    } else if (strcmp(command, STOP) == 0) {
        opcode = STOP_NO;
    }
    return opcode;
}

void opcode_binary_to_bits(BitsCommand *pbc, int opcode_binary) {
    pbc->b11 = opcode_binary % 10;
    opcode_binary = opcode_binary / 10;

    pbc->b12 = opcode_binary % 10;
    opcode_binary = opcode_binary / 10;

    pbc->b13 = opcode_binary % 10;
    opcode_binary = opcode_binary / 10;

    pbc->b14 = opcode_binary;
}


void assign_command_bits(ParsedCommand *ppc, BitsCommand *pbc) {
    int opcode;
    opcode = to_opcode(ppc->command);
    opcode = dec_to_binary(opcode);
    opcode_binary_to_bits(pbc, opcode);
}

void assign_src_arg_bits(ParsedCommand *ppc, BitsCommand *pbc) {
    switch (ppc->src_addressing_method) {
        case INSTANT_ADDRESSING_NO:
            pbc->b7 = 1;
            break;
        case DIRECT_ADDRESSING_NO:
            pbc->b8 = 1;
            break;
        case INDIRECT_REGISTER_ADDRESSING_NO:
            pbc->b9 = 1;
            break;
        case DIRECT_REGISTER_ADDRESSING_NO:
            pbc->b10 = 1;
            break;
        default:
            break;

    }
}

void assign_dst_arg_bits(ParsedCommand *ppc, BitsCommand *pbc) {
    switch (ppc->dst_addressing_method) {
        case INSTANT_ADDRESSING_NO:
            pbc->b3 = 1;
            break;
        case DIRECT_ADDRESSING_NO:
            pbc->b4 = 1;
            break;
        case INDIRECT_REGISTER_ADDRESSING_NO:
            pbc->b5 = 1;
            break;
        case DIRECT_REGISTER_ADDRESSING_NO:
            pbc->b6 = 1;
            break;
        default:
            break;

    }
}

void assign_are_bits(BitsCommand *pbc, int are) {
    switch (are) {
        case 0:
            pbc->b0 = 1;
            break;
        case 1:
            pbc->b1 = 1;
            break;
        case 2:
            pbc->b2 = 1;
            break;
        default:
            break;
    }
}

void convert_pbc_to_pchar(char *pcommand, BitsCommand *pbc) {
    pcommand[14] = pbc->b0 + '0';
    pcommand[13] = pbc->b1 + '0';
    pcommand[12] = pbc->b2 + '0';
    pcommand[11] = pbc->b3 + '0';
    pcommand[10] = pbc->b4 + '0';
    pcommand[9] = pbc->b5 + '0';
    pcommand[8] = pbc->b6 + '0';
    pcommand[7] = pbc->b7 + '0';
    pcommand[6] = pbc->b8 + '0';
    pcommand[5] = pbc->b9 + '0';
    pcommand[4] = pbc->b10 + '0';
    pcommand[3] = pbc->b11 + '0';
    pcommand[2] = pbc->b12 + '0';
    pcommand[1] = pbc->b13 + '0';
    pcommand[0] = pbc->b14 + '0';
    pcommand[15] = '\n';
}

void assign_first_command(ParsedCommand *ppc, BitsCommand *pbc, int are) {
    /**First command**/
    /**Set the command bits: 11-14**/
    assign_command_bits(ppc, pbc);

    /**Set the src arg bits: 7-10**/
    assign_src_arg_bits(ppc, pbc);

    /**Set the src arg bits: 3-6**/
    assign_dst_arg_bits(ppc, pbc);

    /**Set the src arg bits: 0-2**/
    assign_are_bits(pbc, are);
}

void assign_arg_to_bit_3_till_14(BitsCommand *pbc, int binary_arg) {
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


void assign_register_number_to_bit(BitsCommand *pbc, int binary_arg, int is_src_reg) {
    if (is_src_reg) {
        pbc->b6 = binary_arg % 10;
        binary_arg = binary_arg / 10;

        pbc->b7 = binary_arg % 10;
        binary_arg = binary_arg / 10;

        pbc->b8 = binary_arg % 10;
    } else {
        pbc->b3 = binary_arg % 10;
        binary_arg = binary_arg / 10;

        pbc->b4 = binary_arg % 10;
        binary_arg = binary_arg / 10;

        pbc->b5 = binary_arg % 10;
    }

}


void assign_instant_command(ParsedCommand *ppc, BitsCommand *pbc, int are, int is_src_arg) {
    int bin_representation_of_arg, arg_as_dec;
    char instant_arg[5];
    if (is_src_arg) {
        strcpy(instant_arg, ppc->src);
    } else {
        strcpy(instant_arg, ppc->dst);
    }
    sscanf(instant_arg, "%d", &arg_as_dec);

    bin_representation_of_arg = dec_to_binary(arg_as_dec);

    /**Set the instant arg bits: 3-14**/
    assign_arg_to_bit_3_till_14(pbc, bin_representation_of_arg);

    /**Set the src arg bits: 0-2**/
    assign_are_bits(pbc, are);
}

void assign_direct_register_value_command(ParsedCommand *ppc, BitsCommand *pbc, int are, int is_src_arg) {
    int bin_representation_of_arg, arg_as_dec;
    char direct_register_arg[5];
    if (is_src_arg) {
        strcpy(direct_register_arg, ppc->src);
    } else {
        strcpy(direct_register_arg, ppc->dst);
    }

    arg_as_dec = atoi(&direct_register_arg[1]);

    bin_representation_of_arg = dec_to_binary(arg_as_dec);

    /**Set the instant arg bits: 3-14**/
    assign_arg_to_bit_3_till_14(pbc, bin_representation_of_arg);

    /**Set the src arg bits: 0-2**/
    assign_are_bits(pbc, are);
}


void assign_direct_and_indirect_register_number_command(ParsedCommand *ppc, BitsCommand *pbc, int are, int is_src_arg) {
    int bin_representation_of_arg, arg_as_dec;
    char register_number;
    char direct_register_arg[5];
    if (is_src_arg) {
        strcpy(direct_register_arg, ppc->src);
    } else {
        strcpy(direct_register_arg, ppc->dst);
    }
    if (strstr(direct_register_arg, "r")) {
        register_number = direct_register_arg[1];
    }
    arg_as_dec = atoi(&register_number);

    bin_representation_of_arg = dec_to_binary(arg_as_dec);

    /**Set the direct register number arg bits: 3-5 or 6-8**/
    assign_register_number_to_bit(pbc, bin_representation_of_arg, is_src_arg);

    /**Set the src arg bits: 0-2**/
    assign_are_bits(pbc, are);
}

