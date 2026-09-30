#include "isac/operand.h"
#include "isac/types.h"

#include <stddef.h>
#include <stdlib.h>

struct hx_operand {
	hx_operand_type type;

	union {
		u8 reg;
		u64 imm;
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

hx_operand *operand_create_immediate(u64 imm)
{
	hx_operand *operand = malloc(sizeof(hx_operand));
	if (operand == NULL)
		return NULL;

	operand->type = HX_IMMEDIATE;
	operand->value.imm = imm;

	return operand;
}

HAPI hx_operand_type operand_get_type(const hx_operand *operand)
{
	if (operand == NULL)
		return HX_OPERAND_UNKNOWN;

	return operand->type;
}
