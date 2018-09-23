.intel_syntax noprefix

.section .text

.globl _start

.extern main

_start:
    add rsp, 8 /* System V ABI - call must be executed with 16B aligned RSP */
    call main
    sub rsp, 8
    hlt
