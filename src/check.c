#include <stdio.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/symtab.h"
#include "inc/check.h"

extern SCOPE* symtab;

/*
	OPERATORS TABLE
*/

type_ a[MAX_OPERATORS][MAX_OPERANDS][MAX_OPERANDS]
/*
	t_assign_op_eq,
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




/* LEX */

int check_id(is_id* node)
{
	SYMBOL* symbol;

	symbol = symbolLookup(symtab, node->name);
	if (!symbol)
	{
		pretty_error(node->line, "undefined symbol %s", node->name);
		return 1;
	}

	return 0;
}

int check_constant(is_constant* node)
{
	return 0; /* syntax-validated */
}

/* YACC */
/* nodes */
int check_application(is_application* node)
{
	return check_class_def(node);
}

int check_array_decl(is_array_decl* node)
{
	int errors = 0;

	errors += check_type_object(node->type);
	errors += check_dims_empty_list(node->dims);

	return errors;
}

int check_assign_op(is_assign_op* node)
{
	int errors = 0;
	
	
	return errors;
}

int check_binary_op_operation(is_binary_op* node)
{
	int errors = 0;
	return errors;
}

int check_break(is_break* node)
{
	int errors = 0;
	return errors;
}

int check_class_def(is_class_def* node)
{
	int errors = 0;
	return errors;
}

int check_class_stmt(is_class_stmt* node)
{
	int errors = 0;
	return errors;
}
 
int check_class_stmt_list(is_class_stmt_list* node)
{
	int errors = 0;
	return errors;
}
 
int check_class_stmt_scope(is_class_stmt_scope* node)
{
	int errors = 0;
	return errors;
}
 
int check_continue(is_continue* node)
{
	int errors = 0;
	return errors;
}

int check_dims(is_dims* node)
{
	int errors = 0;
	return errors;
}

int check_dims_empty_list(is_dims_empty_list* val)
{
	int errors = 0;
	return errors;
}

int check_dims_sized(is_dims_sized* node)
{
	int errors = 0;
	return errors;
}

int check_dims_sized_list(is_dims_sized_list* node)
{
	int errors = 0;
	return errors;
}

int check_do_while(is_do_while* node)
{
	int errors = 0;
	return errors;
}
 
int check_expr(is_expr* node)
{
	int errors = 0;
	return errors;
}

int check_expr_list(is_expr_list* node)
{
	int errors = 0;
	return errors;
}

int check_expr_op(is_expr_op* node)
{
	int errors = 0;
	return errors;
}

int check_for(is_for* node)
{
	int errors = 0;
	return errors;
}

int check_for_cond(is_for_cond* node)
{
	int errors = 0;
	return errors;
}

int check_for_expr(is_for_expr* node)
{
	int errors = 0;
	return errors;
}
 
int check_for_expr_list(is_for_expr_list* node)
{
	int errors = 0;
	return errors;
}
 
int check_for_inc(is_for_inc* node)
{
	int errors = 0;
	return errors;
}

int check_for_init(is_for_init* node)
{
	int errors = 0;
	return errors;
}

int check_func_call(is_func_call* node)
{
	int errors = 0;
	return errors;
}

int check_func_call_arg_list(is_func_call_arg_list* node)
{
	int errors = 0;
	return errors;
}

int check_func_def(is_func_def* node)
{
	int errors = 0;
	return errors;
}

int check_func_def_arg(is_func_def_arg* node)
{
	int errors = 0;
	return errors;
}

int check_func_def_arg_list(is_func_def_arg_list* node)
{
	int errors = 0;
	return errors;
}

int check_func_def_args(is_func_def_args* node)
{
	int errors = 0;
	return errors;
}

int check_if(is_if* node)
{
	int errors = 0;
	return errors;
}

int check_incr_op(is_incr_op* node)
{
	int errors = 0;
	return errors;
}

int check_loop_stmt(is_loop_stmt* node)
{
	int errors = 0;
	return errors;
}
 
int check_member_stmt(is_member_stmt* node)
{
	int errors = 0;
	return errors;
}

int check_new_op(is_new_op* node)
{
	int errors = 0;
	return errors;
}

int check_return(is_return* node)
{
	int errors = 0;
	return errors;
}

int check_stmt(is_stmt* node)
{
	int errors = 0;
	return errors;
}

int check_stmt_list(is_stmt_list* node)
{
	int errors = 0;
	return errors;
}
 
int check_switch(is_switch* node)
{
	int errors = 0;
	return errors;
}

int check_switch_stmt(is_switch_stmt* node)
{
	int errors = 0;
	return errors;
}

int check_switch_stmt_list(is_switch_stmt_list* node)
{
	int errors = 0;
	return errors;
}

int check_ternary_op(is_ternary_op* node)
{
	int errors = 0;
	return errors;
}

int check_type_decl(is_type_decl* node)
{
	int errors = 0;
	return errors;
}

int check_type_object(is_type_object* node)
{
	int errors = 0;
	return errors;
}

int check_unary_op(is_unary_op* node)
{
	int errors = 0;
	return errors;
}

int check_var(is_var* node)
{
	int errors = 0;
	return errors;
}

int check_var_def(is_var_def* node)
{
	int errors = 0;
	return errors;
}

int check_var_def_list(is_var_def_list* node)
{
	int errors = 0;
	return errors;
}

int check_var_def_left(is_var_def_left* node)
{
	int errors = 0;
	return errors;
}

int check_var_defs(is_var_defs* node)
{
	int errors = 0;
	return errors;
}

int check_var_stmt(is_var_stmt* node)
{
	int errors = 0;
	return errors;
}

int check_var_initializer(is_var_initializer* node)
{
	int errors = 0;
	return errors;
}

int check_var_initializer_list(is_var_initializer_list* node)
{
	int errors = 0;
	return errors;
}

int check_while(is_while* node)
{
	int errors = 0;
	return errors;
}

