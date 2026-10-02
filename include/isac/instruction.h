#ifndef HX_INSTRUCTION_H
#define HX_INSTRUCTION_H

#include "isac/mnemonic.h"
#include "isac/operand.h"
#include "isac/types.h"

typedef struct hx_instruction hx_instruction;

HAPI hx_instruction *instruction_create(hx_mnemonic mnemonic, u64 address, u32 operand_count, ...);
HAPI void instruction_free(hx_instruction *instruction);
HAPI u64 get_instruction_address(const hx_instruction *instruction);

HAPI hx_mnemonic instruction_mnemonic(const hx_instruction *instruction);
HAPI u8 instruction_operand_count(const hx_instruction *instruction);
HAPI u8 instruction_operand_count_of(const hx_instruction *instruction, hx_operand_type operand_type);

HAPI b8 instruction_operand_get_symbol(const hx_instruction *instruction, u32 operand_position, const char **out_name, u32 *out_name_length);
HAPI b8 instruction_operand_resolve_symbol(hx_instruction *instruction, u8 operand_position, u64 address);
HAPI b8 instruction_operand_match_type(const hx_instruction *instruction, u8 operand_position, hx_operand_type type);

void *instruction_get_operand(const hx_instruction *instruction, u8 position, hx_operand_type type);


#endif
