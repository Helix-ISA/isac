#ifndef HX_MNEMONIC_H
#define HX_MNEMONIC_H

#include "isac/types.h"

typedef enum {
	HX_ADD,
	HX_SUB,
	HX_AND,
	HX_OR,
	HX_XOR,
	HX_SLL,
	HX_SLR,
	HX_SAR,
	HX_SLT,
	HX_SLTU,

	HX_ADDI,
	HX_ANDI,
	HX_ORI,
	HX_XORI,
	HX_SLLI,
	HX_SLRI,
	HX_SARI,
	HX_SLTI,
	HX_SLTUI,

	HX_SB,
	HX_SQ,
	HX_SH,
	HX_SW,

	HX_LB,
	HX_LQ,
	HX_LH,
	HX_LW,
	HX_LBU,
	HX_LQU,
	HX_LHU,

	HX_BEQ,
	HX_BNE,
	HX_BLT,
	HX_BGE,
	
	HX_JAL,
	HX_JRAL,

	/* Pseudo Instructions */
	HX_NOP,
	HX_MOV,
	HX_JMP,

	HX_MNEMONIC_UNKNOWN
} hx_mnemonic;

HAPI hx_mnemonic get_mnemonic(const char *string, u32 string_length);
HAPI u8 get_opcode(hx_mnemonic mnemonic);
HAPI u8 get_function(hx_mnemonic mnemonic);
HAPI u8 get_modifier(hx_mnemonic mnemonic);

hx_mnemonic decode_mnemonic(u8 opcode, u8 function, u8 mod);

#endif
