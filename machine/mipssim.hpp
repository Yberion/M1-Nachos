/*! \file mipssim.hpp 
 \brief Internal data structures for simulating the MIPS instruction set.
 DO NOT CHANGE -- part of the machine emulation

 Copyright (c) 1992-1993 The Regents of the University of California.
 All rights reserved.  See copyright.hpp for copyright notice and limitation 
 of liability and disclaimer of warranty provisions.
 */

#ifndef MIPSSIM_H
#define MIPSSIM_H

#include "kernel/copyright.hpp"

/*
 * OpCode values.  The names are straight from the MIPS
 * manual except for the following special ones:
 *
 * OP_UNIMP -		means that this instruction is legal, but hasn't
 *			been implemented in the simulator yet.
 * OP_RES -		means that this is a reserved opcode (it isn't
 *			supported by the architecture).
 *
 * Recent changes (I. Puaut, march 2002), addition of some
 *    COP1 floating point instructions (MIPS I only). 
 *    No fixed-point supported,
 *    and no support neither for NaN values. No exception raised
 *    (behavior is unspecified in such cases).
 */

#define OP_ADD		1
#define OP_ADDI		2
#define OP_ADDIU	3
#define OP_ADDU		4
#define OP_AND		5
#define OP_ANDI		6
#define OP_BEQ		7
#define OP_BGEZ		8
#define OP_BGEZAL	9
#define OP_BGTZ		10
#define OP_BLEZ		11
#define OP_BLTZ		12
#define OP_BLTZAL	13
#define OP_BNE		14
#define OP_DIV		16
#define OP_DIVU		17
#define OP_J		18
#define OP_JAL		19
#define OP_JALR		20
#define OP_JR		21
#define OP_LB		22
#define OP_LBU		23
#define OP_LH		24
#define OP_LHU		25
#define OP_LUI		26
#define OP_LW		27
#define OP_LWL		28
#define OP_LWR		29
#define OP_MFHI		31
#define OP_MFLO		32
#define OP_MTHI		34
#define OP_MTLO		35
#define OP_MULT		36
#define OP_MULTU	37
#define OP_NOR		38
#define OP_OR		39
#define OP_ORI		40
#define OP_RFE		41
#define OP_SB		42
#define OP_SH		43
#define OP_SLL		44
#define OP_SLLV		45
#define OP_SLT		46
#define OP_SLTI		47
#define OP_SLTIU	48
#define OP_SLTU		49
#define OP_SRA		50
#define OP_SRAV		51
#define OP_SRL		52
#define OP_SRLV		53
#define OP_SUB		54
#define OP_SUBU		55
#define OP_SW		56
#define OP_SWL		57
#define OP_SWR		58
#define OP_XOR		59
#define OP_XORI		60
#define OP_SYSCALL	61

/* MIPS I floating point instructions (S/D), no fixed point (W) */
#define OP_LWC1         62
#define OP_LDC1         63
#define OP_SWC1         64
#define OP_SDC1         65
#define OP_ABS_S        66
#define OP_ABS_D        67
#define OP_ADD_S        68
#define OP_ADD_D        69
#define OP_DIV_S        70
#define OP_DIV_D        71
#define OP_MUL_S        72
#define OP_MUL_D        73
#define OP_NEG_S        74
#define OP_NEG_D        75
#define OP_SUB_S        76
#define OP_SUB_D        77
#define OP_CVT_S_D      78
#define OP_CVT_S_W      79
#define OP_CVT_W_S      80
#define OP_CVT_W_D      81
#define OP_CVT_D_S      82
#define OP_CVT_D_W      83
#define OP_CEIL_W_S     84
#define OP_CEIL_W_D     85
#define OP_FLOOR_W_S    86
#define OP_FLOOR_W_D    87
#define OP_ROUND_W_S    88
#define OP_ROUND_W_D    89
#define OP_TRUNC_W_S    90
#define OP_TRUNC_W_D    91
#define OP_MOV_S        92
#define OP_MOV_D        93
#define OP_BC1F         94
#define OP_BC1T         95
#define OP_BC1FL        96
#define OP_BC1TL        97
#define OP_SQRT_S       98
#define OP_SQRT_D       99
#define OP_C_F_S        100
#define OP_C_UN_S       101
#define OP_C_EQ_S       102
#define OP_C_UEQ_S      103
#define OP_C_OLT_S      104
#define OP_C_ULT_S      105
#define OP_C_OLE_S      106
#define OP_C_ULE_S      107
#define OP_C_SF_S       108
#define OP_C_NGLE_S     109
#define OP_C_SEQ_S      110
#define OP_C_NGL_S      111
#define OP_C_LT_S       112
#define OP_C_NGE_S      113
#define OP_C_LE_S       114
#define OP_C_NGT_S      115
#define OP_C_F_D        116
#define OP_C_UN_D       117
#define OP_C_EQ_D       118
#define OP_C_UEQ_D      119
#define OP_C_OLT_D      120
#define OP_C_ULT_D      121
#define OP_C_OLE_D      122
#define OP_C_ULE_D      123
#define OP_C_SF_D       124
#define OP_C_NGLE_D     125
#define OP_C_SEQ_D      126
#define OP_C_NGL_D      127
#define OP_C_LT_D       128
#define OP_C_NGE_D      129
#define OP_C_LE_D       130
#define OP_C_NGT_D      131
#define OP_MFC1         132
#define OP_CFC1         133
#define OP_MTC1         134
#define OP_CTC1         135

