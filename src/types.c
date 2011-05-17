#define TYPES_C

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/types.h"

is_type_native operators_native[MAX_OPERATORS][MAX_NATIVE_TYPES][MAX_NATIVE_TYPES] =
{
	/* t_assign_op_eq (=) */
	{
		/*					bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- second operand */
		/*	bool =		*/	{	t_type_native_bool	, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte =		*/	{	ERROR				, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, ERROR					},
		/*	char =		*/	{	ERROR				, t_type_native_char	, t_type_native_char	, ERROR					, ERROR					, t_type_native_char	, t_type_native_char	, t_type_native_char	, ERROR					},
		/*	double =	*/	{	ERROR				, ERROR					, ERROR					, t_type_native_double	, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}, /* TODO FROM HERE (inclusive)! */
		/*	float =		*/	{	ERROR				, ERROR					, ERROR					, ERROR					, t_type_native_float	, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int =		*/	{	ERROR				, ERROR					, ERROR					, ERROR					, ERROR					, t_type_native_int		, ERROR					, ERROR					, ERROR					},
		/*	long =		*/	{	ERROR				, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, t_type_native_long	, ERROR					, ERROR					},
		/*	short =		*/	{	ERROR				, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, t_type_native_short	, ERROR					},
		/*	String =	*/	{	ERROR				, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, t_type_native_string	}
	}
};

/*
	OPERATORS TABLE ELEMENTS

	t_assign_op_eq, <- pseudo-checked
	t_assign_op_shift_r_eq,
	t_assign_op_shift_l_eq,
	t_assign_op_add_eq,
	t_assign_op_sub_eq,
	t_assign_op_mul_eq,
	t_assign_op_div_eq,
	t_assign_op_mod_eq,
	t_assign_op_and_eq,
	t_assign_op_xor_eq,
	t_assign_op_or_eq

	t_binary_op_add,
	t_binary_op_sub,
	t_binary_op_mul,
	t_binary_op_div,
	t_binary_op_mod,
	t_binary_op_and,
	t_binary_op_or,
	t_binary_op_xor,
	t_binary_op_shift_r,
	t_binary_op_shift_l,
	t_binary_op_logic_and,
	t_binary_op_logic_or,
	t_binary_op_eq,
	t_binary_op_ne,
	t_binary_op_l,
	t_binary_op_g,
	t_binary_op_le,
	t_binary_op_ge,
	t_binary_op_eq3,
	t_binary_op_ne3,
	t_binary_op_assign

	t_unary_op_operator_plus,
	t_unary_op_operator_minus,
	t_unary_op_operator_not,
	t_unary_op_operator_bin_not


	t_type_native_bool,
	t_type_native_byte,
	t_type_native_char,
	t_type_native_double,
	t_type_native_float,
	t_type_native_int,
	t_type_native_long,
	t_type_native_short,
	t_type_native_string,
	t_type_native_void
*/


char *string_type_native(is_type_native* type)
{
	char strings[][8] = { "boolean", "byte", "char", "double", "float", "int", "long", "short", "string", "void"};
	return __strdup(strings[*type]);
}

char *string_type_decl(is_type_decl* type)
{
	if (type->type != t_type_decl_type_object)
		return string_type_native(&type->data.type_object->type);

	return string_array_decl(type->data.array);
}

char *string_array_decl(is_array_decl* array)
{
	char *native, *val;
	int size, i;

	native = string_type_native(&array->type->type);
	size = strlen(native) + 2*(array->dims->size)+1;

	val = (char*)malloc(sizeof(char)*size);
	strcpy(val, native); 
	
	for (i = 0; i < array->dims->size; i++)
		strcat(val, "[]");

	free(native);
	return val;
}

bool type_long_like(is_type_decl* s_type)
{
	if (s_type->type != t_type_decl_type_object)
		return false;

	return operators_native[t_assign_op_eq][t_type_native_long][s_type->data.type_object->type] != ERROR;
}

bool type_bool_like(is_type_decl* s_type)
{
	if (s_type->type != t_type_decl_type_object)
		return false;

	return operators_native[t_assign_op_eq][t_type_native_bool][s_type->data.type_object->type] != ERROR;
}

bool type_cast_able(is_type_decl* s_type, is_type_decl* s_type2)
{
	/*
		FIXME:
		this is invalid if we allow objects:
		e.g. 	Integer b[] = (Integer[])(new Object[1]); is valid BUT
				int b[] = (float[])(new int[1]) is NOT
	*/
	if (s_type->type == t_type_decl_array_decl)
		return false;

	if ((s_type->data.type_object->type == t_type_native_bool || s_type->data.type_object->type == t_type_native_string)
		&& s_type->data.type_object->type != s_type2->data.type_object->type)
		return false;

	return true;
}
