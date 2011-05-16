#include <stdio.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/symtab.h"
#include "inc/check.h"

extern SCOPE* symtab;

/* LEX */

int check_id(is_id* node)
{
	SYMBOL* symbol;

	symbol = scope_lookup(symtab, node->name);
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