#define OP_UNIMP	136
#define OP_RES		137

#define MaxOpcode	137

/*
 * Miscellaneous definitions:
 */

#define IndexToAddr(x) ((x) << 2)

// Mask to obtain the sign bit of integers
#define SIGN_BIT	0x80000000

// Constant for return address register
#define R31		31

// Constants used for instruction decoding
#define SPECIAL 140
#define BCOND	141
#define COP1    142
#define IFMT 1
#define JFMT 2
#define RFMT 3

/*!
 * Information related to the opcode of a MIPS instruction
 */
struct OpInfo
{
    int opCode; /*!< Translated op code. */
    int format; /*!< Format type (IFMT or JFMT or RFMT) */
};

/*!
 * The table is used to translate bits 31:26 of the instruction
 * into a value suitable for the "opCode" field of a MemWord structure,
 * or into a special value (SPECIAL, BCOND, COP1) for further decoding.
 */
static OpInfo opTable[] = { { SPECIAL, RFMT }, { BCOND, IFMT }, { OP_J, JFMT }, { OP_JAL, JFMT }, { OP_BEQ, IFMT }, { OP_BNE, IFMT }, { OP_BLEZ, IFMT }, {
        OP_BGTZ, IFMT }, { OP_ADDI, IFMT }, { OP_ADDIU, IFMT }, { OP_SLTI, IFMT }, { OP_SLTIU, IFMT }, { OP_ANDI, IFMT }, { OP_ORI, IFMT }, { OP_XORI, IFMT }, {
        OP_LUI, IFMT }, { OP_UNIMP, IFMT }, { COP1, IFMT }, { OP_UNIMP, IFMT }, { OP_UNIMP, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, {
        OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_RES,
        IFMT }, { OP_LB, IFMT }, { OP_LH, IFMT }, { OP_LWL, IFMT }, { OP_LW, IFMT }, { OP_LBU, IFMT }, { OP_LHU, IFMT }, { OP_LWR, IFMT }, { OP_RES, IFMT }, {
        OP_SB, IFMT }, { OP_SH, IFMT }, { OP_SWL, IFMT }, { OP_SW, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_SWR, IFMT }, { OP_RES, IFMT }, { OP_UNIMP,
        IFMT }, { OP_LWC1, IFMT }, { OP_UNIMP, IFMT }, { OP_UNIMP, IFMT }, { OP_RES, IFMT }, { OP_LDC1, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT }, { OP_UNIMP,
        IFMT }, { OP_SWC1, IFMT }, { OP_UNIMP, IFMT }, { OP_UNIMP, IFMT }, { OP_RES, IFMT }, { OP_SDC1, IFMT }, { OP_RES, IFMT }, { OP_RES, IFMT } };

/*!
 * The table below is used to convert the "funct" field of SPECIAL
 * instructions into the "opCode" field of a MemWord.
 */

static int specialTable[] = {
OP_SLL, OP_RES, OP_SRL, OP_SRA, OP_SLLV, OP_RES, OP_SRLV, OP_SRAV,
OP_JR, OP_JALR, OP_RES, OP_RES, OP_SYSCALL, OP_UNIMP, OP_RES, OP_RES,
OP_MFHI, OP_MTHI, OP_MFLO, OP_MTLO, OP_RES, OP_RES, OP_RES, OP_RES,
OP_MULT, OP_MULTU, OP_DIV, OP_DIVU, OP_RES, OP_RES, OP_RES, OP_RES,
OP_ADD, OP_ADDU, OP_SUB, OP_SUBU, OP_AND, OP_OR, OP_XOR, OP_NOR,
OP_RES, OP_RES, OP_SLT, OP_SLTU, OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES, OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES, OP_RES, OP_RES, OP_RES, OP_RES };

/* !
 * The table below is used to convert the "function" field of COP1
 * instructions for RS=S (single precision floating point instructions) 
 * into the "Opcode" field of a MemWord.
 */

static int cop1STable[] = {
OP_ADD_S, OP_SUB_S, OP_MUL_S, OP_DIV_S,
OP_SQRT_S, OP_ABS_S, OP_MOV_S, OP_NEG_S,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_ROUND_W_S, OP_TRUNC_W_S, OP_CEIL_W_S, OP_FLOOR_W_S,
OP_RES, OP_UNIMP, OP_UNIMP, OP_UNIMP,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_CVT_D_S, OP_RES, OP_RES,
OP_CVT_W_S, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_C_F_S, OP_C_UN_S, OP_C_EQ_S, OP_C_UEQ_S,
OP_C_OLT_S, OP_C_ULT_S, OP_C_OLE_S, OP_C_ULE_S,
OP_C_SF_S, OP_C_NGLE_S, OP_C_SEQ_S, OP_C_NGL_S,
OP_C_LT_S, OP_C_NGE_S, OP_C_LE_S, OP_C_NGT_S };

/* !
 * The table below is used to convert the "function" field of COP1
 * instructions for RS=D (single precision floating point instructions)
 * into the "Opcode" field of a MemWord.
 */

static int cop1DTable[] = {
OP_ADD_D, OP_SUB_D, OP_MUL_D, OP_DIV_D,
OP_SQRT_D, OP_ABS_D, OP_MOV_D, OP_NEG_D,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_ROUND_W_D, OP_TRUNC_W_D, OP_CEIL_W_D, OP_FLOOR_W_D,
OP_RES, OP_UNIMP, OP_UNIMP, OP_UNIMP,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_CVT_S_D, OP_RES, OP_RES, OP_RES,
OP_CVT_W_D, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_RES, OP_RES, OP_RES, OP_RES,
OP_C_F_D, OP_C_UN_D, OP_C_EQ_D, OP_C_UEQ_D,
OP_C_OLT_D, OP_C_ULT_D, OP_C_OLE_D, OP_C_ULE_D,
OP_C_SF_D, OP_C_NGLE_D, OP_C_SEQ_D, OP_C_NGL_D,
OP_C_LT_D, OP_C_NGE_D, OP_C_LE_D, OP_C_NGT_D };

//! Stuff to help print out each instruction, for debugging
enum RegType
{
    NONE,
    RS,
    RT,
    RD,
    FS,
    FT,
    FD,
    EXTRA
};

//! Textual representation of Mips instructions and their operands
struct OpString
{
    const char *string; //!< Printed version of instruction
    RegType args[3];
};

//! Textual form of instructions
static struct OpString opStrings[] = { { "Shouldn't happen", { NONE, NONE, NONE } }, { "ADD r%d,r%d,r%d", { RD, RS, RT } }, {
        "ADDI r%d,r%d,%d", { RT, RS, EXTRA } }, { "ADDIU r%d,r%d,%d", { RT, RS, EXTRA } }, { "ADDU r%d,r%d,r%d", { RD, RS, RT } }, {
        "AND r%d,r%d,r%d", { RD, RS, RT } }, { "ANDI r%d,r%d,%d", { RT, RS, EXTRA } }, { "BEQ r%d,r%d,%d", { RS, RT, EXTRA } }, {
        "BGEZ r%d,%d", { RS, EXTRA, NONE } }, { "BGEZAL r%d,%d", { RS, EXTRA, NONE } }, { "BGTZ r%d,%d", { RS, EXTRA, NONE } }, {
        "BLEZ r%d,%d", { RS, EXTRA, NONE } }, { "BLTZ r%d,%d", { RS, EXTRA, NONE } }, { "BLTZAL r%d,%d", { RS, EXTRA, NONE } }, {
        "BNE r%d,r%d,%d", { RS, RT, EXTRA } }, { "Shouldn't happen", { NONE, NONE, NONE } }, { "DIV r%d,r%d", { RS, RT, NONE } }, {
        "DIVU r%d,r%d", { RS, RT, NONE } }, { "J 0x%x", { EXTRA, NONE, NONE } }, { "JAL 0x%x", { EXTRA, NONE, NONE } }, {
        "JALR r%d,r%d", { RD, RS, NONE } }, { "JR r%d,r%d", { RD, RS, NONE } }, { "LB r%d,%d(r%d)", { RT, EXTRA, RS } }, {
        "LBU r%d,%d(r%d)", { RT, EXTRA, RS } }, { "LH r%d,%d(r%d)", { RT, EXTRA, RS } }, { "LHU r%d,%d(r%d)", { RT, EXTRA, RS } }, {
        "LUI r%d,%d", { RT, EXTRA, NONE } }, { "LW r%d,%d(r%d)", { RT, EXTRA, RS } }, { "LWL r%d,%d(r%d)", { RT, EXTRA, RS } }, {
        "LWR r%d,%d(r%d)", { RT, EXTRA, RS } }, { "Shouldn't happen", { NONE, NONE, NONE } }, { "MFHI r%d", { RD, NONE, NONE } }, {
        "MFLO r%d", { RD, NONE, NONE } }, { "Shouldn't happen", { NONE, NONE, NONE } }, { "MTHI r%d", { RS, NONE, NONE } }, {
        "MTLO r%d", { RS, NONE, NONE } }, { "MULT r%d,r%d", { RS, RT, NONE } }, { "MULTU r%d,r%d", { RS, RT, NONE } }, {
        "NOR r%d,r%d,r%d", { RD, RS, RT } }, { "OR r%d,r%d,r%d", { RD, RS, RT } }, { "ORI r%d,r%d,%d", { RT, RS, EXTRA } }, { "RFE",
        { NONE, NONE, NONE } }, { "SB r%d,%d(r%d)", { RT, EXTRA, RS } }, { "SH r%d,%d(r%d)", { RT, EXTRA, RS } }, { "SLL r%d,r%d,%d", { RD,
        RT, EXTRA } }, { "SLLV r%d,r%d,r%d", { RD, RT, RS } }, { "SLT r%d,r%d,r%d", { RD, RS, RT } }, { "SLTI r%d,r%d,%d",
        { RT, RS, EXTRA } }, { "SLTIU r%d,r%d,%d", { RT, RS, EXTRA } }, { "SLTU r%d,r%d,r%d", { RD, RS, RT } }, { "SRA r%d,r%d,%d", { RD,
        RT, EXTRA } }, { "SRAV r%d,r%d,r%d", { RD, RT, RS } }, { "SRL r%d,r%d,%d", { RD, RT, EXTRA } }, { "SRLV r%d,r%d,r%d",
        { RD, RT, RS } }, { "SUB r%d,r%d,r%d", { RD, RS, RT } }, { "SUBU r%d,r%d,r%d", { RD, RS, RT } }, { "SW r%d,%d(r%d)", { RT, EXTRA,
        RS } }, { "SWL r%d,%d(r%d)", { RT, EXTRA, RS } }, { "SWR r%d,%d(r%d)", { RT, EXTRA, RS } }, { "XOR r%d,r%d,r%d", { RD, RS, RT } },
        { "XORI r%d,r%d,%d", { RT, RS, EXTRA } }, { "SYSCALL", { NONE, NONE, NONE } },

        /* Some of the floating point instructions (MIPS I, no "W" instr) */
        { "LWC1 f%d,%d(r%d)", { FT, EXTRA, RS } }, { "LDC1 f%d,%d(r%d)", { FT, EXTRA, RS } }, { "SWC1 f%d,%d(r%d)", { FT, EXTRA, RS } }, {
                "SDC1 f%d,%d(r%d)", { FT, EXTRA, RS } }, { "ABS.S f%d,f%d", { FD, FS, NONE } }, { "ABS.D f%d,f%d", { FD, FS, NONE } }, {
                "ADD.S f%d,f%d,f%d", { FD, FS, FT } }, { "ADD.D f%d,f%d,f%d", { FD, FS, FT } }, { "DIV.S f%d,f%d,f%d", { FD, FS, FT } }, {
                "DIV.D f%d,f%d,f%d", { FD, FS, FT } }, { "MUL.S f%d,f%d,f%d", { FD, FS, FT } }, { "MUL.D f%d,f%d,f%d", { FD, FS, FT } }, {
                "NEG.S f%d,f%d", { FD, FS, NONE } }, { "NEG.D f%d,f%d", { FD, FS, NONE } }, { "SUB.S f%d,f%d,f%d", { FD, FS, FT } }, {
                "SUB.D f%d,f%d,f%d", { FD, FS, FT } }, { "CVT.S.D f%d,f%d", { FD, FS, NONE } }, { "CVT.S.W f%d,f%d", { FD, FS, NONE } }, {
                "CVT.W.S f%d,f%d", { FD, FS, NONE } }, { "CVT.W.D f%d,f%d", { FD, FS, NONE } }, { "CVT.D.S f%d,f%d", { FD, FS, NONE } }, {
                "CVT.D.W f%d,f%d", { FD, FS, NONE } }, { "CEIL.W.S f%d,f%d", { FD, FS, NONE } }, { "CEIL.W.D f%d,f%d", { FD, FS, NONE } },
        { "FLOOR.W.S f%d,f%d", { FD, FS, NONE } }, { "FLOOR.W.D f%d,f%d", { FD, FS, NONE } }, { "ROUND.W.S f%d,f%d", { FD, FS, NONE } }, {
                "ROUND.W.D f%d,f%d", { FD, FS, NONE } }, { "TRUNC.W.S f%d,f%d", { FD, FS, NONE } },
        { "TRUNC.W.D f%d,f%d", { FD, FS, NONE } }, { "MOV.S f%d,f%d", { FD, FS, NONE } }, { "MOV.D f%d,f%d", { FD, FS, NONE } }, {
                "BC1F %d", { EXTRA, NONE, NONE } }, { "BC1T %d", { EXTRA, NONE, NONE } }, { "BC1FL %d", { EXTRA, NONE, NONE } }, {
                "BC1TL %d", { EXTRA, NONE, NONE } }, { "SQRT.S f%d,f%d", { FD, FS, NONE } }, { "SQRT.D f%d,f%d", { FD, FS, NONE } }, {
                "C.F.S f%d,f%d", { FS, FT, NONE } }, { "C.UN.S f%d,f%d", { FS, FT, NONE } }, { "C.EQ.S f%d,f%d", { FS, FT, NONE } }, {
                "C.UEQ.S f%d,f%d", { FS, FT, NONE } }, { "C.OLT.S f%d,f%d", { FS, FT, NONE } }, { "C.ULT.S f%d,f%d", { FS, FT, NONE } }, {
                "C.OLE.S f%d,f%d", { FS, FT, NONE } }, { "C.ULE.S f%d,f%d", { FS, FT, NONE } }, { "C.SF.S f%d,f%d", { FS, FT, NONE } }, {
                "C.NGLE.S f%d,f%d", { FS, FT, NONE } }, { "C.SEQ.S f%d,f%d", { FS, FT, NONE } }, { "C.NGL.S f%d,f%d", { FS, FT, NONE } }, {
                "C.LT.S f%d,f%d", { FS, FT, NONE } }, { "C.NGE.S f%d,f%d", { FS, FT, NONE } }, { "C.LE.S f%d,f%d", { FS, FT, NONE } }, {
                "C.NGT.S f%d,f%d", { FS, FT, NONE } }, { "C.F.D f%d,f%d", { FS, FT, NONE } }, { "C.UN.D f%d,f%d", { FS, FT, NONE } }, {
                "C.EQ.D f%d,f%d", { FS, FT, NONE } }, { "C.UEQ.D f%d,f%d", { FS, FT, NONE } }, { "C.OLT.D f%d,f%d", { FS, FT, NONE } }, {
                "C.ULT.D f%d,f%d", { FS, FT, NONE } }, { "C.OLE.D f%d,f%d", { FS, FT, NONE } }, { "C.ULE.D f%d,f%d", { FS, FT, NONE } }, {
                "C.SF.D f%d,f%d", { FS, FT, NONE } }, { "C.NGLE.D f%d,f%d", { FS, FT, NONE } }, { "C.SEQ.D f%d,f%d", { FS, FT, NONE } }, {
                "C.NGL.D f%d,f%d", { FS, FT, NONE } }, { "C.LT.D f%d,f%d", { FS, FT, NONE } }, { "C.NGE.D f%d,f%d", { FS, FT, NONE } }, {
                "C.LE.D f%d,f%d", { FS, FT, NONE } }, { "C.NGT.D f%d,f%d", { FS, FT, NONE } }, { "OP_MFC1 r%d,f%d", { RT, FS, NONE } }, {
                "OP_CFC1 r%d,f%d", { RT, FS, NONE } }, { "OP_MTC1 r%d,f%d", { RT, FS, NONE } }, { "OP_CTC1 r%d,f%d", { RT, FS, NONE } }, {
                "Unimplemented", { NONE, NONE, NONE } }, { "Reserved", { NONE, NONE, NONE } } };

#endif // MIPSSIM_H
