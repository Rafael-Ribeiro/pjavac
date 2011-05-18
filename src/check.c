#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/symtab.h"
#include "inc/check.h"
#include "inc/types.h"
#include "inc/insert.h"
#include "inc/duplicate.h"

/* LEX */
/*
	TODO: used?
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
*/
int check_constant(is_constant* node)
{
	switch (node->type)
	{
		case t_constant_bool:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_bool));
		break;

		case t_constant_long:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_long));
		break;

		case t_constant_double:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_double));
		break;

		case t_constant_char:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_char));
		break;

		case t_constant_string:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_string));
		break;
	}

	return 0;
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
	char* typeA, *typeB;
	is_type_native type;

	check_var(node->var);
	check_expr(node->expr);

	if (errors == 0)
	{
		switch (node->type)
		{
			case t_assign_op_eq:
				if (!type_type_assign_able(node->var->s_type, node->expr->s_type))
				{
					errors++;
					pretty_error(node->line, "invalid assignment between %s and %s",
						typeA = string_type_decl(node->var->s_type),
						typeB = string_type_decl(node->expr->s_type)
					);
					free(typeA);
					free(typeB);
				}
			break;

			default:
				if (node->var->s_type->type == t_type_decl_array_decl || node->expr->s_type->type == t_type_decl_array_decl)
				{
					errors++;
					pretty_error(node->line, "assignment operations are invalid between array types");
				} else
				{
					type = operators_binary[node->type][node->var->s_type->data.type_object->type][node->expr->s_type->data.type_object->type];
					if (type == ERROR)
					{
						errors++;
						pretty_error(node->line, "assignment operation invalid between %s and %s",
							typeA = string_type_decl(node->var->s_type),
							typeB = string_type_decl(node->expr->s_type)
						);
						free(typeA);
						free(typeB);
					}
				}
			break;
		}
	}

	if (errors == 0)
		node->s_type = duplicate_type_decl(node->s_type);

	return errors;
}

int check_binary_op(is_binary_op* node)
{
	int errors = 0;
	char *typeA, *typeB;
	is_type_native type;

	switch (node->type)
	{
		case t_binary_op_assign:
			errors += check_assign_op(node->data.assign);
			node->s_type = duplicate_type_decl(node->data.assign->s_type);
		break;

		default:
			errors += check_expr(node->data.operands.left);
			errors += check_expr(node->data.operands.right);

			if (node->data.operands.left->s_type->type == t_type_decl_array_decl ||
				node->data.operands.right->s_type->type == t_type_decl_array_decl)
			{
				errors++;
				pretty_error(node->line, "binary operations are invalid between array types");
			} else
			{
				type = operators_binary[node->type][node->data.operands.left->s_type->data.type_object->type][node->data.operands.right->s_type->data.type_object->type];
				if (type == ERROR)
				{
					errors++;
					pretty_error(node->line, "binary operation invalid between %s and %s",
						typeA = string_type_decl(node->data.operands.left->s_type),
						typeB = string_type_decl(node->data.operands.right->s_type)
					);
					free(typeA);
					free(typeB);
				}
			}

			/* only valid for objects not arrays*/
			if (errors == 0)
				node->s_type->type = type;
		break;
	}
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

	symbol = scope_lookup(symtab, node->id->name, t_symbol_class);
	if (symbol)
	{
		errors++;
		pretty_error(node->line, "class %s is already defined (previous declaration was here: %d)", node->id->name, symbol->line);
	} else
		scope_insert(symtab, symbol = symbol_new_class(node->id->name, node->line));

	node->scope = scope_new(symbol, true);

	/*
		FIXME:
		this should be in application and not in class def,
		because theoretically class should be able to access other classes
	*/
	scope_push(node->scope);
		errors += check_class_stmt_list(node->body, true); 
		errors += check_class_stmt_list(node->body, false);
	scope_pop();

	return errors;
}

