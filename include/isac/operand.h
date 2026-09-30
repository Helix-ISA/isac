#ifndef HX_OPERAND_H
#define HX_OPERAND_H

#include "isac/types.h"

typedef enum {
	HX_REGISTER,
	HX_IMMEDIATE,

	HX_OPERAND_UNKNOWN
} hx_operand_type;

typedef struct hx_operand hx_operand;

HAPI hx_operand *operand_create_register(u8 reg);
HAPI hx_operand *operand_create_immediate(u64 imm);

HAPI hx_operand_type operand_get_type(const hx_operand *operand);

#endif
