#pragma once

#include "definitions.h"
#include "pi_exports.h"

typedef char const * cstring;

void PRIMEIDEAL_EXPORT output_newline();

void PRIMEIDEAL_EXPORT output_text(cstring const message);

void PRIMEIDEAL_EXPORT output_integer(integer number);

void PRIMEIDEAL_EXPORT output_line(cstring const message);
