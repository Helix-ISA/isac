#include "isac/mnemonic.h"
#include <string.h>

#define MATCH(s) \
	(string_length == sizeof(s) - 1 && strncmp(string, s, string_length) == 0)

hx_mnemonic get_mnemonic(const char *string, u32 string_length)
{
	if (MATCH("add")) {
		return HX_ADD;
	} else if (MATCH("sub")) {
		return HX_SUB;
	} else if (MATCH("and")) {
		return HX_AND;
	} else if (MATCH("or")) {
		return HX_OR;
	} else if (MATCH("xor")) {
		return HX_XOR;
	} else if (MATCH("sll")) {
		return HX_SLL;
	} else if (MATCH("slr")) {
		return HX_SLR;
	} else if (MATCH("sar")) {
		return HX_SAR;
	} else if (MATCH("slt")) {
		return HX_SLT;
	} else if (MATCH("sltu")) {
		return HX_SLTU;
	} else if (MATCH("addi")) {
		return HX_ADDI;
	} else if (MATCH("andi")) {
		return HX_ANDI;
	} else if (MATCH("ori")) {
		return HX_ORI;
	} else if (MATCH("xori")) {
		return HX_XORI;
	} else if (MATCH("slli")) {
		return HX_SLLI;
	} else if (MATCH("slri")) {
		return HX_SLRI;
	} else if (MATCH("sari")) {
		return HX_SARI;
	} else if (MATCH("slti")) {
		return HX_SLTI;
	} else if (MATCH("sltiu")) {
		return HX_SLTUI;
	} else if (MATCH("sb")) {
		return HX_SB;
	} else if (MATCH("sq")) {
		return HX_SQ;
	} else if (MATCH("sh")) {
		return HX_SH;
	} else if (MATCH("sw")) {
		return HX_SW;
	} else if (MATCH("lb")) {
		return HX_LB;
	} else if (MATCH("lq")) {
		return HX_LQ;
	} else if (MATCH("lh")) {
		return HX_LH;
	} else if (MATCH("lw")) {
		return HX_LW;
	} else if (MATCH("lbu")) {
		return HX_LBU;
	} else if (MATCH("lqu")) {
		return HX_LQU;
	} else if (MATCH("lhu")) {
		return HX_LHU;
	} else if (MATCH("beq")) {
		return HX_BEQ;
	} else if (MATCH("bne")) {
		return HX_BNE;
	} else if (MATCH("blt")) {
		return HX_BLT;
	} else if (MATCH("bge")) {
		return HX_BGE;
	} else if (MATCH("jal")) {
		return HX_JAL;
	} else if (MATCH("jral")) {
		return HX_JRAL;
	} 
	/* Pseudo Instruction */
	else if (MATCH("nop")) {
		return HX_NOP;
	} else if (MATCH("mov")) {
		return HX_MOV;
	} else if (MATCH("jmp")) {
		return HX_JMP;
	}
	return HX_MNEMONIC_UNKNOWN;

}

#define BASE_OP(x) \
	((x << 2) | 0x3) \

u8 get_opcode(hx_mnemonic mnemonic)
{
	switch (mnemonic) {
		case HX_ADD:
		case HX_SUB:
		case HX_AND:
		case HX_OR:
		case HX_XOR:
		case HX_SLL:
		case HX_SLR:
		case HX_SAR:
		case HX_SLT:
		case HX_SLTU:
			return BASE_OP(0x00);

		case HX_ADDI:
		case HX_ANDI:
		case HX_ORI:
		case HX_XORI:
		case HX_SLLI:
		case HX_SLRI:
		case HX_SARI:
		case HX_SLTI:
		case HX_SLTUI:

		/* Pseudo */
		case HX_MOV:
		case HX_NOP:
			return BASE_OP(0x08);

		case HX_SB:
		case HX_SQ:
		case HX_SH:
		case HX_SW:
			return BASE_OP(0x01);

		case HX_LB:
		case HX_LQ:
		case HX_LH:
		case HX_LW:
		case HX_LBU:
		case HX_LQU:
		case HX_LHU:
			return BASE_OP(0x09);

		case HX_JAL:

		/* Pseudo */
		case HX_JMP:
			return BASE_OP(0x02);

		case HX_JRAL:
			return BASE_OP(0x0A);

		case HX_BEQ:
		case HX_BNE:
		case HX_BLT:
		case HX_BGE:
			return BASE_OP(0x10);

		default:
			return -1;
		
	}
}

u8 get_function(hx_mnemonic mnemonic)
{
	switch (mnemonic) {
		case HX_ADD:
		case HX_SUB:
		case HX_ADDI:
		case HX_JAL:
		case HX_JRAL:
		case HX_SB:
		case HX_LB:
		case HX_BEQ:
		case HX_NOP:
		case HX_MOV:
		case HX_JMP:
			return 0;

		case HX_AND:
		case HX_ANDI:
		case HX_SQ:
		case HX_LQ:
		case HX_BNE:
			return 1;

		case HX_OR:
		case HX_ORI:
		case HX_SH:
		case HX_LH:
		case HX_BLT:
			return 2;

		case HX_XOR:
		case HX_XORI:
		case HX_SW:
		case HX_LW:
		case HX_BGE:
			return 3;

		case HX_SLL:
		case HX_SLLI:
		case HX_LBU:
			return 4;

		case HX_SLR:
		case HX_SLRI:
		case HX_SAR:
		case HX_SARI:
		case HX_LQU:
			return 5;

		case HX_SLT:
		case HX_SLTI:
		case HX_LHU:
			return 6;

		case HX_SLTU:
		case HX_SLTUI:
			return 7;

		default:
			return -1;
	}
}

u8 get_modifier(hx_mnemonic mnemonic)
{
	switch (mnemonic) {
		case HX_ADD:
		case HX_AND:
		case HX_OR:
		case HX_XOR:
		case HX_SLL:
		case HX_SLR:
		case HX_SLT:
		case HX_SLTU:
			return 0;

		case HX_SUB:
		case HX_SAR:
			return 0x40;

		default:
			return -1;
	}
}
