// COMP1521 20T3 Assignment 1: mips_sim -- a MIPS simulator
// starting point code v0.1 - 13/10/20


// Written by Nicholas Liu (z5310207) 19th Oct ~ 


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 256
#define INSTRUCTIONS_GROW 64


// ADD YOUR #defines HERE


void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode);
char *process_arguments(int argc, char *argv[], int *trace_mode);
uint32_t *read_instructions(char *filename, int *n_instructions_p);
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions);


// ADD YOUR FUNCTION PROTOTYPES HERE
int interpret_hex(uint32_t instr, int *var, int pc, int *exitPointer);
void mips_add_function(int *var, int d, int s, int t);
void mips_sub_function(int *var, int d, int s, int t);
void mips_slt_function(int *var, int d, int s, int t);
void mips_mul_function(int *var, int d, int s, int t);
int mips_beq_function(int *var, int pc, int s, int t, int16_t i);
int mips_bne_function(int *var, int pc, int s, int t, int16_t i);
void mips_addi_function(int *var, int t, int s, int16_t i);
void mips_ori_function(int *var, int t, int s, int16_t i);
void mips_lui_function(int *var, int t, int16_t i);
void syscall_function(int *var, int *exitPointer);

int interpret_hex_dashR(uint32_t instr, int *var, int pc, int *exitPointer);
void mips_add_function_dashR(int *var, int d, int s, int t);
void mips_sub_function_dashR(int *var, int d, int s, int t);
void mips_slt_function_dashR(int *var, int d, int s, int t);
void mips_mul_function_dashR(int *var, int d, int s, int t);
int mips_beq_function_dashR(int *var, int pc, int s, int t, int16_t i);
int mips_bne_function_dashR(int *var, int pc, int s, int t, int16_t i);
void mips_addi_function_dashR(int *var, int t, int s, int16_t i);
void mips_ori_function_dashR(int *var, int t, int s, int16_t i);
void mips_lui_function_dashR(int *var, int t, int16_t i);
void syscall_function_dashR(int *var, int *exitPointer);

int hex_add_condition(int32_t hexCode);
int hex_sub_condition(int32_t hexCode);
int hex_slt_condition(int32_t hexCode);
int hex_mul_condition(int32_t hexCode);
int hex_beq_condition(int32_t hexCode);
int hex_bne_condition(int32_t hexCode);
int hex_addi_condition(int32_t hexCode);
int hex_ori_condition(int32_t hexCode);
int hex_lui_condition(int32_t hexCode);
int hex_syscall_condition(int32_t hexCode);

// YOU SHOULD NOT NEED TO CHANGE MAIN

int main(int argc, char *argv[]) {
    int trace_mode;
    char *filename = process_arguments(argc, argv, &trace_mode);

    int n_instructions;
    uint32_t *instructions = read_instructions(filename, &n_instructions);

    execute_instructions(n_instructions, instructions, trace_mode);

    free(instructions);
    return 0;
}


// simulate execution of  instruction codes in  instructions array
// output from syscall instruction & any error messages are printed
//
// if trace_mode != 0:
//     information is printed about each instruction as it executed
//
// execution stops if it reaches the end of the array

void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode) {
    // Start at branch 0
    int pc = 0;

    // Register numbers act as indexes to var array pointer
    int *var = malloc(32 * sizeof(int));
    var[0] = 0;       // $0 is hard-wired to 0

    // Program ends when exit == 1
    int exit = 0;
    int *exitPointer = &exit;

    // Loop through the branches until you exhaust out of instructions
    while (pc < n_instructions) {
        if (trace_mode) {
            // If trace mode is on
            printf("%d: 0x%08X ", pc, instructions[pc]);
            pc = interpret_hex(instructions[pc], var, pc, exitPointer);
        } else {
            // If trace mode is off
            pc = interpret_hex_dashR(instructions[pc], var, pc, exitPointer);
        }
        if (pc < -1) {
            // If pc becomes negative (i.e. illegal branching)
            //* pc can be -1 because the interpret_hex functions
            //* returns one less the value of the new branch
            //* if the branch changes (i.e branch 0 is a valid branch)
            printf(
                "Illegal branch to address before instructions: PC = %d\n", 
                                                                   pc + 1
            );
            exit = 1; // thus program is to exit 
        }
        if (exit) {
            // If exit == 1, then end program
            free(var);
            return;
        }
        
        var[0] = 0;   // $0 is hard-wired to 0
        pc++;         // onto the next branch !!
    }
}

