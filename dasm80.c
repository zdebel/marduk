#include <stdint.h>
#include "z80.h"

#ifdef DEBUG
typedef enum
{
 NOTHING,
 ARG8,
 ARG16,
 ARGREL
} zvar;

typedef struct
{
 char *disp;
 zvar fmt;
} zop;

/* from z80.c */
static inline uint8_t get_f(z80* const z) 
{
 uint8_t val = 0;
 val |= z->cf << 0;
 val |= z->nf << 1;
 val |= z->pf << 2;
 val |= z->xf << 3;
 val |= z->hf << 4;
 val |= z->yf << 5;
 val |= z->zf << 6;
 val |= z->sf << 7;
 return val;
}

/*
 * Every entry should be padded out to the length of the opcode; after that
 * does not matter.
 */
zop tabmain[]={
 "NOP   ", NOTHING,
 "LD    BC, $%04X", ARG16,
 "LD    (BC), A", NOTHING,
 "INC   BC", NOTHING,
 "INC   B", NOTHING,
 "DEC   B", NOTHING,
 "LD    B, $%02X", ARG8,
 "RLCA  ", NOTHING,
 "EX    AF, AF'", NOTHING,
 "ADD   HL, BC", NOTHING,
 "LD    A, (BC)", NOTHING,
 "DEC   BC", NOTHING,
 "INC   C", NOTHING,
 "DEC   C", NOTHING,
 "LD    C, $%02X", ARG8,
 "RRCA  ", NOTHING,
 "DJNZ  $%04X", ARGREL,
 "LD    DE, $%04X", ARG16,
 "LD    (DE), A", NOTHING,
 "INC   DE", NOTHING,
 "INC   D", NOTHING,
 "DEC   D", NOTHING,
 "LD    D, $%02X", ARG8,
 "RLA   ", NOTHING,
 "JR    $%04X", ARGREL,
 "ADD   HL, DE", NOTHING,
 "LD    A, (DE)", NOTHING,
 "DEC   DE", NOTHING,
 "INC   E", NOTHING,
 "DEC   E", NOTHING,
 "LD    E, $%02X", ARG8,
 "RRA   ", NOTHING,
 "JR    NZ, $%04X", ARGREL,
 "LD    HL, $%04X", ARG16,
 "LD    ($%04X), HL", ARG16,
 "INC   HL", NOTHING,
 "INC   H", NOTHING,
 "DEC   H", NOTHING,
 "LD    H, $%02X", ARG8,
 "DAA   ", NOTHING,
 "JR    Z, $%04X", ARGREL,
 "ADD   HL, HL", NOTHING,
 "LD    HL, ($%04X)", ARG16,
 "DEC   HL", NOTHING,
 "INC   L", NOTHING,
 "DEC   L", NOTHING,
 "LD    L, $%02X", ARG8,
 "CPL   ", NOTHING,
 "JR    NC, $%04X", ARGREL,
 "LD    SP, $%04X", ARG16,
 "LD    ($%04X), A", ARG16,
 "INC   SP", NOTHING,
 "INC   (HL)", NOTHING,
 "DEC   (HL)", NOTHING,
 "LD    (HL), $%02X", ARG8,
 "SCF   ", NOTHING,
 "JR    C, $%04X", ARGREL,
 "ADD   HL, SP", NOTHING,
 "LD    A, ($%04X)", ARG16,
 "DEC   SP", NOTHING,
 "INC   A", NOTHING,
 "DEC   A", NOTHING,
 "LD    A, $%02X", ARG8,
 "CCF   ", NOTHING,
 "LD    B, B", NOTHING,
 "LD    B, C", NOTHING,
 "LD    B, D", NOTHING,
 "LD    B, E", NOTHING,
 "LD    B, H", NOTHING,
 "LD    B, L", NOTHING,
 "LD    B, (HL)", NOTHING,
 "LD    B, A", NOTHING,
 "LD    C, B", NOTHING,
 "LD    C, C", NOTHING,
 "LD    C, D", NOTHING,
 "LD    C, E", NOTHING,
 "LD    C, H", NOTHING,
 "LD    C, L", NOTHING,
 "LD    C, (HL)", NOTHING,
 "LD    C, A", NOTHING,
 "LD    D, B", NOTHING,
 "LD    D, C", NOTHING,
 "LD    D, D", NOTHING,
 "LD    D, E", NOTHING,
 "LD    D, H", NOTHING,
 "LD    D, L", NOTHING,
 "LD    D, (HL)", NOTHING,
 "LD    D, A", NOTHING,
 "LD    E, B", NOTHING,
 "LD    E, C", NOTHING,
 "LD    E, D", NOTHING,
 "LD    E, E", NOTHING,
 "LD    E, H", NOTHING,
 "LD    E, L", NOTHING,
 "LD    E, (HL)", NOTHING,
 "LD    E, A", NOTHING,
 "LD    H, B", NOTHING,
 "LD    H, C", NOTHING,
 "LD    H, D", NOTHING,
 "LD    H, E", NOTHING,
 "LD    H, H", NOTHING,
 "LD    H, L", NOTHING,
 "LD    H, (HL)", NOTHING,
 "LD    H, A", NOTHING,
 "LD    L, B", NOTHING,
 "LD    L, C", NOTHING,
 "LD    L, D", NOTHING,
 "LD    L, E", NOTHING,
 "LD    L, H", NOTHING,
 "LD    L, L", NOTHING,
 "LD    L, (HL)", NOTHING,
 "LD    L, A", NOTHING,
 "LD    (HL), B", NOTHING,
 "LD    (HL), C", NOTHING,
 "LD    (HL), D", NOTHING,
 "LD    (HL), E", NOTHING,
 "LD    (HL), H", NOTHING,
 "LD    (HL), L", NOTHING,
 "HALT  ", NOTHING,
 "LD    (HL), A", NOTHING,
 "LD    A, B", NOTHING,
 "LD    A, C", NOTHING,
 "LD    A, D", NOTHING,
 "LD    A, E", NOTHING,
 "LD    A, H", NOTHING,
 "LD    A, L", NOTHING,
 "LD    A, (HL)", NOTHING,
 "LD    A, A", NOTHING,
 "ADD   A, B", NOTHING,
 "ADD   A, C", NOTHING,
 "ADD   A, D", NOTHING,
 "ADD   A, E", NOTHING,
 "ADD   A, H", NOTHING,
 "ADD   A, L", NOTHING,
 "ADD   A, (HL)", NOTHING,
 "ADD   A, A", NOTHING,
 "ADC   A, B", NOTHING,
 "ADC   A, C", NOTHING,
 "ADC   A, D", NOTHING,
 "ADC   A, E", NOTHING,
 "ADC   A, H", NOTHING,
 "ADC   A, L", NOTHING,
 "ADC   A, (HL)", NOTHING,
 "ADC   A, A", NOTHING,
 "SUB   B", NOTHING,
 "SUB   C", NOTHING,
 "SUB   D", NOTHING,
 "SUB   E", NOTHING,
 "SUB   H", NOTHING,
 "SUB   L", NOTHING,
 "SUB   (HL)", NOTHING,
 "SUB   A", NOTHING,
 "SBC   A, B", NOTHING,
 "SBC   A, C", NOTHING,
 "SBC   A, D", NOTHING,
 "SBC   A, E", NOTHING,
 "SBC   A, H", NOTHING,
 "SBC   A, L", NOTHING,
 "SBC   A, (HL)", NOTHING,
 "SBC   A, A", NOTHING,
 "AND   B", NOTHING,
 "AND   C", NOTHING,
 "AND   D", NOTHING,
 "AND   E", NOTHING,
 "AND   H", NOTHING,
 "AND   L", NOTHING,
 "AND   (HL)", NOTHING,
 "AND   A", NOTHING,
 "XOR   B", NOTHING,
 "XOR   C", NOTHING,
 "XOR   D", NOTHING,
 "XOR   E", NOTHING,
 "XOR   H", NOTHING,
 "XOR   L", NOTHING,
 "XOR   (HL)", NOTHING,
 "XOR   A", NOTHING,
 "OR    B", NOTHING,
 "OR    C", NOTHING,
 "OR    D", NOTHING,
 "OR    E", NOTHING,
 "OR    H", NOTHING,
 "OR    L", NOTHING,
 "OR    (HL)", NOTHING,
 "OR    A", NOTHING,
 "CP    B", NOTHING,
 "CP    C", NOTHING,
 "CP    D", NOTHING,
 "CP    E", NOTHING,
 "CP    H", NOTHING,
 "CP    L", NOTHING,
 "CP    (HL)", NOTHING,
 "CP    A", NOTHING,
 "RETNZ ", NOTHING,
 "POP   BC", NOTHING,
 "JP    NZ, $%04X", ARG16,
 "JP    $%04X", ARG16,
 "CALL  NZ, $%04X", ARG16,
 "PUSH  BC", NOTHING,
 "ADD   A, $%02X", ARG8,
 "RST   $00", NOTHING,
 "RETZ  ", NOTHING,
 "RET   ", NOTHING,
 "JP    Z, $%04X", ARG16,
 "", NOTHING,
 "CALL  Z, $%04X", ARG16,
 "CALL  $%04X", ARG16,
 "ADC   A, $%02X", ARG8,
 "RST   $08", NOTHING,
 "RET   NC", NOTHING,
 "POP   DE", NOTHING,
 "JP    NC, $%04X", ARG16,
 "OUT   ($%02X), A", ARG8,
 "CALL  NC, $%04X", ARG16,
 "PUSH  DE", NOTHING,
 "SUB   $%02X", ARG8,
 "RST   $10", NOTHING,
 "RET   C", NOTHING,
 "EXX   ", NOTHING,
 "JP    C, $%04X", ARG16,
 "IN    A, ($%02X)", ARG8,
 "CALL  C, $%04X", ARG16,
 "", NOTHING,
 "SBC   A, $%02X", ARG8,
 "RST   $18", NOTHING,
 "RET   PO", NOTHING,
 "POP   HL", NOTHING,
 "JP    PO, $%04X", ARG16,
 "EX    (SP), HL", NOTHING,
 "CALL  PO, $%04X", ARG16,
 "PUSH  HL", NOTHING,
 "AND   $%02X", ARG8,
 "RST   $20", NOTHING,
 "RET   PE", NOTHING,
 "JP    (HL)", NOTHING,
 "JP    PE, $%04X", ARG16,
 "EX    DE, HL", NOTHING,
 "CALL  PE, $%04X", ARG16,
 "", NOTHING,
 "XOR   $%02X", ARG8,
 "RST   $28", NOTHING,
 "RET   P", NOTHING,
 "POP   AF", NOTHING,
 "JP    P, $%04X", ARG16,
 "DI    ",  NOTHING,
 "CALL  P, $%04X", ARG16,
 "PUSH  AF", NOTHING,
 "OR    $%02X", ARG8,
 "RST   $30", NOTHING,
 "RET   M", NOTHING,
 "LD    SP, HL", NOTHING,
 "JP    M, $%04X", ARG16,
 "EI    ",  NOTHING,
 "CALL  M, $%04X", ARG16,
 "", NOTHING,
 "CP    $%02X", ARG8,
 "RST   $38", NOTHING
},tabcb[]={
 "RLC   B", NOTHING,
 "RLC   C", NOTHING,
 "RLC   D", NOTHING,
 "RLC   E", NOTHING,
 "RLC   H", NOTHING,
 "RLC   L", NOTHING,
 "RLC   (HL)", NOTHING,
 "RLC   A", NOTHING,
 "RRC   B", NOTHING,
 "RRC   C", NOTHING,
 "RRC   D", NOTHING,
 "RRC   E", NOTHING,
 "RRC   H", NOTHING,
 "RRC   L", NOTHING,
 "RRC   (HL)", NOTHING,
 "RRC   A", NOTHING,
 "RL    B", NOTHING,
 "RL    C", NOTHING,
 "RL    D", NOTHING,
 "RL    E", NOTHING,
 "RL    H", NOTHING,
 "RL    L", NOTHING,
 "RL    (HL)", NOTHING,
 "RL    A", NOTHING,
 "RR    B", NOTHING,
 "RR    C", NOTHING,
 "RR    D", NOTHING,
 "RR    E", NOTHING,
 "RR    H", NOTHING,
 "RR    L", NOTHING,
 "RR    (HL)", NOTHING,
 "RR    A", NOTHING,
 "SLA   B", NOTHING,
 "SLA   C", NOTHING,
 "SLA   D", NOTHING,
 "SLA   E", NOTHING,
 "SLA   H", NOTHING,
 "SLA   L", NOTHING,
 "SLA   (HL)", NOTHING,
 "SLA   A", NOTHING,
 "SRA   B", NOTHING,
 "SRA   C", NOTHING,
 "SRA   D", NOTHING,
 "SRA   E", NOTHING,
 "SRA   H", NOTHING,
 "SRA   L", NOTHING,
 "SRA   (HL)", NOTHING,
 "SRA   A", NOTHING,
 "SLL   B", NOTHING,
 "SLL   C", NOTHING,
 "SLL   D", NOTHING,
 "SLL   E", NOTHING,
 "SLL   H", NOTHING,
 "SLL   L", NOTHING,
 "SLL   (HL)", NOTHING,
 "SLL   A", NOTHING,
 "SRL   B", NOTHING,
 "SRL   C", NOTHING,
 "SRL   D", NOTHING,
 "SRL   E", NOTHING,
 "SRL   H", NOTHING,
 "SRL   L", NOTHING,
 "SRL   (HL)", NOTHING,
 "SRL   A", NOTHING,
 "BIT   0, B", NOTHING,
 "BIT   0, C", NOTHING,
 "BIT   0, D", NOTHING,
 "BIT   0, E", NOTHING,
 "BIT   0, H", NOTHING,
 "BIT   0, L", NOTHING,
 "BIT   0, (HL)", NOTHING,
 "BIT   0, A", NOTHING,
 "BIT   1, B", NOTHING,
 "BIT   1, C", NOTHING,
 "BIT   1, D", NOTHING,
 "BIT   1, E", NOTHING,
 "BIT   1, H", NOTHING,
 "BIT   1, L", NOTHING,
 "BIT   1, (HL)", NOTHING,
 "BIT   1, A", NOTHING,
 "BIT   2, B", NOTHING,
 "BIT   2, C", NOTHING,
 "BIT   2, D", NOTHING,
 "BIT   2, E", NOTHING,
 "BIT   2, H", NOTHING,
 "BIT   2, L", NOTHING,
 "BIT   2, (HL)", NOTHING,
 "BIT   2, A", NOTHING,
 "BIT   3, B", NOTHING,
 "BIT   3, C", NOTHING,
 "BIT   3, D", NOTHING,
 "BIT   3, E", NOTHING,
 "BIT   3, H", NOTHING,
 "BIT   3, L", NOTHING,
 "BIT   3, (HL)", NOTHING,
 "BIT   3, A", NOTHING,
 "BIT   4, B", NOTHING,
 "BIT   4, C", NOTHING,
 "BIT   4, D", NOTHING,
 "BIT   4, E", NOTHING,
 "BIT   4, H", NOTHING,
 "BIT   4, L", NOTHING,
 "BIT   4, (HL)", NOTHING,
 "BIT   4, A", NOTHING,
 "BIT   5, B", NOTHING,
 "BIT   5, C", NOTHING,
 "BIT   5, D", NOTHING,
 "BIT   5, E", NOTHING,
 "BIT   5, H", NOTHING,
 "BIT   5, L", NOTHING,
 "BIT   5, (HL)", NOTHING,
 "BIT   5, A", NOTHING,
 "BIT   6, B", NOTHING,
 "BIT   6, C", NOTHING,
 "BIT   6, D", NOTHING,
 "BIT   6, E", NOTHING,
 "BIT   6, H", NOTHING,
 "BIT   6, L", NOTHING,
 "BIT   6, (HL)", NOTHING,
 "BIT   6, A", NOTHING,
 "BIT   7, B", NOTHING,
 "BIT   7, C", NOTHING,
 "BIT   7, D", NOTHING,
 "BIT   7, E", NOTHING,
 "BIT   7, H", NOTHING,
 "BIT   7, L", NOTHING,
 "BIT   7, (HL)", NOTHING,
 "BIT   7, A", NOTHING,
 "RES   0, B", NOTHING,
 "RES   0, C", NOTHING,
 "RES   0, D", NOTHING,
 "RES   0, E", NOTHING,
 "RES   0, H", NOTHING,
 "RES   0, L", NOTHING,
 "RES   0, (HL)", NOTHING,
 "RES   0, A", NOTHING,
 "RES   1, B", NOTHING,
 "RES   1, C", NOTHING,
 "RES   1, D", NOTHING,
 "RES   1, E", NOTHING,
 "RES   1, H", NOTHING,
 "RES   1, L", NOTHING,
 "RES   1, (HL)", NOTHING,
 "RES   1, A", NOTHING,
 "RES   2, B", NOTHING,
 "RES   2, C", NOTHING,
 "RES   2, D", NOTHING,
 "RES   2, E", NOTHING,
 "RES   2, H", NOTHING,
 "RES   2, L", NOTHING,
 "RES   2, (HL)", NOTHING,
 "RES   2, A", NOTHING,
 "RES   3, B", NOTHING,
 "RES   3, C", NOTHING,
 "RES   3, D", NOTHING,
 "RES   3, E", NOTHING,
 "RES   3, H", NOTHING,
 "RES   3, L", NOTHING,
 "RES   3, (HL)", NOTHING,
 "RES   3, A", NOTHING,
 "RES   4, B", NOTHING,
 "RES   4, C", NOTHING,
 "RES   4, D", NOTHING,
 "RES   4, E", NOTHING,
 "RES   4, H", NOTHING,
 "RES   4, L", NOTHING,
 "RES   4, (HL)", NOTHING,
 "RES   4, A", NOTHING,
 "RES   5, B", NOTHING,
 "RES   5, C", NOTHING,
 "RES   5, D", NOTHING,
 "RES   5, E", NOTHING,
 "RES   5, H", NOTHING,
 "RES   5, L", NOTHING,
 "RES   5, (HL)", NOTHING,
 "RES   5, A", NOTHING,
 "RES   6, B", NOTHING,
 "RES   6, C", NOTHING,
 "RES   6, D", NOTHING,
 "RES   6, E", NOTHING,
 "RES   6, H", NOTHING,
 "RES   6, L", NOTHING,
 "RES   6, (HL)", NOTHING,
 "RES   6, A", NOTHING,
 "RES   7, B", NOTHING,
 "RES   7, C", NOTHING,
 "RES   7, D", NOTHING,
 "RES   7, E", NOTHING,
 "RES   7, H", NOTHING,
 "RES   7, L", NOTHING,
 "RES   7, (HL)", NOTHING,
 "RES   7, A", NOTHING,
 "SET   0, B", NOTHING,
 "SET   0, C", NOTHING,
 "SET   0, D", NOTHING,
 "SET   0, E", NOTHING,
 "SET   0, H", NOTHING,
 "SET   0, L", NOTHING,
 "SET   0, (HL)", NOTHING,
 "SET   0, A", NOTHING,
 "SET   1, B", NOTHING,
 "SET   1, C", NOTHING,
 "SET   1, D", NOTHING,
 "SET   1, E", NOTHING,
 "SET   1, H", NOTHING,
 "SET   1, L", NOTHING,
 "SET   1, (HL)", NOTHING,
 "SET   1, A", NOTHING,
 "SET   2, B", NOTHING,
 "SET   2, C", NOTHING,
 "SET   2, D", NOTHING,
 "SET   2, E", NOTHING,
 "SET   2, H", NOTHING,
 "SET   2, L", NOTHING,
 "SET   2, (HL)", NOTHING,
 "SET   2, A", NOTHING,
 "SET   3, B", NOTHING,
 "SET   3, C", NOTHING,
 "SET   3, D", NOTHING,
 "SET   3, E", NOTHING,
 "SET   3, H", NOTHING,
 "SET   3, L", NOTHING,
 "SET   3, (HL)", NOTHING,
 "SET   3, A", NOTHING,
 "SET   4, B", NOTHING,
 "SET   4, C", NOTHING,
 "SET   4, D", NOTHING,
 "SET   4, E", NOTHING,
 "SET   4, H", NOTHING,
 "SET   4, L", NOTHING,
 "SET   4, (HL)", NOTHING,
 "SET   4, A", NOTHING,
 "SET   5, B", NOTHING,
 "SET   5, C", NOTHING,
 "SET   5, D", NOTHING,
 "SET   5, E", NOTHING,
 "SET   5, H", NOTHING,
 "SET   5, L", NOTHING,
 "SET   5, (HL)", NOTHING,
 "SET   5, A", NOTHING,
 "SET   6, B", NOTHING,
 "SET   6, C", NOTHING,
 "SET   6, D", NOTHING,
 "SET   6, E", NOTHING,
 "SET   6, H", NOTHING,
 "SET   6, L", NOTHING,
 "SET   6, (HL)", NOTHING,
 "SET   6, A", NOTHING,
 "SET   7, B", NOTHING,
 "SET   7, C", NOTHING,
 "SET   7, D", NOTHING,
 "SET   7, E", NOTHING,
 "SET   7, H", NOTHING,
 "SET   7, L", NOTHING,
 "SET   7, (HL)", NOTHING,
 "SET   7, A", NOTHING
}, tabdd[]={
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "ADD   IX,BC", NOTHING, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "ADD   IX,DE", NOTHING, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LD    IX,$%04X", ARG16, 
 "LD    ($%04X),IX", ARG16, 
 "INC   IX", NOTHING, 
 "INC   IXH", NOTHING, 
 "DEC   IXH", NOTHING, 
 "LD    IXH,$%02X", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "ADD   IX,IX", NOTHING, 
 "LD    IX,($%04X)", ARG16, 
 "DEC   IX", NOTHING, 
 "INC   IXL", NOTHING, 
 "DEC   IXL", NOTHING, 
 "LD    IXL,$%02X", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "INC   (IX+$%02X)", ARG8, 
 "DEC   (IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "ADD   IX,SP", NOTHING, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LD    B,IXH", NOTHING, 
 "LD    B,IXL", NOTHING, 
 "LD    B,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LD    C,IXH", NOTHING, 
 "LD    C,IXL", NOTHING, 
 "LD    C,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LD    D,IXH", NOTHING, 
 "LD    D,IXL", NOTHING, 
 "LD    E,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "LD    IXH,B", NOTHING, 
 "LD    IXH,C", NOTHING, 
 "LD    IXH,D", NOTHING, 
 "LD    IXH,E", NOTHING, 
 "LD    IXH,IXH", NOTHING, 
 "LD    IXH,IXL", NOTHING, 
 "LD    H,(IX+$%02X)", ARG8, 
 "LD    IXH,A", NOTHING, 
 "LD    IXL,B", NOTHING, 
 "LD    IXL,C", NOTHING, 
 "LD    IXL,D", NOTHING, 
 "LD    IXL,E", NOTHING, 
 "LD    IXL,IXH", NOTHING, 
 "LD    IXL,IXL", NOTHING, 
 "LD    L,(IX+$%02X)", ARG8, 
 "LD    IXL,A", NOTHING, 
 "LD    (IX+$%02X),B", ARG8, 
 "LD    (IX+$%02X),C", ARG8, 
 "LD    (IX+$%02X),D", ARG8, 
 "LD    (IX+$%02X),E", ARG8, 
 "LD    (IX+$%02X),H", ARG8, 
 "LD    (IX+$%02X),L", ARG8, 
 "???   ", NOTHING,
 "LD    (IX+$%02X),A", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LD    A,IXH", NOTHING, 
 "LD    A,IXL", NOTHING, 
 "LD    A,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "ADD   A,IXH", NOTHING, 
 "ADD   A,IXL", NOTHING, 
 "ADD   A,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "ADC   A,IXH", NOTHING, 
 "ADC   A,IXL", NOTHING, 
 "ADC   A,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "SUB   A,IXH", NOTHING, 
 "SUB   A,IXL", NOTHING, 
 "SUB   A,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "SBC   A,IXH", NOTHING, 
 "SBC   A,IXL", NOTHING, 
 "SBC   A,(IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "AND   IXH", NOTHING, 
 "AND   IXL", NOTHING, 
 "AND   (IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "XOR   IXH", NOTHING, 
 "XOR   IXL", NOTHING, 
 "XOR   (IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "OR    IXH", NOTHING, 
 "OR    IXL", NOTHING, 
 "OR    (IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "CP    IXH", NOTHING, 
 "CP    IXL", NOTHING, 
 "CP    (IX+$%02X)", ARG8, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "POP   IX", NOTHING, 
 "???   ", NOTHING,
 "EX    (SP),IX", NOTHING, 
 "???   ", NOTHING,
 "PUSH  IX", NOTHING, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "JP    (IX)", NOTHING, 
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING
},tabed[]={
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "IN    B, (C)", NOTHING,
 "OUT   (C), B", NOTHING,
 "SBC   HL, BC", NOTHING,
 "LD    ($%04X), BC", ARG16,
 "NEG   ", NOTHING,
 "RETN  ", NOTHING,
 "IM0   ", NOTHING,
 "LD    I, A", NOTHING,
 "IN    C, (C)", NOTHING,
 "OUT   (C), C", NOTHING,
 "ADC   HL, BC", NOTHING,
 "LD    BC, ($%04X)", ARG16,
 "NEG   ", NOTHING,
 "RETI  ", NOTHING,
 "???   ", NOTHING,
 "LD    R, A", NOTHING,
 "IN    D, (C)", NOTHING,
 "OUT   (C), D", NOTHING,
 "SBC   HL, DE", NOTHING,
 "LD    ($%04X), DE", ARG16,
 "NEG   ", NOTHING,
 "RETN  ", NOTHING,
 "IM1   ", NOTHING,
 "LD    A, I", NOTHING,
 "IN    E, (C)", NOTHING,
 "OUT   (C), E", NOTHING,
 "ADC   HL, DE", NOTHING,
 "LD    DE, ($%04X)", ARG16,
 "NEG   ", NOTHING,
 "RETN  ", NOTHING,
 "IM2   ", NOTHING,
 "LD    A, R", NOTHING,
 "IN    H, (C)", NOTHING,
 "OUT   (C), H", NOTHING,
 "SBC   HL, HL", NOTHING,
 "LD    ($%04X), HL", ARG16,
 "NEG   ", NOTHING,
 "RETN  ", NOTHING,
 "???   ", NOTHING,
 "RRD   ", NOTHING,
 "IN    L, (C)", NOTHING,
 "OUT   (C), L", NOTHING,
 "ADC   HL, HL", NOTHING,
 "LD    HL, ($%04X)", ARG16,
 "NEG   ", NOTHING,
 "RETN  ", NOTHING,
 "???   ", NOTHING,
 "RLD   ", NOTHING,
 "IN    F, (C)", NOTHING,
 "OUT   (C), $00", NOTHING,
 "SBC   HL, SP", NOTHING,
 "LD    ($%04X), SP", ARG16,
 "NEG   ", NOTHING,
 "RETN  ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "IN    A, (C)", NOTHING,
 "OUT   (C), A", NOTHING,
 "ADC   HL, SP", NOTHING,
 "LD    SP, ($%04X)", ARG16,
 "NEG   ", NOTHING,
 "RETI  ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LDI   ", NOTHING,
 "CPI   ", NOTHING,
 "INI   ", NOTHING,
 "OUTI  ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LDD   ", NOTHING,
 "CPD   ", NOTHING,
 "IND   ", NOTHING,
 "OUTD  ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LDIR  ", NOTHING,
 "CPIR  ", NOTHING,
 "INIR  ", NOTHING,
 "OUTIR ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "LDDR  ", NOTHING,
 "CPDR  ", NOTHING,
 "INDR  ", NOTHING,
 "OUTDR ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING,
 "???   ", NOTHING
}, tabfd[]={
 "ADD    IY,BC", NOTHING,
 "ADD    IY,DE", NOTHING,
 "LD     IY,%04X", ARG16,
 "LD     (%04X),IY", ARG16,
 "INC    IY", NOTHING,
 "INC    IYH", NOTHING,
 "DEC    IYH", NOTHING,
 "LD     IYH,%02X", ARG8,
 "ADD    IY,IY", NOTHING,
 "LD     IY,(%04X)", ARG16,
 "DEC    IY", NOTHING,
 "INC    IYL", NOTHING,
 "DEC    IYL", NOTHING,
 "LD     IYL,%02X", ARG8,
 "INC    (IY+%02X)", ARG8,
 "DEC    (IY+%02X)", ARG8,
 "ADD    IY,SP", NOTHING,
 "LD     B,IYH", NOTHING,
 "LD     B,IYL", NOTHING,
 "LD     B,(IY+%02X)", ARG8,
 "LD     C,IYH", NOTHING,
 "LD     C,IYL", NOTHING,
 "LD     C,(IY+%02X)", ARG8,
 "LD     D,IYH", NOTHING,
 "LD     D,IYL", NOTHING,
 "LD     E,(IY+%02X)", ARG8,
 "LD     IYH,B", NOTHING,
 "LD     IYH,C", NOTHING,
 "LD     IYH,D", NOTHING,
 "LD     IYH,E", NOTHING,
 "LD     IYH,IYH", NOTHING,
 "LD     IYH,IYL", NOTHING,
 "LD     H,(IY+%02X)", ARG8,
 "LD     IYH,A", NOTHING,
 "LD     IYL,B", NOTHING,
 "LD     IYL,C", NOTHING,
 "LD     IYL,D", NOTHING,
 "LD     IYL,E", NOTHING,
 "LD     IYL,IYH", NOTHING,
 "LD     IYL,IYL", NOTHING,
 "LD     L,(IY+%02X)", ARG8,
 "LD     IYL,A", NOTHING,
 "LD     (IY+%02X),B", ARG8,
 "LD     (IY+%02X),C", ARG8,
 "LD     (IY+%02X),D", ARG8,
 "LD     (IY+%02X),E", ARG8,
 "LD     (IY+%02X),H", ARG8,
 "LD     (IY+%02X),L", ARG8,
 "LD     (IY+%02X),A", ARG8,
 "LD     A,IYH", NOTHING,
 "LD     A,IYL", NOTHING,
 "LD     A,(IY+%02X)", ARG8,
 "ADD    A,IYH", NOTHING,
 "ADD    A,IYL", NOTHING,
 "ADD    A,(IY+%02X)", ARG8,
 "ADC    A,IYH", NOTHING,
 "ADC    A,IYL", NOTHING,
 "ADC    A,(IY+%02X)", ARG8,
 "SUB    A,IYH", NOTHING,
 "SUB    A,IYL", NOTHING,
 "SUB    A,(IY+%02X)", ARG8,
 "SBC    A,IYH", NOTHING,
 "SBC    A,IYL", NOTHING,
 "SBC    A,(IY+%02X)", ARG8,
 "AND    IYH", NOTHING,
 "AND    IYL", NOTHING,
 "AND    (IY+%02X)", ARG8,
 "XOR    IYH", NOTHING,
 "XOR    IYL", NOTHING,
 "XOR    (IY+%02X)", ARG8,
 "OR     IYH", NOTHING,
 "OR     IYL", NOTHING,
 "OR     (IY+%02X)", ARG8,
 "CP     IYH", NOTHING,
 "CP     IYL", NOTHING,
 "CP     (IY+%02X)", ARG8,
 "POP    IY", NOTHING,
 "EX     (SP),IY", NOTHING,
 "PUSH   IY", NOTHING,
 "JP     (IY)", NOTHING
};

