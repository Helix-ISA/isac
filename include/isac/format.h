#ifndef HX_FORMAT_H
#define HX_FORMAT_H

#include "isac/instruction.h"
#include "isac/types.h"

HAPI u32 format_r_encode(const hx_instruction *instruction);
HAPI u32 format_i_encode(const hx_instruction *instruction);
HAPI u32 format_s_encode(const hx_instruction *instruction);
HAPI u32 format_b_encode(const hx_instruction *instruction);
HAPI u32 format_j_encode(const hx_instruction *instruction);

HAPI hx_instruction *format_r_decode(const u32 encoding);
HAPI hx_instruction *format_i_decode(const u32 encoding);
HAPI hx_instruction *format_s_decode(const u32 encoding);
HAPI hx_instruction *format_b_decode(const u32 encoding);
HAPI hx_instruction *format_j_decode(const u32 encoding);

#endif
