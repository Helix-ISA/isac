#include "mnemonic.h"
#include <string.h>

hx_mnemonic get_mnemonic(const char *string)
{
	if (strcmp(string, "add") == 0) {
		return HX_ADD;
	} else if (strcmp(string, "sub") == 0) {
		return HX_SUB;
	} else if (strcmp(string, "and") == 0) {
		return HX_AND;
	} else if (strcmp(string, "or") == 0) {
		return HX_OR;
	} else if (strcmp(string, "xor") == 0) {
		return HX_XOR;
	} else if (strcmp(string, "sll") == 0) {
		return HX_SLL;
	} else if (strcmp(string, "slr") == 0) {
		return HX_SLR;
	} else if (strcmp(string, "sar") == 0) {
		return HX_SAR;
	} else if (strcmp(string, "slt") == 0) {
		return HX_SLT;
	} else if (strcmp(string, "sltu") == 0) {
		return HX_SLTU;
	} else if (strcmp(string, "addi") == 0) {
		return HX_ADDI;
	} else if (strcmp(string, "andi") == 0) {
		return HX_ANDI;
	} else if (strcmp(string, "ori") == 0) {
		return HX_ORI;
	} else if (strcmp(string, "xori") == 0) {
		return HX_XORI;
	} else if (strcmp(string, "slli") == 0) {
		return HX_SLLI;
	} else if (strcmp(string, "slri") == 0) {
		return HX_SLRI;
	} else if (strcmp(string, "sari") == 0) {
		return HX_SARI;
	} else if (strcmp(string, "slti") == 0) {
		return HX_SLTI;
	} else if (strcmp(string, "sltiu") == 0) {
		return HX_SLTUI;
	} else if (strcmp(string, "sb") == 0) {
		return HX_SB;
	} else if (strcmp(string, "sq") == 0) {
		return HX_SQ;
	} else if (strcmp(string, "sh") == 0) {
		return HX_SH;
	} else if (strcmp(string, "sw") == 0) {
		return HX_SW;
	} else if (strcmp(string, "lb") == 0) {
		return HX_LB;
	} else if (strcmp(string, "lq") == 0) {
		return HX_LQ;
	} else if (strcmp(string, "lh") == 0) {
		return HX_LH;
	} else if (strcmp(string, "lw") == 0) {
		return HX_LW;
	} else if (strcmp(string, "lbu") == 0) {
		return HX_LBU;
	} else if (strcmp(string, "lqu") == 0) {
		return HX_LQU;
	} else if (strcmp(string, "lhu") == 0) {
		return HX_LHU;
	} else if (strcmp(string, "beq") == 0) {
		return HX_BEQ;
	} else if (strcmp(string, "bne") == 0) {
		return HX_BNE;
	} else if (strcmp(string, "blt") == 0) {
		return HX_BLT;
	} else if (strcmp(string, "bge") == 0) {
		return HX_BGE;
	} else if (strcmp(string, "jal") == 0) {
		return HX_JAL;
	} else if (strcmp(string, "jral") == 0) {
		return HX_JRAL;
	} 
	/* Pseudo Instruction */
	else if (strcmp(string, "nop") == 0) {
		return HX_NOP;
	} else if (strcmp(string, "mov") == 0) {
		return HX_MOV;
	} else if (strcmp(string, "jmp") == 0) {
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
