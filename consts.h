/* Input */
#define MAX_LINE 80
#define MAX_ARG_SIZE 5
#define MAX_INSTRUCTION_LEN 6

/* Assembly language */
#define R1 "r1"
#define R2 "r2"
#define R3 "r3"
#define R4 "r4"
#define R5 "r5"
#define R6 "r6"
#define R7 "r7"
#define MOV "mov"
#define MOV_NO 0
#define CMP "cmp"
#define CMP_NO 1
#define ADD "add"
#define ADD_NO 2
#define SUB "sub"
#define SUB_NO 3
#define LEA "lea"
#define LEA_NO 4
#define CLR "clr"
#define CLR_NO 5
#define NOT "not"
#define NOT_NO 6
#define INC "inc"
#define INC_NO 7
#define DEC "dec"
#define DEC_NO 8
#define JMP "jmp"
#define JMP_NO 9
#define BNE "bne"
#define BNE_NO 10
#define RED "red"
#define RED_NO 11
#define PRN "prn"
#define PRN_NO 12
#define JSR "jsr"
#define JSR_NO 13
#define RTS "rts"
#define RTS_NO 14
#define STOP "stop"
#define STOP_NO 15
#define UNKNOWN_COMMAND_NO -1

/* Addressing method */
#define INSTANT_ADDRESSING_NO 0
#define DIRECT_ADDRESSING_NO 1
#define INDIRECT_REGISTER_ADDRESSING_NO 2
#define DIRECT_REGISTER_ADDRESSING_NO 3

/* Instructions */
#define DATA "data"
#define DATA_NO 0
#define STRING "string"
#define STRING_NO 1
#define ENTRY "entry"
#define ENTRY_NO 2
#define EXTERN "extern"
#define EXTERN_NO 3


/*General*/
#define TRUE (1)
#define FALSE (0)
#define MAX_NUM_OF_TRANSLATION_COMMANDS 3
#define TERMINATE "terminate"


/* Output */
#define BIN_FILENAME "../binary_output.txt"
