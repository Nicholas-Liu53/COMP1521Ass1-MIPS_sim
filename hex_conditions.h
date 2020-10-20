// hex_conditions.h header file
// Part of 20T3 COMP1521 Assignment 1: mips_sim, MIPS simulator
// Written by Nicholas Liu (z5310207) 20th October 2020

//* This set of functions return 1 if the condition is true,
//* or 0 if the condition is false.
//* These conditions represent what hex command is being called

// If hex code is calling "add" instruction
int hex_add_condition(int32_t hexCode);

// If hex code is calling "sub" instruction
int hex_sub_condition(int32_t hexCode);

// If hex code is calling "slt" instruction
int hex_slt_condition(int32_t hexCode);

// If hex code is calling "mul" instruction
int hex_mul_condition(int32_t hexCode);

// If hex code is calling "beq" instruction
int hex_beq_condition(int32_t hexCode);

// If hex code is calling "bne" instruction
int hex_bne_condition(int32_t hexCode);

// If hex code is calling "addi" instruction
int hex_addi_condition(int32_t hexCode);

// If hex code is calling "ori" instruction
int hex_ori_condition(int32_t hexCode);

// If hex code is calling "lui" instruction
int hex_lui_condition(int32_t hexCode);

// If hex code is calling "syscall" instruction
int hex_syscall_condition(int32_t hexCode);