// hex_conditions.c c file
// Part of 20T3 COMP1521 Assignment 1: mips_sim, MIPS simulator
// Written by Nicholas Liu (z5310207) 20th October 2020

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

//* This set of functions return 1 if the condition is true,
//* or 0 if the condition is false.
//* These conditions represent what hex command is being called

// If hex code is calling "add" instruction
int hex_add_condition(int32_t hexCode) {
    return !(hexCode >> 26) && ((hexCode & 0x7FF) == 0x20);
}

// If hex code is calling "sub" instruction
int hex_sub_condition(int32_t hexCode) {
    return !(hexCode >> 26) && ((hexCode & 0x7FF) == 0x22);
}

// If hex code is calling "slt" instruction
int hex_slt_condition(int32_t hexCode) {
    return !(hexCode >> 26) && ((hexCode & 0x7FF) == 0x2A);
}

// If hex code is calling "mul" instruction
int hex_mul_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 0x1C && ((hexCode & 0x7FF) == 2);
}

// If hex code is calling "beq" instruction
int hex_beq_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 4;
}

// If hex code is calling "bne" instruction
int hex_bne_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 5;
}

// If hex code is calling "addi" instruction
int hex_addi_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 8;
}

// If hex code is calling "ori" instruction
int hex_ori_condition(int32_t hexCode) {
    return ((hexCode >> 26) & 0x3F) == 0xD;
}

// If hex code is calling "lui" instruction
int hex_lui_condition(int32_t hexCode) {
    return ((hexCode >> 21) & 0x1FF) == 0x1E0;
}

// If hex code is calling "syscall" instruction
int hex_syscall_condition(int32_t hexCode) {
    return hexCode == 0b1100;
}