// ADD YOUR FUNCTIONS HERE

//* This first set of functions are specifically when
//* trace_mode is on

// Function to interpret the hex command
//! NOTE: instr refers to instructions[n_instructions]
// This function returns one less of the value of the new pc
// if the branch changes
// Otherwise it returns the current pc
int interpret_hex(uint32_t instr, int *var, int pc, int *exitPointer) {
    // First identify the d, s, t and I variables
    //! Note: On the spec it's 'I' but I typed it in
    //! lower-case 'i' as CAPS should be reserved 
    //! for #defines
    int d = (instr >> 11) & 0x1F;
    int s = (instr >> 21) & 0x1F;
    int t = (instr >> 16) & 0x1F;
    int16_t i = instr & 0xFFFF;
    if (hex_add_condition(instr)) {
        // If the command is to add
        mips_add_function(var, d, s, t);
          
    } else if (hex_sub_condition(instr)) {
        // If the command is to sub
        mips_sub_function(var, d, s, t);
        
    } else if (hex_slt_condition(instr)) {
        // If the command is to slt
        mips_slt_function(var, d, s, t);
        
    } else if (hex_mul_condition(instr)) {
        // If the command is to mul
        mips_mul_function(var, d, s, t);
        
    } else if (hex_beq_condition(instr)) {
        // If the command is to beq
        return mips_beq_function(var, pc, s, t, i);
        
    } else if (hex_bne_condition(instr)) {
        // If the command is to bne
        return mips_bne_function(var, pc, s, t, i);

    } else if (hex_addi_condition(instr)) {
        // If the command is to addi
        mips_addi_function(var, t, s, i);

    } else if (hex_ori_condition(instr)) {
        // If the command is to ori
        mips_ori_function(var, t, s, i);

    } else if (hex_lui_condition(instr)) {
        // If the command is to ori
        mips_lui_function(var, t, i);

    } else if (hex_syscall_condition(instr)) {
        // If the command is to syscall
        syscall_function(var, exitPointer);
        
    } else {
        // If the command is none of the above
        // i.e. invalid command
        printf("invalid instruction code\n");
        *exitPointer = 1;
    }

    return pc;
}

