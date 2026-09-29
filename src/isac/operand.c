#include "operand.h"
#include "types.h"

#include <stddef.h>

struct hx_operand {
	hx_operand_type type;

	union {
		u8 reg;
		u64 imm;
	} value;
};

b8 operand_create_register(hx_operand *operand, u8 reg)
{
	if (operand == NULL)
		return failure;

	operand->type = HX_REGISTER;
	operand->value.reg = reg;

	return success;
}

b8 operand_create_immediate(hx_operand *operand, u64 imm)
{
	if (operand == NULL)
		return failure;

	operand->type = HX_IMMEDIATE;
	operand->value.imm = imm;

	return success;
}

HAPI hx_operand_type operand_get_type(const hx_operand *operand)
{
	if (operand == NULL)
		return HX_OPERAND_UNKNOWN;

	return operand->type;
}
