#include "isac/format.h"

#include "isac/instruction.h"
#include "isac/mnemonic.h"
#include "isac/operand.h"

#include <stddef.h>
#include <stdlib.h>

union operand {
	u8 reg;
	u64 imm;
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
		((get_function(mnemonic) << 7) & 0x07) |
		((rd->reg << 10) & 0x1F) |
		((rs1->reg << 15) & 0x1F) |
		((rs2->reg << 20) & 0x1F) |
		((get_modifier(mnemonic) << 25) & 0x7F);

	free(rd);
	free(rs1);
	free(rs2);

	return encoded;
}

u32 format_i_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

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
		((get_function(mnemonic) << 7) & 0x07) |
		((rd->reg << 10) & 0x1F) |
		((rs1->reg << 15) & 0x1F) |
		((imm->reg << 20) & 0x0FFF);

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

	union operand *rs2 = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	union operand *imm = instruction_get_operand(instruction, 2, HX_IMMEDIATE);

	if (rs2 == NULL || rs1 == NULL || imm == NULL) {
		free(rs2);
		free(rs1);
		free(imm);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		((rs2->reg << 10) & 0x1F) |
		((rs1->reg<< 15) & 0x1F) |
		((imm->imm << 20) & 0x0FFF);

	free(rs2);
	free(rs1);
	free(imm);

	return encoded;
}

u32 format_b_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	union operand *rs2 = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	union operand *imm = instruction_get_operand(instruction, 2, HX_IMMEDIATE);

	if (rs2 == NULL || rs1 == NULL || imm == NULL) {
		free(rs2);
		free(rs1);
		free(imm);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		((rs2->reg << 10) & 0x1F) |
		((rs1->reg<< 15) & 0x1F) |
		(((imm->imm >> 2) << 20) & 0x0FFF); // Divide by 4, store larger addresses

	free(rs2);
	free(rs1);
	free(imm);

	return encoded;
}

u32 format_j_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	union operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	union operand *imm = instruction_get_operand(instruction, 1, HX_IMMEDIATE);

	if (rd == NULL || imm == NULL) {
		free(rd);
		free(imm);
		return -1;
	}

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		((rd->reg<< 10) & 0x1F) |
		(((imm->imm >> 2) << 15) & 0x1FFFF); // Divide by 4, store larger addresses

	free(rd);
	free(imm);

	return encoded;
}