// All these functions print out the respective mips fns
// and apply it to the var variables
void mips_add_function(int *var, int d, int s, int t) {
    printf("add  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] + var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

void mips_sub_function(int *var, int d, int s, int t) {
    printf("sub  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] - var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

void mips_slt_function(int *var, int d, int s, int t) {
    printf("slt  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] < var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

void mips_mul_function(int *var, int d, int s, int t) {
    printf("mul  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] * var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

int mips_beq_function(int *var, int pc, int s, int t, int16_t i) {
    printf("beq  $%d, $%d, %d\n", s, t, i);
    if (var[s] == var[t]) {
        printf(">>> branch taken to PC = %d\n", pc + i);
        return pc + i - 1;
    } else {
        printf(">>> branch not taken\n");
    }

    return pc;
}

int mips_bne_function(int *var, int pc, int s, int t, int16_t i) {
    printf("bne  $%d, $%d, %d\n", s, t, i);
    if (var[s] != var[t]) {
        printf(">>> branch taken to PC = %d\n", pc + i);
        return pc + i - 1;
    } else {
        printf(">>> branch not taken\n");
    }

    return pc;
}

void mips_addi_function(int *var, int t, int s, int16_t i) {
    printf("addi $%d, $%d, %d\n", t, s, i);
    var[t] = var[s] + i;
    printf(">>> $%d = %d\n", t, var[t]);
}

void mips_ori_function(int *var, int t, int s, int16_t i) {
    printf("ori  $%d, $%d, %d\n", t, s, i);
    var[t] = var[s] | i;
    printf(">>> $%d = %d\n", t, var[t]);
}

void mips_lui_function(int *var, int t, int16_t i) {
    printf("lui  $%d, %d\n", t, i);
    var[t] = i << 16;
    printf(">>> $%d = %d\n", t, var[t]);
}

void syscall_function(int *var, int *exitPointer) {
    printf("syscall\n");
    printf(">>> syscall %d\n", var[2]);
    if (var[2] == 1) {
        printf("<<< %d\n", var[4]);
    } else if (var[2] == 10) {
        *exitPointer = 1;
    } else if (var[2] == 11) {
        printf("<<< ");
        putchar(var[4]);
        printf("\n");
    } else {
        printf("Unknown system call: %d\n", var[2]);
        *exitPointer = 1;
    }
}

//* This next set of functions are specifically when
//* trace_mode is off

// Function to interpret the hex command
//! NOTE: instr refers to instructions[n_instructions]
// This function returns one less of the value of the new pc
// if the branch changes
// Otherwise it returns the current pc
int interpret_hex_dashR(uint32_t instr, int *var, int pc, int *exitPointer) {
    // First identify the d, s, t and I variables
    //! Note: On the spec it's 'I' but I typed it in
    //! lower-case 'i' as CAPS should be reserved 
    //! for #defines
    int d = (instr >> 11) & 0x1F;
    int s = (instr >> 21) & 0x1F;
    int t = (instr >> 16) & 0x1F;
    int16_t i = instr & 0xFFFF;
    if (hex_add_condition(instr)) {
        // If the command is to add
        mips_add_function_dashR(var, d, s, t);
          
    } else if (hex_sub_condition(instr)) {
        // If the command is to sub
        mips_sub_function_dashR(var, d, s, t);
        
    } else if (hex_slt_condition(instr)) {
        // If the command is to slt
        mips_slt_function_dashR(var, d, s, t);
        
    } else if (hex_mul_condition(instr)) {
        // If the command is to mul
        mips_mul_function_dashR(var, d, s, t);
        
    } else if (hex_beq_condition(instr)) {
        // If the command is to beq
        return mips_beq_function_dashR(var, pc, s, t, i);
        
    } else if (hex_bne_condition(instr)) {
        // If the command is to bne
        return mips_bne_function_dashR(var, pc, s, t, i);

    } else if (hex_addi_condition(instr)) {
        // If the command is to addi
        mips_addi_function_dashR(var, t, s, i);

    } else if (hex_ori_condition(instr)) {
        // If the command is to ori
        mips_ori_function_dashR(var, t, s, i);

    } else if (hex_lui_condition(instr)) {
        // If the command is to ori
        mips_lui_function_dashR(var, t, i);

    } else if (hex_syscall_condition(instr)) {
        // If the command is to syscall
        syscall_function_dashR(var, exitPointer);

    } else {
        // If the command is none of the above
        // i.e. invalid command
        printf("invalid instruction code\n");
        *exitPointer = 1;
    }

    return pc;
}

// All these functions apply respective mips fns
// to the var variables
void mips_add_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] + var[t];
}

void mips_sub_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] - var[t];
}

void mips_slt_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] < var[t];
}

void mips_mul_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] * var[t];
}

int mips_beq_function_dashR(int *var, int pc, int s, int t, int16_t i) {
    if (var[s] == var[t]) {
        return pc + i - 1;
    }

    return pc;
}

int mips_bne_function_dashR(int *var, int pc, int s, int t, int16_t i) {
    if (var[s] != var[t]) {
        return pc + i - 1;
    }

    return pc;
}

void mips_addi_function_dashR(int *var, int t, int s, int16_t i) {
    var[t] = var[s] + i;
}