int check_class_stmt(is_class_stmt* node, bool first_pass)
{
	int errors = 0;

	errors += check_class_stmt_scope(node->scope);
	errors += check_class_stmt_privacy(node->privacy);
	errors += check_member_stmt(node->stmt, first_pass);

	return errors;
}
 
int check_class_stmt_list(is_class_stmt_list* node, bool first_pass)
{
	int errors = 0;
	
	if (node)
	{
		errors += check_class_stmt(node->node, first_pass);
		errors += check_class_stmt_list(node->next, first_pass);
	}

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
		if (!type_native_assign_able(t_type_native_int, node->s_type))
		{
			errors++;
			pretty_error(node->line, "invalid array size (must be convertible to int)");
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
		
		if (node->next)
			node->length = node->next->length + 1;
		else
			node->length = 1;

	}

	return errors;
}

int check_do_while(is_do_while* node)
{
	int errors = 0;
	
	/* FIXME:
		force an addition of a scope
		this makes do int a; while(i == 0); int a; semantically valid while it should be syntactically invalid 
	*/
	node->scope = scope_new(NULL, false);
	scope_push(node->scope);
		errors += check_stmt(node->body);
	scope_pop();

	errors += check_expr(node->cond);
	if (errors == 0)
	{
		if (!type_native_assign_able(t_type_native_bool, node->cond->s_type))
		{
			errors++;
			pretty_error(node->line, "invalid do..while condition (must be boolean)");
		}
	}
	
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
			node->s_type = duplicate_type_decl(node->data.var->s_type);

			if (errors == 0)
			{
	
				if (!node->data.var->initialized)
				{
					errors++;
					pretty_error(node->line, "variable used without being initialized");
				}
			}
		break;

		case t_expr_new_op:
			errors += check_new_op(node->data.new_op);
			node->s_type = duplicate_type_decl(node->data.new_op->s_type);
		break;

		case t_expr_type_cast:
			errors += check_expr(node->data.type_cast.expr);
			errors += check_type_decl(node->data.type_cast.type);

			if (errors == 0)
			{
				if (!type_type_cast_able(node->data.type_cast.type, node->data.type_cast.expr->s_type))
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
			errors += check_constant(node->data.constant);
			node->s_type = duplicate_type_decl(node->data.constant->s_type);

		break;

		case t_expr_func_call:
			errors += check_func_call(node->data.func_call);
			node->s_type = duplicate_type_decl(node->data.func_call->s_type);

		break;

		case t_expr_operation:
			errors += check_expr_op(node->data.operation);
			node->s_type = duplicate_type_decl(node->data.operation->s_type);
		break;
	}

	return errors;
}

int check_expr_list(is_expr_list* node)
{
	int errors = 0;

	if (node);
	{
		errors += check_expr(node->node);
		errors += check_expr_list(node->next);

		if (node->next)
			node->length = node->next->length+1;
		else
			node->length = 1;
	}

	return errors;
}

int check_expr_op(is_expr_op* node)
{
	int errors = 0;

	switch (node->type)
	{
		case t_expr_op_unary:
			errors += check_unary_op(node->data.unary);
			node->s_type = duplicate_type_decl(node->data.unary->s_type);
			break;

		case t_expr_op_binary:
			errors += check_binary_op(node->data.binary);
			node->s_type = duplicate_type_decl(node->data.binary->s_type);
			break;

		case t_expr_op_ternary:
			errors += check_ternary_op(node->data.ternary);
			node->s_type = duplicate_type_decl(node->data.ternary->s_type);
			break;
	}

	return errors;
}

int check_for(is_for* node)
{
	int errors = 0, cond_errors;
	char* typeA;

	node->scope = scope_new(NULL, false);
	scope_push(node->scope);
		errors += check_for_init(node->init);	

		cond_errors = check_for_cond(node->cond);
		if (cond_errors == 0)
		{
			if (!type_native_assign_able(t_type_native_bool, node->cond->s_type))
			{
				cond_errors++;
				pretty_error(node->line, "for conditional is not boolean (is of type %s)", typeA = string_type_decl(node->cond->s_type));
				free(typeA);
			}
		}
		errors += cond_errors;

		errors += check_for_inc(node->inc);

		errors += check_stmt(node->body);
	scope_pop();

	return errors;
}

