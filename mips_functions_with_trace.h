// mips_functions_with_trace.h header file
// Part of 20T3 COMP1521 Assignment 1: mips_sim, MIPS simulator
// Written by Nicholas Liu (z5310207) 20th October 2020

//* This set of functions are specifically when
//* trace_mode is on
// All these functions print out the respective mips fns
// and apply it to the var variables

// The mips instruction to add
void mips_add_function(int *var, int d, int s, int t);

// The mips instruction to sub
void mips_sub_function(int *var, int d, int s, int t);

// The mips instruction to slt
void mips_slt_function(int *var, int d, int s, int t);

// The mips instruction to mul
void mips_mul_function(int *var, int d, int s, int t);

// The mips instruction to beq
int mips_beq_function(int *var, int pc, int s, int t, int16_t i);

// The mips instruction to bne
int mips_bne_function(int *var, int pc, int s, int t, int16_t i);

// The mips instruction to addi
void mips_addi_function(int *var, int t, int s, int16_t i);

// The mips instruction to ori
void mips_ori_function(int *var, int t, int s, int16_t i);

// The mips instruction to lui
void mips_lui_function(int *var, int t, int16_t i);

// The mips instruction to syscall
void syscall_function(int *var, int *exitPointer);