#ifndef HX_OPERAND_H
#define HX_OPERAND_H

#include "types.h"

typedef enum {
	HX_REGISTER,
	HX_IMMEDIATE,
	HX_MEMORY,
	HX_LABEL,

	HX_OPERAND_UNKNOWN
} hx_operand_type;

typedef struct hx_operand hx_operand;

HAPI b8 operand_create_register(hx_operand *operand, u8 reg);
HAPI b8 operand_create_immediate(hx_operand *operand, u64 imm);
HAPI b8 operand_create_memory(hx_operand *operand, u8 reg, u64 imm);
HAPI b8 operand_create_label(hx_operand *operand, const char *text, u32 text_length);

HAPI hx_operand_type operand_get_type(const hx_operand *operand);

#endif
