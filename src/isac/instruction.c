#include "isac/instruction.h"

#include "isac/mnemonic.h"
#include "isac/operand.h"
#include "isac/types.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPERANDS 3

struct hx_operand {
	hx_operand_type type;

	union {
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
	} value;
};

struct hx_instruction {
	hx_mnemonic mnemonic;

	hx_operand operands[MAX_OPERANDS];
	u8 operand_count;

	u64 address;
};

hx_instruction *instruction_create(hx_mnemonic mnemonic, u64 address, u32 operand_count, ...)
{
	hx_instruction *instruction = malloc(sizeof(hx_instruction));
	if (instruction == NULL)
		return NULL;

	if (operand_count > MAX_OPERANDS)
		return failure;

	instruction->mnemonic = mnemonic;
	instruction->address = address;
	instruction->operand_count = operand_count;

	va_list args;
	va_start(args, operand_count);

	for (u8 i = 0; i < operand_count; i++) {
		hx_operand *operand = va_arg(args, hx_operand *);

		if (operand == NULL) {
			va_end(args);
			return failure;
		}

		instruction->operands[i] = *operand;
	}

	va_end(args);

	return instruction;
}

void instruction_free(hx_instruction *instruction)
{
	for (u8 i = 0; i < instruction->operand_count; i++) {
		operand_free(&instruction->operands[i]);
	}

	free(instruction);
}

hx_mnemonic instruction_mnemonic(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return HX_MNEMONIC_UNKNOWN;
	
	return instruction->mnemonic;
}

u64 get_instruction_address(const hx_instruction *instruction)
{
	return instruction->address;
}

u8 instruction_operand_count(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return -1;

	return instruction->operand_count;
}

u8 instruction_operand_count_of(const hx_instruction *instruction, hx_operand_type operand_type)
{
	u8 count = 0;
	for (u8 i = 0; i < instruction->operand_count; i++) {
		if (instruction->operands[i].type == operand_type)
			count++;
	}

	return count;
}

b8 instruction_operand_get_symbol(const hx_instruction *instruction, u32 operand_position, const char **out_name, u32 *out_name_length)
{
	if (instruction->operands[operand_position].type != HX_SYMBOL)
		return false;

	*out_name = instruction->operands[operand_position].value.symbol.name;
	*out_name_length = instruction->operands[operand_position].value.symbol.name_length;
	return true;
	

}

b8 instruction_operand_resolve_symbol(hx_instruction *instruction, u8 operand_position, u64 address)
{
	if (instruction->operands[operand_position].type != HX_SYMBOL)
		return failure;

	instruction->operands[operand_position].value.symbol.address = address;
	return success;
}

b8 instruction_operand_match_type(const hx_instruction *instruction, u8 operand_position, hx_operand_type type)
{
	return instruction->operands[operand_position].type == type;
}

void *instruction_get_operand(const hx_instruction *instruction, u8 position, hx_operand_type type)
{
	if (instruction == NULL)
		return NULL;

	if (instruction->operand_count - 1 < position)
		return NULL;

	if (instruction->operands[position].type != type)
		return NULL;

	union out {
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

	union out *p = malloc(sizeof(*p));
	if (p == NULL)
		return NULL;

	switch (type) {
		case HX_REGISTER:
			p->reg = instruction->operands[position].value.reg;
			return p;
		
		case HX_IMMEDIATE:
			p->imm = instruction->operands[position].value.imm;
			return p;

		case HX_MEMORY:
			p->memory.reg = instruction->operands[position].value.memory.reg;
			p->memory.offset = instruction->operands[position].value.memory.offset;
			return p;

		case HX_SYMBOL:
			p->symbol.name = instruction->operands[position].value.symbol.name;
			p->symbol.name_length = instruction->operands[position].value.symbol.name_length;
			p->symbol.address = instruction->operands[position].value.symbol.address;
			return p;

		default:
			return NULL;
	}
}