int check_for_cond(is_for_cond* node)
{
	if (node)
		return check_expr(node);
	return 0;
}

int check_for_expr(is_for_expr* node)
{
	int errors = 0;
	
	if (!node)
		return 0;

	switch (node->type)
	{
		case t_for_expr_incr:
			errors += check_incr_op(node->data.incr);
			break;

		case t_for_expr_assign:
			errors += check_assign_op(node->data.assign);
			break;

		case t_for_expr_func_call:
			errors += check_func_call(node->data.func_call);
			break;
	}

	return errors;
}
 
int check_for_expr_list(is_for_expr_list* node)
{
	int errors = 0;

	if (node)
	{
		errors += check_for_expr(node->node);
		errors += check_for_expr_list(node->next);
	}

	return errors;
}
 
int check_for_inc(is_for_inc* node)
{
	return check_for_expr_list(node);
}

int check_for_init(is_for_init* node)
{
	int errors = 0;

	switch (node->type)
	{
		case t_for_init_var_defs:
			errors += check_var_defs(node->data.var_defs);
			break;

		case t_for_init_for_expr_list:
			errors += check_for_expr_list(node->data.expr_list);
			break;
	}

	return errors;
}

int check_func_call(is_func_call* node)
{
	SYMBOL* symbol;
	is_expr_list* arg;
	int errors = 0;
	int i;
	char *typeA, *typeB;

	symbol = scope_lookup(symtab, node->id->name, t_symbol_func);
	if (!symbol)
	{
		pretty_error(node->line, "undefined function %s", node->id->name);
		errors++;
	} else
	{
		errors += check_func_call_arg_list(node->args);

		if (errors == 0)
		{
			if (node->args->length != symbol->data.func_data.nArgs)
			{
				pretty_error(node->line, "too %s arguments for %s, got %d expected %d (declaration is here: %d)",
					node->args->length > symbol->data.func_data.nArgs ? "many" : "few",
					node->id->name,
					symbol->line);

				errors++;
			} else
			{
				for (i = 0, arg = node->args; i < node->args->length; i++, arg = arg->next)
				{
					if (!type_type_assign_able(symbol->data.func_data.args[i]->type, arg->node->s_type))
					{
						errors++;
						pretty_error(node->line, "invalid parameter %d (%s) of function %s (got %s expected %s)",
							i,
							symbol->data.func_data.args[i]->id->name,
							node->id->name,
							typeA = string_type_decl(arg->node->s_type),
							typeB = string_type_decl(symbol->data.func_data.args[i]->type)
						);

						free(typeA);
						free(typeB);
					}
				}
			}
		}
	}

	return errors;
}

int check_func_call_arg_list(is_func_call_arg_list* node)
{
	return check_expr_list(node);
}

int check_func_def(is_func_def* node, bool first_pass)
{
	SYMBOL* symbol;
	int errors = 0;

	if (first_pass)
	{
		errors += check_type_decl(node->type);

		symbol = scope_lookup(symtab, node->id->name, t_symbol_func);
		if (symbol)
		{
			pretty_error(node->line, "symbol %s is already defined (previous declaration was here: %d)", node->id->name, symbol->line);
			errors++;
		} else
			scope_insert(symtab, symbol = symbol_new_func(node->id->name, node->line, node->type, node->args));

		node->scope = scope_new(symbol, false);
		scope_push(node->scope);
			errors += check_func_def_args(node->args);
		scope_pop();

	} else
	{
		scope_push(node->scope);
			errors += check_stmt_list(node->body);
		scope_pop();
	}

	return errors;
}

int check_func_def_arg(is_func_def_arg* node)
{
	int errors = 0;
	SYMBOL* symbol;

	errors += check_type_decl(node->type);
	if (errors == 0)
	{
		symbol = scope_local_lookup(symtab, node->id->name, t_symbol_var);
		if (symbol)
		{
			pretty_error(node->line, "argument %s colides with already defined symbol (previous declaration was here: %d)",
				node->id->name, symbol->line);
			errors++;
		} else
			scope_insert(symtab, symbol_new_var(node->id->name, node->line, node->type));
	}

	return errors;
}

