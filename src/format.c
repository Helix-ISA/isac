#include "format.h"

#include "instruction.h"
#include "mnemonic.h"
#include "operand.h"

#include <stddef.h>

union operand {
	u8 reg;
	u64 imm;

	struct {
		u8 reg;
		u64 offset;
	} memory;

	struct {
		const char *text;
		u32 text_length;
	} label;
};

u32 format_r_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		(((((union operand *)instruction_get_operand(instruction, 0, HX_REGISTER))->reg) << 10) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 1, HX_REGISTER))->reg) << 15) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 2, HX_REGISTER))->reg) << 20) & 0x1F) |
		((get_modifier(mnemonic) << 25) & 0x7F);

	return encoded;
}

u32 format_i_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		(((((union operand *)instruction_get_operand(instruction, 0, HX_REGISTER))->reg) << 10) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 1, HX_REGISTER))->reg) << 15) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 2, HX_IMMEDIATE))->imm) << 20) & 0x0FFF);

	return encoded;
}

u32 format_s_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	/* Swap operands 0 and 1, since rs2 is in rd location */
	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		(((((union operand *)instruction_get_operand(instruction, 1, HX_REGISTER))->reg) << 10) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 0, HX_REGISTER))->reg) << 15) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 2, HX_IMMEDIATE))->imm) << 20) & 0x0FFF);

	return encoded;
}

/* TODO: Two pass assembler, first pass operand[2] is a label, second pass we
 * resolve that labels address and change the instructions operand[2] to an
 * immediate that points PC relative to label
 */
u32 format_b_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	/* Swap operands 0 and 1, since rs2 is in rd location */
	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		(((((union operand *)instruction_get_operand(instruction, 1, HX_REGISTER))->reg) << 10) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 0, HX_REGISTER))->reg) << 15) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 2, HX_IMMEDIATE))->imm >> 2) << 20) & 0x0FFF); // Divide by 4, store larger addresses

	return encoded;
}

u32 format_j_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) << 7) & 0x07) |
		(((((union operand *)instruction_get_operand(instruction, 0, HX_REGISTER))->reg) << 10) & 0x1F) |
		(((((union operand *)instruction_get_operand(instruction, 2, HX_IMMEDIATE))->imm >> 2) << 15) & 0x1FFFF); // Divide by 4, store larger addresses

	return encoded;
}
