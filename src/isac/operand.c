#include "isac/operand.h"
#include "isac/types.h"

#include <stddef.h>
#include <stdlib.h>

struct hx_operand {
	hx_operand_type type;

	union {
		u8 reg;
		s64 imm;

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

hx_operand *operand_create_register(u8 reg)
{
	hx_operand *operand = malloc(sizeof(hx_operand));
	if (operand == NULL)
		return NULL;

	operand->type = HX_REGISTER;
	operand->value.reg = reg;

	return operand;
}

hx_operand *operand_create_immediate(s64 imm)
{
	hx_operand *operand = malloc(sizeof(hx_operand));
	if (operand == NULL)
		return NULL;

	operand->type = HX_IMMEDIATE;
	operand->value.imm = imm;

	return operand;
}

hx_operand *operand_create_memory(u8 reg, u64 offset)
{
	hx_operand *operand = malloc(sizeof(hx_operand));
	if (operand == NULL)
		return NULL;

	operand->type = HX_MEMORY;
	operand->value.memory.reg = reg;
	operand->value.memory.offset = offset;

	return operand;
}

hx_operand *operand_create_symbol(const char *symbol_name, u32 symbol_name_length)
{
	hx_operand *operand = malloc(sizeof(hx_operand));
	if (operand == NULL)
		return NULL;

	operand->type = HX_SYMBOL;
	operand->value.symbol.name = symbol_name;
	operand->value.symbol.name_length = symbol_name_length;

	return operand;
}

void operand_free(hx_operand *operand)
{
	free(operand);
}

hx_operand_type operand_get_type(const hx_operand *operand)
{
	if (operand == NULL)
		return HX_OPERAND_UNKNOWN;

	return operand->type;
}

u8 operand_get_register(const hx_operand *operand)
{
	return operand->value.reg;
}

s64 operand_get_immediate(const hx_operand *operand)
{
	return operand->value.imm;
}

u8 operand_get_memory_register(const hx_operand *operand)
{
	return operand->value.memory.reg;
}

s64 operand_get_memory_offset(const hx_operand *operand)
{
	return operand->value.memory.offset;
}

s64 operand_get_symbol_address(const hx_operand *operand)
{
	return operand->value.symbol.address;
}