int check_func_def_arg_list(is_func_def_arg_list* node)
{
	int errors = 0;

	if (node)
	{
		errors += check_func_def_arg(node->node);
		errors += check_func_def_arg_list(node->next);
	}

	return errors;
}

int check_func_def_args(is_func_def_args* node)
{
	return check_func_def_arg_list(node);
}

int check_if(is_if* node)
{
	int errors = 0;
	char* typeA;

	errors += check_expr(node->cond);
	if (errors == 0 && !type_native_assign_able(t_type_native_bool, node->cond->s_type))
	{
		errors++;
		pretty_error(node->line, "if conditional is not boolean (is of type %s)", typeA = string_type_decl(node->cond->s_type));
		free(typeA);
	}	

	errors += check_stmt(node->then_body);
	if (node->else_body)
		errors += check_stmt(node->else_body);

	return errors;
}

int check_incr_op(is_incr_op* node)
{
	is_type_native type;
	char* typeA;
	int errors = 0;

	errors += check_var(node->var);
	if (errors == 0)
	{
		if (node->var->s_type->type != t_type_decl_array_decl)
		{
			type = operators_unary[node->type][node->var->s_type->type];
			if (type == ERROR)
			{
				errors++;
				pretty_error(node->line, "unary operation with %s type is invalid",
					typeA = string_type_decl(node->var->s_type));
			} else if (!node->var->initialized)
			{
				errors++;
				pretty_error(node->line, "variable used in a unary op without being initialized ");
			}
		} else
		{
			errors++;
			pretty_error(node->line, "unary operations are invalid between array types");
		}
	}
	return errors;
}

