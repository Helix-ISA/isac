#include "isac/format.h"

#include "isac/instruction.h"
#include "isac/mnemonic.h"
#include "isac/operand.h"

#include <stddef.h>
#include <stdlib.h>

u32 format_r_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return 0;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	const hx_operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	const hx_operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	const hx_operand *rs2 = instruction_get_operand(instruction, 2, HX_REGISTER);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((operand_get_register(rd) & 0x1F) << 10) |
		((operand_get_register(rs1) & 0x1F) << 15) |
		((operand_get_register(rs2) & 0x1F) << 20) |
		((get_modifier(mnemonic) & 0x7F) << 25);

	return encoded;
}

u32 static encode_load(const hx_instruction *instruction)
{
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	const hx_operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	const hx_operand *mem = instruction_get_operand(instruction, 1, HX_MEMORY);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((operand_get_register(rd) & 0x1F) << 10) |
		((operand_get_memory_register(mem) & 0x1F) << 15) |
		((operand_get_memory_offset(mem) & 0x0FFF) << 20);

	return encoded;
}

u32 format_i_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return 0;
	
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

	const hx_operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	const hx_operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	const hx_operand *imm = instruction_get_operand(instruction, 2, HX_IMMEDIATE);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((operand_get_register(rd) & 0x1F) << 10) |
		((operand_get_register(rs1) & 0x1F) << 15) |
		((operand_get_immediate(imm) & 0x0FFF) << 20);

	return encoded;
}

u32 format_s_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return 0;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	const hx_operand *mem = instruction_get_operand(instruction, 0, HX_MEMORY);
	const hx_operand *rs2 = instruction_get_operand(instruction, 1, HX_REGISTER);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((operand_get_register(rs2) & 0x1F) << 10) |
		((operand_get_memory_register(mem) & 0x1F) << 15) |
		((operand_get_memory_offset(mem) & 0x0FFF) << 20);

	return encoded;
}

u32 format_b_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return 0;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	const hx_operand *rs2 = instruction_get_operand(instruction, 0, HX_REGISTER);
	const hx_operand *rs1 = instruction_get_operand(instruction, 1, HX_REGISTER);
	const hx_operand *symbol = instruction_get_operand(instruction, 2, HX_SYMBOL);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((operand_get_register(rs2) & 0x1F) << 10) |
		((operand_get_register(rs1) & 0x1F) << 15) |
		(((operand_get_symbol_address(symbol) >> 2) & 0x0FFF) << 20); // Divide by 4, store larger addresses

	return encoded;
}

u32 format_j_encode(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return 0;
	
	hx_mnemonic mnemonic = instruction_mnemonic(instruction);

	const hx_operand *rd = instruction_get_operand(instruction, 0, HX_REGISTER);
	const hx_operand *symbol = instruction_get_operand(instruction, 1, HX_SYMBOL);

	u32 encoded = get_opcode(mnemonic) |
		((get_function(mnemonic) & 0x07 ) << 7) |
		((operand_get_register(rd) & 0x1F) << 10) |
		(((operand_get_symbol_address(symbol) >> 2) & 0x1FFFF) << 15); // Divide by 4, store larger addresses

	return encoded;
}

static hx_mnemonic fetch_mnemonic(const u32 encoding)
{
	u8 opcode = encoding & 0x7F;
	u8 function = (encoding >> 7) & 0x3;
	u8 mod = (encoding >> 25) & 0x7F;

	return decode_mnemonic(opcode, function, mod);
}

hx_instruction *format_r_decode(const u32 encoding)
{
	hx_mnemonic mnemonic = fetch_mnemonic(encoding);
	u8 rd = (encoding >> 10) & 0x1F;
	u8 rs1 = (encoding >> 15) & 0x1F;
	u8 rs2 = (encoding >> 20) & 0x1F;

	return instruction_create(
			mnemonic,
			0,
			3,
			operand_create_register(rd),
			operand_create_register(rs1),
			operand_create_register(rs2)
	);
}

hx_instruction *format_i_decode(const u32 encoding)
{
	hx_mnemonic mnemonic = fetch_mnemonic(encoding);
	u8 rd = (encoding >> 10) & 0x1F;
	u8 rs1 = (encoding >> 15) & 0x1F;

	if (mnemonic == HX_JRAL) {
		s64 immediate = (s64)(encoding >> 18);
		if (immediate & (1 << 13)) // If top bit is set signed
			immediate |= ~0x3FFFLL; // Sign extend with the not of the 12 lowest bits
		return instruction_create(
				mnemonic,
				0,
				3,
				operand_create_register(rd),
				operand_create_register(rs1),
				operand_create_immediate(immediate)
		);
	} else {
		s64 immediate = (s64)(encoding >> 20);
		if (immediate & (1 < 11)) // If top bit is set signed
			immediate |= ~0xFFFLL; // Sign extend with the not of the 12 lowest bits
		return instruction_create(
				mnemonic,
				0,
				3,
				operand_create_register(rd),
				operand_create_register(rs1),
				operand_create_immediate(immediate)
		);
	}
}

hx_instruction *format_s_decode(const u32 encoding)
{
	hx_mnemonic mnemonic = fetch_mnemonic(encoding);
	u8 rs2 = (encoding >> 10) & 0x1F;
	u8 rs1 = (encoding >> 15) & 0x1F;
	s64 immediate = (s64)(encoding >> 20);
	if (immediate & (1 << 11))
		immediate |= ~0xFFFLL;

	return instruction_create(
			mnemonic,
			0,
			2,
			operand_create_memory(rs1, immediate),
			operand_create_register(rs2)
	);
}

hx_instruction *format_b_decode(const u32 encoding)
{
	hx_mnemonic mnemonic = fetch_mnemonic(encoding);
	u8 rs2 = (encoding >> 10) & 0x1F;
	u8 rs1 = (encoding >> 15) & 0x1F;
	s64 immediate = (s64)(encoding >> 18);
	if (immediate & (1 << 13))
		immediate |= ~0x3FFFLL;

	return instruction_create(
			mnemonic,
			0,
			3,
			operand_create_register(rs1),
			operand_create_register(rs2),
			operand_create_immediate(immediate)
	);
}

hx_instruction *format_j_decode(const u32 encoding)
{
	hx_mnemonic mnemonic = fetch_mnemonic(encoding);
	u8 rd = (encoding >> 10) & 0x1F;
	s64 immediate = (s64)(encoding >> 13);
	if (immediate & (1 << 16))
		immediate |= ~0x1FFFFLL;

	return instruction_create(
			mnemonic,
			0,
			2,
			operand_create_register(rd),
			operand_create_immediate(immediate)
	);
}
