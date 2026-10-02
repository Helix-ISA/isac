#include "isac/format.h"

#include "isac/instruction.h"
#include "isac/mnemonic.h"
#include "isac/operand.h"

#include <stddef.h>
#include <stdlib.h>

union operand {
	u8 reg;
	u64 imm;

	struct {
		u8 reg;
		u64 offset;
	} memory;
	
	struct {
		const char *name;
		u32 name_length;
		u64 address;
	} symbol;
};

u32 format_r_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	union operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	union operand *rs2 = instruction_get_operand(instruction, 2, HX_REGISTER);

	if (rd == NULL || rs1 == NULL || rs2 == NULL) {
		free(rd);
		free(rs1);
		free(rs2);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((rd->reg & 0x1F) << 10) |
		((rs1->reg & 0x1F) << 15) |
		((rs2->reg & 0x1F) << 20) |
		((get_modifier(mnemonic) & 0x7F) << 25);

	free(rd);
	free(rs1);
	free(rs2);

	return encoded;
}

u32 static encode_load(const hx_instruction *instruction)
{
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	union operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *mem = instruction_get_operand(instruction, 1, HX_MEMORY);

	if (rd == NULL || mem == NULL) {
		free(rd);
		free(mem);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((rd->reg & 0x1F) << 10) |
		((mem->memory.reg & 0x1F) << 15) |
		((mem->memory.offset & 0x0FFF) << 20);

	free(rd);
	free(mem);

	return encoded;
}

u32 format_i_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	switch (mnemonic) {
		case HX_LB:
		case HX_LQ:
		case HX_LH:
		case HX_LW:
		case HX_LBU:
		case HX_LQU:
		case HX_LHU:
			return encode_load(instruction);

		default:
			break;
	}

	union operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	union operand *imm = instruction_get_operand(instruction, 2, HX_IMMEDIATE);

	if (rd == NULL || rs1 == NULL || imm == NULL) {
		free(rd);
		free(rs1);
		free(imm);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((rd->reg & 0x1F) << 10) |
		((rs1->reg & 0x1F) << 15) |
		((imm->reg & 0x0FFF) << 20);

	free(rd);
	free(rs1);
	free(imm);

	return encoded;
}

u32 format_s_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	union operand *mem = instruction_get_operand(instruction, 0, HX_MEMORY);
	union operand *rs2 = instruction_get_operand(instruction, 1, HX_REGISTER);

	if (mem == NULL || rs2 == NULL) {
		free(mem);
		free(rs2);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((rs2->reg & 0x1F) << 10) |
		((mem->memory.reg & 0x1F) << 15) |
		((mem->memory.offset & 0x0FFF) << 20);

	free(rs2);
	free(rs2);

	return encoded;
}

u32 format_b_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	union operand *rs2 = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	union operand *symbol = instruction_get_operand(instruction, 2, HX_SYMBOL);

	if (rs2 == NULL || rs1 == NULL || symbol == NULL) {
		free(rs2);
		free(rs1);
		free(symbol);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((rs2->reg & 0x1F) << 10) |
		((rs1->reg & 0x1F) << 15) |
		(((symbol->symbol.address >> 2) & 0x0FFF) << 20); // Divide by 4, store larger addresses

	free(rs2);
	free(rs1);
	free(symbol);

	return encoded;
}

u32 format_j_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	union operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *symbol = instruction_get_operand(instruction, 1, HX_SYMBOL);

	if (rd == NULL || symbol == NULL) {
		free(rd);
		free(symbol);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((rd->reg & 0x1F) << 10) |
		(((symbol->symbol.address >> 2) & 0x1FFFF) << 15); // Divide by 4, store larger addresses

	free(rd);
	free(symbol);

	return encoded;
}
