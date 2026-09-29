#include "instruction.h"

#include "mnemonic.h"
#include "operand.h"
#include "types.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX_OPERANDS 3

struct hx_operand {
	hx_operand_type type;

	union {
		u8 reg;
		u64 imm;
	} value;
};

struct hx_instruction {
	hx_mnemonic mnemonic;

	hx_operand operands[MAX_OPERANDS];
	u8 operand_count;

	u32 line;
};

b8 instruction_create(hx_instruction *instruction, hx_mnemonic mnemonic, u32 line, u32 operand_count, ...)
{
	if (instruction == NULL)
		return failure;

	if (operand_count > MAX_OPERANDS)
		return failure;

	instruction->mnemonic = mnemonic;
	instruction->line = line;
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

	return success;
}

hx_mnemonic instruction_mnemonic(const hx_instruction *instruction)
{
	if (instruction == NULL)
		return HX_MNEMONIC_UNKNOWN;
	
	return instruction->mnemonic;
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

		default:
			return NULL;
	}
}
