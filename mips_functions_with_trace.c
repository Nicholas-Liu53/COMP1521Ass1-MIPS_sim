// mips_functions_with_trace.c c file
// Part of 20T3 COMP1521 Assignment 1: mips_sim, MIPS simulator
// Written by Nicholas Liu (z5310207) 20th October 2020

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

//* This set of functions are specifically when
//* trace_mode is on
// All these functions print out the respective mips fns
// and apply it to the var variables

// The mips instruction to add
void mips_add_function(int *var, int d, int s, int t) {
    printf("add  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] + var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

// The mips instruction to sub
void mips_sub_function(int *var, int d, int s, int t) {
    printf("sub  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] - var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

// The mips instruction to slt
void mips_slt_function(int *var, int d, int s, int t) {
    printf("slt  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] < var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

// The mips instruction to mul
void mips_mul_function(int *var, int d, int s, int t) {
    printf("mul  $%d, $%d, $%d\n", d, s, t);
    var[d] = var[s] * var[t];
    printf(">>> $%d = %d\n", d, var[d]);
}

// The mips instruction to beq
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

// The mips instruction to bne
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

// The mips instruction to addi
void mips_addi_function(int *var, int t, int s, int16_t i) {
    printf("addi $%d, $%d, %d\n", t, s, i);
    var[t] = var[s] + i;
    printf(">>> $%d = %d\n", t, var[t]);
}

// The mips instruction to ori
void mips_ori_function(int *var, int t, int s, int16_t i) {
    printf("ori  $%d, $%d, %d\n", t, s, i);
    var[t] = var[s] | i;
    printf(">>> $%d = %d\n", t, var[t]);
}

// The mips instruction to lui
void mips_lui_function(int *var, int t, int16_t i) {
    printf("lui  $%d, %d\n", t, i);
    var[t] = i << 16;
    printf(">>> $%d = %d\n", t, var[t]);
}

// The mips instruction to syscall
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