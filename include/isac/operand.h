#ifndef HX_OPERAND_H
#define HX_OPERAND_H

#include "isac/types.h"

typedef enum {
	HX_REGISTER,
	HX_IMMEDIATE,
	HX_MEMORY,
	HX_SYMBOL,

	HX_OPERAND_UNKNOWN
} hx_operand_type;

typedef struct hx_operand hx_operand;

HAPI hx_operand *operand_create_register(u8 reg);
HAPI hx_operand *operand_create_immediate(s64 imm);
HAPI hx_operand *operand_create_memory(u8 reg, u64 offset);
HAPI hx_operand *operand_create_symbol(const char *symbol_name, u32 symbol_name_length);

HAPI u8 operand_get_register(const hx_operand *operand);
HAPI s64 operand_get_immediate(const hx_operand *operand);
HAPI u8 operand_get_memory_register(const hx_operand *operand);
HAPI s64 operand_get_memory_offset(const hx_operand *operand);
HAPI s64 operand_get_symbol_address(const hx_operand *operand);

HAPI void operand_free(hx_operand *operand);

HAPI hx_operand_type operand_get_type(const hx_operand *operand);

#endif
