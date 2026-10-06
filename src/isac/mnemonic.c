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

hx_mnemonic decode_mnemonic(u8 opcode, u8 function, u8 mod)
{
	u8 op = (opcode >> 2) & 0x1F;
	switch (op) {
		case 0x0:
			switch (function) {
				case 0x0:
					if (mod == 0x40)
						return HX_SUB;
					else
					 	return HX_ADD;
					break;
				case 0x1:
					return HX_AND;
					break;
				case 0x2:
					return HX_OR;
					break;
				case 0x3:
					return HX_XOR;
					break;
				case 0x4:
					return HX_SLL;
					break;
				case 0x5:
					if (mod == 0x40)
						return HX_SAR;
					else
					 	return HX_SLR;
					break;
				case 0x6:
					return HX_SLT;
					break;
				case 0x7:
					return HX_SLTU;
					break;
				default:
					return HX_MNEMONIC_UNKNOWN;
			}
			break;
		case 0x08:
			switch (function) {
				case 0x0:
					return HX_ADDI;
					break;
				case 0x1:
					return HX_ANDI;
					break;
				case 0x2:
					return HX_ORI;
					break;
				case 0x3:
					return HX_XORI;
					break;
				case 0x4:
					return HX_SLLI;
					break;
				case 0x5:
					if (mod == 0x20)
						return HX_SARI;
					else
					 	return HX_SLRI;
					break;
				case 0x6:
					return HX_SLTI;
					break;
				case 0x7:
					return HX_SLTUI;
					break;
				default:
					return HX_MNEMONIC_UNKNOWN;
			}
			break;
		case 0x01:
			switch (function) {
				case 0x0:
					return HX_SB;
					break;
				case 0x1:
					return HX_SQ;
					break;
				case 0x2:
					return HX_SH;
					break;
				case 0x3:
					return HX_SW;
					break;
				case 0x4:
					break;
				case 0x5:
					break;
				case 0x6:
					break;
				case 0x7:
					break;
				default:
					return HX_MNEMONIC_UNKNOWN;
			}
			break;
		case 0x09:
			switch (function) {
				case 0x0:
					return HX_LB;
					break;
				case 0x1:
					return HX_LQ;
					break;
				case 0x2:
					return HX_LH;
					break;
				case 0x3:
					return HX_LW;
					break;
				case 0x4:
					return HX_LBU;
					break;
				case 0x5:
					return HX_LQU;
					break;
				case 0x6:
					return HX_LHU;
					break;
				case 0x7:
					break;
				default:
					return HX_MNEMONIC_UNKNOWN;
			}
			break;
		case 0x02:
			switch (function) {
				case 0x0:
					return HX_JAL;
					break;
				case 0x1:
					break;
				case 0x2:
					break;
				case 0x3:
					break;
				case 0x4:
					break;
				case 0x5:
					break;
				case 0x6:
					break;
				case 0x7:
					break;
				default:
					return HX_MNEMONIC_UNKNOWN;
			}
			break;
		case 0x10:
			switch (function) {
				case 0x0:
					return HX_BEQ;
					break;
				case 0x1:
					return HX_BNE;
					break;
				case 0x2:
					return HX_BLT;
					break;
				case 0x3:
					return HX_BGE;
					break;
				case 0x4:
					break;
				case 0x5:
					break;
				case 0x6:
					break;
				case 0x7:
					break;
				default:
					return HX_MNEMONIC_UNKNOWN;
			}
			break;
		case 0x0A:
			switch (function) {
				case 0x0:
					return HX_JRAL;
					break;
				case 0x1:
					break;
				case 0x2:
					break;
				case 0x3:
					break;
				case 0x4:
					break;
				case 0x5:
					break;
				case 0x6:
					break;
				case 0x7:
					break;
				default:
					return HX_MNEMONIC_UNKNOWN;
			}
			break;
		default:
			return HX_MNEMONIC_UNKNOWN;
	}

	return HX_MNEMONIC_UNKNOWN;
}

const char *mnemonic_string(hx_mnemonic mnemonic)
{
	switch (mnemonic) {
		case HX_ADD:  return "ADD";
		case HX_SUB:  return "SUB";
		case HX_AND:  return "AND";
		case HX_OR:   return "OR";
		case HX_XOR:  return "XOR";
		case HX_SLL:  return "SLL";
		case HX_SLR:  return "SLR";
		case HX_SAR:  return "SAR";
		case HX_SLT:  return "SLT";
		case HX_SLTU: return "SLTU";

		case HX_ADDI:  return "ADDI";
		case HX_ANDI:  return "ANDI";
		case HX_ORI:   return "ORI";
		case HX_XORI:  return "XORI";
		case HX_SLLI:  return "SLLI";
		case HX_SLRI:  return "SLRI";
		case HX_SARI:  return "SARI";
		case HX_SLTI:  return "SLTI";
		case HX_SLTUI: return "SLTUI";

		case HX_SB: return "SB";
		case HX_SQ: return "SQ";
		case HX_SH: return "SH";
		case HX_SW: return "SW";

		case HX_LB:  return "LB";
		case HX_LQ:  return "LQ";
		case HX_LH:  return "LH";
		case HX_LW:  return "LW";
		case HX_LBU: return "LBU";
		case HX_LQU: return "LQU";
		case HX_LHU: return "LHU";

		case HX_BEQ: return "BEQ";
		case HX_BNE: return "BNE";
		case HX_BLT: return "BLT";
		case HX_BGE: return "BGE";

		case HX_JAL:  return "JAL";
		case HX_JRAL: return "JRAL";

		case HX_NOP: return "NOP";
		case HX_MOV: return "MOV";
		case HX_JMP: return "JMP";

		case HX_MNEMONIC_UNKNOWN:
		default:
			return "UNKNOWN";
	}
}