int check_label(is_id* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_loop_stmt(is_loop_stmt* node)
{
	int errors = 0;

	switch (node->type)
	{
		case t_loop_stmt_for:
			errors += check_for(node->data.for_stmt);
		break;

		case t_loop_stmt_while:
			errors += check_while(node->data.while_stmt);
		break;

		case t_loop_stmt_do_while:
			errors += check_do_while(node->data.do_while_stmt);
		break;
	}

	return errors;
}
 
int check_member_stmt(is_member_stmt* node, bool first_pass)
{
	int errors = 0;

	switch (node->type)
	{
		case t_member_stmt_var:
			errors += check_var_stmt(node->data.var, first_pass);
		break;

		case t_member_stmt_func_def:
			errors += check_func_def(node->data.func_def, first_pass);
		break;
	}

	return errors;
}

int check_new_op(is_new_op* node)
{
	int errors = 0;

	errors += check_type_object(node->type_object);
	errors += check_dims(node->dims);

	if (errors == 0)
		node->s_type = new_type_decl_object_dims(node->line, node->type_object, node->dims);
	
	return errors;
}

int check_return(is_return* node)
{
	int errors = 0;
	SYMBOL* symbol;
	is_type_decl *type = NULL, *typeR;
	char *typeA, *typeB;

	if (node->value)
	{
		errors += check_expr(node->value);
		typeR = node->value->s_type;
	}else
	{
		type = new_type_decl_void(node->line);
		typeR = type;
	}

	if (errors == 0)
	{
		symbol = scope_get_symbol(symtab, t_symbol_func);
		if (!type_type_equal(typeR, symbol->data.func_data.type))
		{
			errors++;
			pretty_error(node->line, "invalid return type %s should be of type %s",
				typeA = string_type_decl(typeR),
				typeB = string_type_decl(symbol->data.func_data.type)
			);

			free(typeA);
			free(typeB);
		}	
	}

	if (type)
		free_type_decl(type);

	return errors;
}

int check_stmt(is_stmt* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_stmt_list(is_stmt_list* node)
{
	int errors = 0;
	/* TODO */

	/* TODO: mark nodes after break, continue and return as DEAD CODE */
	return errors;
}
 
int check_switch(is_switch* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_switch_stmt(is_switch_stmt* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_switch_stmt_list(is_switch_stmt_list* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_ternary_op(is_ternary_op* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_type_decl(is_type_decl* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_type_object(is_type_object* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_unary_op(is_unary_op* node)
{
	int errors = 0;
	/* TODO */

	return errors;
}

int check_var(is_var* node)
{
	int errors = 0;
	/* TODO */
	/* todo propagate node->initialized */
	return errors;
}

int check_var_def(is_var_def* node)
{
	int errors = 0;

	errors += check_var_def_left(node->left);
	if (node->var_init)
		errors += check_var_initializer(node->var_init);

	return errors;
}

int check_var_def_list(is_var_def_list* node)
{
	int errors = 0;

	errors += check_var_def(node->node);
	if (node->next)
		errors += check_var_def_list(node->next);

	return errors;
}

int check_var_def_left(is_var_def_left* node)
{
	int errors = 0;

	errors += check_dims_empty_list(node->empty);

	return errors;
}

int check_var_defs(is_var_defs* node)
{
	int errors = 0;

	SYMBOL *symbol;

	is_type_decl *type;

	is_var_def_list *it;

	errors += check_type_decl(node->type);
	errors += check_var_def_list(node->list);

	for (it = node->list; it != NULL; it = it->next)
	{
		symbol = scope_lookup(symtab, it->node->left->id->name, t_symbol_var);
		if (symbol)
		{
			errors++;
			pretty_error(it->node->line, "symbol %s is already defined (previous declaration was here: %d)", it->node->left->id->name, symbol->line);
		} else
		{
			if (it->node->left->empty->size != 0)
			{
				if (node->type->type != t_type_decl_array_decl)
				{
					/* create a new type_decl (array) with it->node->left->data.empty->size dimensions */
					type = insert_type_decl_array(insert_array_decl(insert_type_object(node->type->data.type_object->type), new_dims_empty_list(node->type->line, it->node->left->empty->size)));
				} else
				{
					/* type is already a type_decl_array, only dims update is needed */
					type = duplicate_type_decl(node->type);
					type->data.array->dims->size += it->node->left->empty->size;
				}

			} else /* no dims updates are needed; even if the type is "dimmed" this is only a copy of the type */
				type = duplicate_type_decl(node->type);

			symbol = scope_insert(symtab, symbol_new_var(it->node->left->id->name, node->line, type));

			if (it->node->var_init) /* check initialization */
				if (type_var_init_assign_able(NULL, 0, it->node->var_init)) /* TODO */
					/* if initialization is valid */
					symbol->data.var_data.initialized = true;

		}
	}

	return errors;
}

int check_var_stmt(is_var_stmt* node, bool first_pass)
{
	if (first_pass)
		return check_var_defs(node);

	return 0;
}

int check_var_initializer(is_var_initializer* node)
{
	int errors = 0;

	switch(node->type)
	{
		case t_var_initializer_val_arr:
			errors += check_var_initializer_list(node->data.array);
		break;

		case t_var_initializer_expr:
			errors += check_expr(node->data.expr);
		break;
	}

	return errors;
}

int check_var_initializer_list(is_var_initializer_list* node)
{
	int errors = 0;

	if (node == NULL)
		return 0;

	errors += check_var_initializer(node->node);
	errors += check_var_initializer_list(node->next);

	return errors;
}

int check_while(is_while* node)
{
	int errors = 0;
	char *string;
	
	errors += check_expr(node->cond);
	if (errors == 0)
	{
		if (!type_native_assign_able(t_type_native_bool, node->cond->s_type))
		{
			errors++;
			pretty_error(node->line, "invalid while condition: expected boolean, got %s", string = string_type_decl(node->cond->s_type));
			free(string);
		}
	}

	node->scope = scope_new(NULL, false);
	scope_push(node->scope);
		errors += check_stmt(node->body);
	scope_pop();
	
	return errors;
}

