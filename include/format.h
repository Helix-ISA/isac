#ifndef HX_FORMAT_H
#define HX_FORMAT_H

#include "instruction.h"
#include "types.h"

HAPI u32 format_r_encode(const hx_instruction *instruction);
HAPI u32 format_i_encode(const hx_instruction *instruction);
HAPI u32 format_s_encode(const hx_instruction *instruction);
HAPI u32 format_b_encode(const hx_instruction *instruction);
HAPI u32 format_j_encode(const hx_instruction *instruction);

HAPI hx_instruction *format_r_decode(const u32 encoding);

#endif
