#include <stdio.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/symtab.h"
#include "inc/check.h"
#include "inc/types.h"

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
	/* TODO check operators */
	/* TODO: set type*/

	return errors;
}

int check_binary_op_operation(is_binary_op* node)
{
	int errors = 0;
	/* TODO check operators */
	/* TODO: set type*/
	return errors;
}

int check_break(is_break* node)
{
	int errors = 0;

	if (node->label)
		errors += check_label(node->label);

	return errors;
}

int check_class_def(is_class_def* node)
{
	int errors = 0;
	SYMBOL* symbol;
	
	symbol = scope_lookup(symtab, node->id->name);
	if (symbol)
	{
		errors++;
		pretty_error(node->line, "symbol %s is already defined (previous declaration was here: %d)", node->id->name, symbol->line);
	}

	scope_insert(symtab, symbol_new_class(node->id->name));

	symtab = scope_new(symtab);
	errors += check_class_stmt_list(node->body);
	symtab = scope_delete(symtab);

	return errors;
}

int check_class_stmt(is_class_stmt* node)
{
	int errors = 0;

	errors += check_class_stmt_scope(node->scope);
	errors += check_class_stmt_privacy(node->privacy);
	errors += check_member_stmt(node->stmt);

	return errors;
}
 
int check_class_stmt_list(is_class_stmt_list* node)
{
	int errors = 0;
	
	errors += check_class_stmt(node->node);
	errors += check_class_stmt_list(node->next);

	return errors;
}

/* TODO: check scope and privacy */
int check_class_stmt_privacy(is_class_stmt_privacy* node)
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

	if (node->label)
		errors += check_label(node->label);

	return errors;
}

int check_dims(is_dims* node)
{
	int errors = 0;

	errors += check_dims_sized_list(node->sized);
	errors += check_dims_empty_list(node->empty);

	return errors;
}

int check_dims_empty_list(is_dims_empty_list* val)
{
	/* nothing to do */
	return 0;
}

int check_dims_sized(is_dims_sized* node)
{
	int errors = 0;

	errors += check_expr(node);
	if (errors == 0)
	{
		if (!type_long_like(node->s_type))
		{
			errors++;
			pretty_error(node->line, "invalid array size (must be long like)");
		}
	}

	return errors;
}

int check_dims_sized_list(is_dims_sized_list* node)
{
	int errors = 0;

	if (node)
	{
		errors += check_dims_sized(node->node);
		errors += check_dims_sized_list(node->next);
	}

	return errors;
}

int check_do_while(is_do_while* node)
{
	int errors = 0;
	
	errors += check_expr(node->cond);
	if (errors == 0)
	{
		if (!type_bool_like(node->cond->s_type))
		{
			errors++;
			pretty_error(node->line, "invalid array condition (must be boolean)");
		}
	}

	/* FIXME:
		force an adition of a scope
		this makes do int a; while(i=0); int a; semantically valid while it should be syntactically invalid 
	*/
	symtab = scope_new(symtab);
	errors += check_stmt(node->body);
	symtab = scope_delete(symtab);
	
	return errors;
}
 
int check_expr(is_expr* node)
{
	char *typeA, *typeB; 
	int errors = 0;

	switch (node->type)
	{
		case t_expr_var:
			errors += check_var(node->data.var);
			node->s_type = node->data.var->s_type;
			break;

		case t_expr_new_op:
			errors += check_new_op(node->data.new_op);
			node->s_type = node->data.new_op->s_type;
			break;

		case t_expr_type_cast:
			errors += check_expr(node->data.type_cast.expr);
			errors += check_type_decl(node->data.type_cast.type);

			if (errors == 0)
			{
				if (!type_cast_able(node->data.type_cast.type, node->data.type_cast.expr->s_type))
				{
					errors++;
					typeA = string_type_decl(node->data.type_cast.type);
					typeB = string_type_decl(node->data.type_cast.expr->s_type);

					pretty_error(node->line, "invalid typecast from %s to %s", typeA, typeB);
					free(typeA); free(typeB);
				}
			}
			break;

		case t_expr_constant:
			break;

		case t_expr_func_call:
			break;

		case t_expr_operation:
			break;
	}

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

int check_label(is_id* node)
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

