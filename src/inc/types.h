#ifndef TYPES_H
#define TYPES_H

#include "structures.h"

#define MAX_OPERATORS		36
#define MAX_NATIVE_TYPES	9

#define ERROR t_type_native_void

#ifndef TYPES_C
	extern is_type_native operators_native[MAX_OPERATORS][MAX_NATIVE_TYPES][MAX_NATIVE_TYPES];
#endif

bool type_long_like(is_type_decl* s_type);
bool type_bool_like(is_type_decl* s_type);

#endif
