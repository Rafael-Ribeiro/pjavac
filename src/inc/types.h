#ifndef TYPES_H
#define TYPES_H

#include "structures.h"

#define MAX_OPERATORS		36
#define MAX_NATIVE_TYPES	10

#define ERROR t_type_native_void

#ifndef TYPES_C
	extern is_type_native operators_native[MAX_OPERATORS][MAX_NATIVE_TYPES-1][MAX_NATIVE_TYPES-1];
#endif

char *string_type_native(is_type_native* type);
char *string_type_decl(is_type_decl* type);
char *string_array_decl(is_array_decl* array);


bool type_long_like(is_type_decl* s_type);
bool type_bool_like(is_type_decl* s_type);
bool type_cast_able(is_type_decl* s_type, is_type_decl* s_type2);

is_type_decl* duplicate_type_decl(is_type_decl* type);
#endif