void dasm (z80 *cpu, uint16_t addr)
{
 uint8_t c, d, e, f;
 uint16_t g, a;
 char *op;
 zop z;
 
 a=addr;
 c=cpu->read_byte(cpu->userdata, a++);
 d=0;
 /* CB DD ED FD */
 if (c==0xCB)
 {
  d=cpu->read_byte(cpu->userdata, a++);
  z=tabcb[d];
 }
 else if (c==0xDD)
 {
  d=cpu->read_byte(cpu->userdata, a++);
  z=tabdd[d];
 }
 else if (c==0xED)
 {
  d=cpu->read_byte(cpu->userdata, a++);
  z=tabfd[d];
 }
 else if (c==0xFD)
 {
  d=cpu->read_byte(cpu->userdata, a++);
  z=tabfd[d];
 }
 else 
  z=tabmain[c];
 
 switch (z.fmt)
 {
  case ARG8:
   g=cpu->read_byte(cpu->userdata, a++);
   break;
  case ARG16:
   e=cpu->read_byte(cpu->userdata, a++);
   f=cpu->read_byte(cpu->userdata, a++);
   g=f;
   g<<=8;
   g|=e;
   break;
  case ARGREL:
   e=cpu->read_byte(cpu->userdata, a++);
   g=a+(int8_t) e;
   break;
  default:
   g=0; /* irrelevant */
 }
 printf ("%04X- %02X ", addr, c);
 if ((c==0xCB)||(c==0xDD)||(c==0xED)||(c==0xFD))
 {
  if (z.fmt==NOTHING)
   printf ("%02X       ", d);
  else if (z.fmt==ARG16)
   printf ("%02X %02X %02X ", d, e, f);
  else
   printf ("%02X %02X    ", d, g);
 }
 else
 {
  if (z.fmt==NOTHING)
   printf ("         ");
  else if (z.fmt==ARG16)
   printf ("%02X %02X    ", e, f);
  else
   printf ("%02X       ", g);
 }
 printf (z.disp, g);
 printf ("\n%04X-  AF=%02X%02X BC=%02X%02X DE=%02X%02X HL=%02X%02X SP=%04X\n"
           "       IX=%04X IY=%04X          I=%02X    R=%02X\n",
         cpu->pc, cpu->a, get_f(cpu), cpu->b, cpu->c, cpu->d, cpu->e,
         cpu->h, cpu->l, cpu->sp, cpu->ix, cpu->iy, cpu->i, cpu->r);
}
#endif