void mips_ori_function_dashR(int *var, int t, int s, int16_t i) {
    var[t] = var[s] | i;
}

void mips_lui_function_dashR(int *var, int t, int16_t i) {
    var[t] = i << 16;
}

void syscall_function_dashR(int *var, int *exitPointer) {
    if (var[2] == 1) {
        printf("%d", var[4]);
    } else if (var[2] == 10) {
        *exitPointer = 1;
    } else if (var[2] == 11) {
        putchar(var[4]);
    } else {
        printf("Unknown system call: %d\n", var[2]);
        *exitPointer = 1;
    }
}

//* This last set of functions return 1 if the condition is true,
//* or 0 if the condition is false.
//* These conditions represent what hex command is being called

int hex_add_condition(int32_t hexCode) {
    return !(hexCode >> 26) && ((hexCode & 0x7FF) == 0x20);
}

int hex_sub_condition(int32_t hexCode) {
    return !(hexCode >> 26) && ((hexCode & 0x7FF) == 0x22);
}

int hex_slt_condition(int32_t hexCode) {
    return !(hexCode >> 26) && ((hexCode & 0x7FF) == 0x2A);
}

int hex_mul_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 0x1C && ((hexCode & 0x7FF) == 2);
}

int hex_beq_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 4;
}

int hex_bne_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 5;
}

int hex_addi_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 8;
}

int hex_ori_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 0xD;
}

int hex_lui_condition(int32_t hexCode) {
    return ((hexCode >> 21) & 0x1FF) == 0x1E0;
}

int hex_syscall_condition(int32_t hexCode) {
    return hexCode == 0b1100;
}

// YOU DO NOT NEED TO CHANGE CODE BELOW HERE


// check_arguments is given command-line arguments
// it sets *trace_mode to 0 if -r is specified
//          *trace_mode is set to 1 otherwise
// the filename specified in command-line arguments is returned

char *process_arguments(int argc, char *argv[], int *trace_mode) {
    if (
        argc < 2 ||
        argc > 3 ||
        (argc == 2 && strcmp(argv[1], "-r") == 0) ||
        (argc == 3 && strcmp(argv[1], "-r") != 0)) {
        fprintf(stderr, "Usage: %s [-r] <file>\n", argv[0]);
        exit(1);
    }
    *trace_mode = (argc == 2);
    return argv[argc - 1];
}


// read hexadecimal numbers from filename one per line
// numbers are return in a malloc'ed array
// *n_instructions is set to size of the array

uint32_t *read_instructions(char *filename, int *n_instructions_p) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "%s: '%s'\n", strerror(errno), filename);
        exit(1);
    }

    uint32_t *instructions = NULL;
    int n_instructions = 0;
    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, sizeof line, f) != NULL) {

        // grow instructions array in steps of INSTRUCTIONS_GROW elements
        if (n_instructions % INSTRUCTIONS_GROW == 0) {
            instructions = instructions_realloc(instructions, n_instructions + INSTRUCTIONS_GROW);
        }

        char *endptr;
        instructions[n_instructions] = strtol(line, &endptr, 16);
        if (*endptr != '\n' && *endptr != '\r' && *endptr != '\0') {
            fprintf(stderr, "%s:line %d: invalid hexadecimal number: %s",
                    filename, n_instructions + 1, line);
            exit(1);
        }
        n_instructions++;
    }
    fclose(f);
    *n_instructions_p = n_instructions;
    // shrink instructions array to correct size
    instructions = instructions_realloc(instructions, n_instructions);
    return instructions;
}


// instructions_realloc is wrapper for realloc
// it calls realloc to grow/shrink the instructions array
// to the speicfied size
// it exits if realloc fails
// otherwise it returns the new instructions array
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions) {
    instructions = realloc(instructions, n_instructions * sizeof *instructions);
    if (instructions == NULL) {
        fprintf(stderr, "out of memory");
        exit(1);
    }
    return instructions;
}