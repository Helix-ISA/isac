#ifndef HX_INSTRUCTION_H
#define HX_INSTRUCTION_H

#include "isac/mnemonic.h"
#include "isac/operand.h"
#include "isac/types.h"

typedef struct hx_instruction hx_instruction;

HAPI b8 instruction_create(hx_instruction *instruction, hx_mnemonic mnemonic, u32 line, u32 operand_count, ...);

HAPI hx_mnemonic instruction_mnemonic(const hx_instruction *instruction);
HAPI u8 instruction_operand_count(const hx_instruction *instruction);
HAPI u8 instruction_operand_count_of(const hx_instruction *instruction, hx_operand_type operand_type);

void *instruction_get_operand(const hx_instruction *instruction, u8 position, hx_operand_type type);

#endif
