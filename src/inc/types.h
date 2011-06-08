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
	extern is_type_native operators_incr_op[MAX_NATIVE_TYPES-1];
#endif

char string_unary_operator(type_unary_op_operator operator);
char *string_incr_operator(type_incr_op operator);

char *string_assign_operator(type_assign_op operator);
char *string_binary_operator(type_binary_op operator);
char *string_type_native(is_type_native* type);
char *string_type_native_array(is_type_native type, int dims);
char *string_type_decl(is_type_decl* type);
char *string_array_decl(is_array_decl* array);

bool type_dims_empty_list_equal(is_dims_empty_list* dims1, is_dims_empty_list* dims2);
bool type_array_decl_equal(is_array_decl* array1, is_array_decl* array2);
bool type_type_object_equal(is_type_object* type1, is_type_object* type2);
bool type_type_equal(is_type_decl* s_type, is_type_decl* s_type2);

bool type_native_assign_able(is_type_native native, is_type_decl* s_type);
bool type_type_assign_able(is_type_decl* s_type, is_type_decl* s_type2);
bool type_type_cast_able(is_type_decl* s_type, is_type_decl* s_type2);
bool type_var_init_assign_able(is_type_decl* type, int nDimensions, is_var_initializer* init);

bool type_type_cast_able(is_type_decl* s_type, is_type_decl* s_type2);

is_type_decl* duplicate_type_decl(is_type_decl* type);
is_type_decl* new_type_decl_void();

#endif
