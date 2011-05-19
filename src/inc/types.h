#ifndef TYPES_H
#define TYPES_H

#include "structures.h"

#define MAX_OPERATORS_BINARY	31
#define MAX_OPERATORS_UNARY		4
#define MAX_NATIVE_TYPES		10

#define ERROR t_type_native_void

#ifndef TYPES_C
	extern is_type_native operators_binary[MAX_OPERATORS_BINARY][MAX_NATIVE_TYPES-1][MAX_NATIVE_TYPES-1];
	extern is_type_native operators_unary[MAX_OPERATORS_UNARY][MAX_NATIVE_TYPES-1];
#endif

char *string_type_native(is_type_native* type);
char *string_type_decl(is_type_decl* type);
char *string_array_decl(is_array_decl* array);

bool type_native_assign_able(is_type_native native, is_type_decl* s_type);
bool type_type_assign_able(is_type_decl* s_type, is_type_decl* s_type2);
bool type_type_cast_able(is_type_decl* s_type, is_type_decl* s_type2);
bool type_var_init_assign_able(is_type_decl* type, int nDimensions, is_var_initializer* init);

is_type_decl* duplicate_type_decl(is_type_decl* type);

#endif
