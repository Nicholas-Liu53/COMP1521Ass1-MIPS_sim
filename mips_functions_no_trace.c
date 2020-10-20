// mips_functions_no_trace.c c file
// Part of 20T3 COMP1521 Assignment 1: mips_sim, MIPS simulator
// Written by Nicholas Liu (z5310207) 20th October 2020

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

//* This set of functions are specifically when
//* trace_mode is off
// All these functions print out the respective mips fns
// and apply it to the var variables

// The mips instruction to add
void mips_add_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] + var[t];
}

// The mips instruction to sub
void mips_sub_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] - var[t];
}

// The mips instruction to slt
void mips_slt_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] < var[t];
}

// The mips instruction to mul
void mips_mul_function_dashR(int *var, int d, int s, int t) {
    var[d] = var[s] * var[t];
}

// The mips instruction to beq
int mips_beq_function_dashR(int *var, int pc, int s, int t, int16_t i) {
    if (var[s] == var[t]) {
        return pc + i - 1;
    }

    return pc;
}

// The mips instruction to bne
int mips_bne_function_dashR(int *var, int pc, int s, int t, int16_t i) {
    if (var[s] != var[t]) {
        return pc + i - 1;
    }

    return pc;
}

// The mips instruction to addi
void mips_addi_function_dashR(int *var, int t, int s, int16_t i) {
    var[t] = var[s] + i;
}

// The mips instruction to ori
void mips_ori_function_dashR(int *var, int t, int s, int16_t i) {
    var[t] = var[s] | i;
}

// The mips instruction to lui
void mips_lui_function_dashR(int *var, int t, int16_t i) {
    var[t] = i << 16;
}

// The mips instruction to syscall
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