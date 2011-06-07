#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_C

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/symtab.h"
#include "inc/check.h"
#include "inc/types.h"
#include "inc/insert.h"
#include "inc/duplicate.h"
#include "inc/free.h"
#include "inc/translate.h"

/* LEX */
int check_constant(is_constant* node)
{
	switch (node->type)
	{
		case t_constant_bool:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_bool));
		break;

		case t_constant_int:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_int));
		break;

		case t_constant_long:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_long));
		break;

		case t_constant_float:
			node->s_type = insert_type_decl_object(insert_type_object(t_type_native_float));
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
	globalpos = 0; 
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
	SYMBOL* symbol;

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
					pretty_error(node->line, "invalid assignment from %s to %s",
						typeA = string_type_decl(node->expr->s_type),
						typeB = string_type_decl(node->var->s_type)
					);
					free(typeA);
					free(typeB);
				} else
				{
					symbol = scope_lookup(symtab, node->var->data.id->name, t_symbol_var);
					symbol->data.var_data.initialized = true;

					node->s_type = duplicate_type_decl(node->var->s_type);
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
					} else
						node->s_type = insert_type_decl_object(insert_type_object(type));
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
			if (errors == 0)
				node->s_type = duplicate_type_decl(node->data.assign->s_type);
		break;

		default:
			errors += check_expr(node->data.operands.left);
			errors += check_expr(node->data.operands.right);

			if (errors == 0)
			{
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
						pretty_error(node->line, "invalid binary operation between %s and %s",
							typeA = string_type_decl(node->data.operands.left->s_type),
							typeB = string_type_decl(node->data.operands.right->s_type)
						);
						free(typeA);
						free(typeB);
					}
				}
			}

			/* only valid for objects not arrays*/
			if (errors == 0)
				node->s_type = insert_type_decl_object(insert_type_object(type));
		break;
	}
	return errors;
}

int check_break(is_break* node)
{
	int errors = 0;

	if (node->label)
	{
		pretty_error(node->line, "labels are not supported at this time");		
		errors++;
		/* TODO: 
			errors += check_label(node->label);
		*/
	}

	if (errors == 0)
	{
		node->scope = scope_get_by_name(symtab, NULL, t_symbol_loop);

		if (!node->scope)
		{
			errors++;
			pretty_error(node->line, "break stmt outside of loop or case", node->label);		
		}
	}

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

		if (errors == 0)
		{
			symbol = scope_lookup(symtab, "main", t_symbol_func);
			if (symbol)
			{
				/* TODO check function prototype */
			} else
			{
				errors++;
				pretty_error(node->line, "missing main entry point");
			}
		}
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
	{
		pretty_error(node->line, "labels are not supported at this time");		
		errors++;
		/* TODO: 
			errors += check_label(node->label);
		*/
	}

	if (errors == 0)
	{
		node->scope = scope_get_by_name(symtab, NULL, t_symbol_loop);

		if (!node->scope)
		{
			errors++;
			pretty_error(node->line, "continue stmt outside of loop", node->label);		
		}
	}

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

	int label = ++label_counter; /* setting label for use with loops and break/continue */

	node->scope = scope_new(symbol_new_loop(node->line, label), false);
	scope_push(node->scope);
		errors += check_stmt(node->body);
		if (errors == 0)
			node->terminates = node->body->terminates;

		errors += check_expr(node->cond);
		if (errors == 0)
		{
			if (!type_native_assign_able(t_type_native_bool, node->cond->s_type))
			{
				errors++;
				pretty_error(node->line, "invalid do..while condition (must be boolean)");
			}
		}
	scope_pop();
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

			if (errors == 0)
			{
				node->s_type = duplicate_type_decl(node->data.var->s_type);

				if (!node->data.var->initialized)
				{
					errors++;
					pretty_error(node->line, "variable used without being initialized");
				}
			}
		break;

		case t_expr_new_op:
			errors += check_new_op(node->data.new_op);
			if (errors == 0)
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
				} else
					node->s_type = duplicate_type_decl(node->data.type_cast.type);
			}
		break;

		case t_expr_constant:
			errors += check_constant(node->data.constant);
			if (errors == 0)
				node->s_type = duplicate_type_decl(node->data.constant->s_type);
		break;

		case t_expr_func_call:
			errors += check_func_call(node->data.func_call);
			if (errors == 0)
				node->s_type = duplicate_type_decl(node->data.func_call->s_type);
		break;

		case t_expr_operation:
			errors += check_expr_op(node->data.operation);
			if (errors == 0)
				node->s_type = duplicate_type_decl(node->data.operation->s_type);
		break;
	}

	return errors;
}

int check_expr_list(is_expr_list* node)
{
	int errors = 0;

	if (node)
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
			if (errors == 0)
				node->s_type = duplicate_type_decl(node->data.unary->s_type);
			break;

		case t_expr_op_binary:
			errors += check_binary_op(node->data.binary);
			if (errors == 0)
				node->s_type = duplicate_type_decl(node->data.binary->s_type);
			break;

		case t_expr_op_ternary:
			errors += check_ternary_op(node->data.ternary);
			if (errors == 0)
				node->s_type = duplicate_type_decl(node->data.ternary->s_type);
			break;
	}

	return errors;
}

int check_for(is_for* node)
{
	int errors = 0, cond_errors;
	char* typeA;

	int label = ++label_counter; /* setting label for use with loops and break/continue */

	node->scope = scope_new(symbol_new_loop(node->line, label), false);
	scope_push(node->scope);
		if (node->init)
			errors += check_for_init(node->init);

		if (node->cond)
		{
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
		}
	
		if (node->inc)
			errors += check_for_inc(node->inc);

		errors += check_stmt(node->body);
		if (errors == 0)
			node->terminates = node->body->terminates;
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
			if (errors == 0)
				node->data.incr->used = true;
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
			errors += check_var_defs(node->data.var_defs, false);
			break;

		case t_for_init_for_expr_list:
			errors += check_for_expr_list(node->data.expr_list);
			break;
	}

	return errors;
}

int check_func_call(is_func_call* node)
{
	is_expr_list* arg;
	int errors = 0;
	int i;
	char *typeA, *typeB;

	node->symbol = scope_lookup(symtab, node->id->name, t_symbol_func);
	if (!node->symbol)
	{
		pretty_error(node->line, "undefined function %s", node->id->name);
		errors++;
	} else
	{
		errors += check_func_call_arg_list(node->args);

		if (errors == 0)
		{
			if ((node->args == NULL && node->symbol->data.func_data.nArgs != 0) ||
				(node->args != NULL && node->args->length != node->symbol->data.func_data.nArgs))
			{
				pretty_error(node->line, "too %s arguments for %s, got %d expected %d (declaration is here: %d)",
					node->args->length > node->symbol->data.func_data.nArgs ? "many" : "few",
					node->id->name,
					node->args->length,
					node->symbol->data.func_data.nArgs,
					node->symbol->line);

				errors++;
			} else
			{
				for (i = 0, arg = node->args; arg != NULL; i++, arg = arg->next)
				{
					if (!type_type_assign_able(node->symbol->data.func_data.args[i]->type, arg->node->s_type))
					{
						errors++;
						pretty_error(node->line, "invalid parameter %d (%s) of function %s (got %s expected %s)",
							i,
							node->symbol->data.func_data.args[i]->id->name,
							node->id->name,
							typeA = string_type_decl(arg->node->s_type),
							typeB = string_type_decl(node->symbol->data.func_data.args[i]->type)
						);

						free(typeA);
						free(typeB);
					}
				}

				if (errors == 0)
					node->s_type = duplicate_type_decl(node->symbol->data.func_data.type);
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
	SCOPE* tempscope;
	int label;
	int errors = 0;
	is_type_decl *tmpType = NULL;

	if (first_pass)
	{
		errors += check_type_decl(node->type);

		symbol = scope_lookup(symtab, node->id->name, t_symbol_func);
		if (symbol)
		{
			pretty_error(node->line, "symbol %s is already defined (previous declaration was here: %d)", node->id->name, symbol->line);
			errors++;
		} else
		{
			tempscope = scope_new(NULL, false);
			scope_push(tempscope);
				errors += check_func_def_args(node->args);
			scope_pop();
			
			if (strcmp(node->id->name, "main") == 0)
			{
				label = 0;

				if (node->args) /* no args is valid */
				{
					if (node->args->length == 1) /* main may must not have more than two arguments */
					{
						tmpType = insert_type_decl_array(insert_array_decl(insert_type_object(t_type_native_string), new_dims_empty_list(0, 1))); /* must be an array of Strings */

						if (!type_type_equal(tmpType,node->args->node->type))
						{
							errors++;
							pretty_error(node->line, "main function arguments do not match any valid prototypes");
						}

						free_type_decl(tmpType);
					} else
					{
						errors++;
						pretty_error(node->line, "main function arguments do not match any valid prototypes");
					}
				}

				tmpType = insert_type_decl_object(insert_type_object(t_type_native_int)); /* return value must be int or void */

				if (!type_type_equal(tmpType,node->type))
				{
					free_type_decl(tmpType);

					tmpType = new_type_decl_void(0); /* check for void */

					if (!type_type_equal(tmpType,node->type)) /* none; errors occurred */
					{
						errors++;
						pretty_error(node->line, "main function return type does not match any valid types (nor int nor void)");
					}
				}
				
				free_type_decl(tmpType);
			} else
				label = ++label_counter;

			symbol = symbol_new_func(node->id->name, node->line, node->type, node->args, label);
			scope_delete(tempscope);

			scope_insert(symtab, symbol);

			node->scope = scope_new(symbol, false);
		}
	} else
	{
		scope_push(node->scope);
			errors += check_func_def_args(node->args); /* this will not give errors */
			errors += check_stmt_list(node->body);
			
			if ((!node->body || !node->body->terminated) &&
				!(node->type->type == t_type_decl_type_object && node->type->data.type_object->type == t_type_native_void))
			{
				pretty_error(node->line, "reached end of non void function");
				errors++;		
			}
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
		{
			symbol = scope_insert(symtab, symbol_new_var(node->id->name, node->line, node->type, false, symtab->framepos++));
			symbol->data.var_data.initialized = true;
		}
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

		if (node->next)
			node->length = node->next->length + 1;
		else
			node->length = 1;
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
	node->terminates = node->then_body->terminates && node->else_body != NULL;
	if (node->else_body)
	{
		errors += check_stmt(node->else_body);
		node->terminates &= node->else_body->terminates;
	}

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
			type = operators_incr_op[node->var->s_type->data.type_object->type];
			if (type == ERROR)
			{
				errors++;
				pretty_error(node->line, "increment operation with %s type is invalid",
					typeA = string_type_decl(node->var->s_type));

				free(typeA);
			} else if (!node->var->initialized)
			{
				errors++;
				pretty_error(node->line, "variable used in a increment op without being initialized ");
			} else
				node->s_type = duplicate_type_decl(node->var->s_type);

		} else
		{
			errors++;
			pretty_error(node->line, "increment operations are invalid between array types");
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

	if (errors == 0)
	{
		/*
			TODO:
			propagate loop terminates, only if node condition is ALWAYS true
		*/
	}
	return errors;
}
 
int check_member_stmt(is_member_stmt* node, bool first_pass)
{
	int errors = 0;

	switch (node->type)
	{
		case t_member_stmt_var:
			if (first_pass)
				errors += check_var_stmt(node->data.var, true);
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
	SCOPE* scope;

	is_type_decl *type = NULL, *typeR;
	char *typeA, *typeB;

	if (node->value)
	{
		errors += check_expr(node->value);
		typeR = node->value->s_type;
	} else
	{
		type = new_type_decl_void(node->line);
		typeR = type;
	}

	if (errors == 0)
	{
		scope = scope_get_by_name(symtab, NULL, t_symbol_func);
		node->symbol = scope->symbol;
		if (!type_type_equal(typeR, node->symbol->data.func_data.type))
		{
			typeA = string_type_decl(typeR);

			typeB = string_type_decl(node->symbol->data.func_data.type);

			errors++;
			pretty_error(node->line, "invalid return type %s should be of type %s",
				typeA,
				typeB
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

	/* ; empty statement */
	if (!node)
		return 0;

	switch (node->type)
	{
		case t_stmt_stmt_list:
			node->data.stmt_list.scope = scope_new(NULL, false);
			scope_push(node->data.stmt_list.scope);
				errors += check_stmt_list(node->data.stmt_list.list);
			scope_pop();
			node->terminates = node->data.stmt_list.list->terminated;
		break;

		case t_stmt_var_stmt:
			errors += check_var_stmt(node->data.var, false);
		break;

		case t_stmt_assign:
			errors += check_assign_op(node->data.assign);
		break;

		case t_stmt_incr:
			errors += check_incr_op(node->data.incr);
		break;

		case t_stmt_if:
			errors += check_if(node->data.if_stmt);
			node->terminates = node->data.if_stmt->terminates;
		break;

		case t_stmt_loop:
			errors += check_loop_stmt(node->data.loop);
			node->terminates = node->data.loop->terminates;
		break;

		case t_stmt_func_call:
			errors += check_func_call(node->data.func_call);
		break;

		case t_stmt_switch:
			errors += check_switch(node->data.switch_stmt);
			node->terminates = node->data.switch_stmt->terminates;
		break;

		case t_stmt_break:
			errors += check_break(node->data.break_stmt);
			node->terminates = true;
		break;

		case t_stmt_continue:
			errors += check_continue(node->data.continue_stmt);
			node->terminates = true;
		break;
		
		case t_stmt_return:
			errors += check_return(node->data.return_stmt);
			node->terminates = true;
		break;
	}

	return errors;
}

int check_stmt_list(is_stmt_list* node)
{
	int errors = 0;

	if (node)
	{
		errors += check_stmt(node->node);
		errors += check_stmt_list(node->next);

		node->terminated = node->node->terminates;

		if (node->next)
		{
			node->length = node->next->length+1;
			
			if (node->terminated)
				pretty_error(node->line, "dead code after incoditional jump stmt");
			else
				node->terminated = node->next->terminated;
		} else
			node->length = 1;
	}

	return errors;
}
 
int check_switch(is_switch* node)
{
	int errors = 0;
	errors += 1;
	pretty_error(node->line, "switch statement's are not supported yet");

	/* TODO: propagate terminates*/

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
	char *typeA, *typeB;
	int errors = 0;

	errors += check_expr(node->if_expr);
	if (errors == 0 && !type_native_assign_able(t_type_native_bool, node->if_expr->s_type))
	{
		errors++;
		typeA = string_type_decl(node->if_expr->s_type);

		pretty_error(node->line, "ternary conditional is not boolean (is of type %s)", typeA);

		free(typeA);
	}

	errors += check_expr(node->then_expr);
	errors += check_expr(node->else_expr);
	if (errors == 0 && !type_type_equal(node->then_expr->s_type, node->else_expr->s_type))
	{
		errors++;
		typeA = string_type_decl(node->then_expr->s_type);
		typeB = string_type_decl(node->else_expr->s_type);

		pretty_error(node->line, "ternary results are not of the same type (are of types %s and %s)", typeA, typeB);

		free(typeA);
		free(typeB);
	}

	if (errors == 0)
		node->s_type = duplicate_type_decl(node->then_expr->s_type);

	return errors;
}

int check_type_decl(is_type_decl* node)
{
	int errors = 0;

	switch (node->type)
	{
		case t_type_decl_type_object:
			errors += check_type_object(node->data.type_object);
		break;

		case t_type_decl_array_decl:
			errors += check_array_decl(node->data.array);
		break;	
	}	
	return errors;
}

int check_type_object(is_type_object* node)
{
	int errors = 0;

	/*errors += check_type_native(node->type); */

	return errors;
}

int check_unary_op(is_unary_op* node)
{
	is_type_native type;
	char* typeA;
	int errors = 0;

	switch (node->type)
	{
		case t_unary_op_operation:
			errors += check_expr(node->data.operation.expr);
			if (errors == 0)
			{
				if (node->data.operation.expr->s_type->type != t_type_decl_array_decl)
				{
					type = operators_unary[node->data.operation.op][node->data.operation.expr->s_type->type];
					if (type == ERROR)
					{
						errors++;
						pretty_error(node->line, "unary operation with %s type is invalid",
							typeA = string_type_decl(node->data.operation.expr->s_type));
						free(typeA);
					} else
						node->s_type = duplicate_type_decl(node->data.operation.expr->s_type);
				} else
				{
					errors++;
					pretty_error(node->line, "unary operations are invalid between array types");
				}
			}
		break;

		case t_unary_op_incr_op:
			errors += check_incr_op(node->data.incr);
			if (errors == 0)
			{
				node->s_type = duplicate_type_decl(node->data.incr->s_type);
				node->data.incr->used = true;
			}
		break;	
	}

	return errors;
}

int check_var(is_var* node)
{
	int errors = 0;
	char *typeA;

	switch (node->type)
	{
		case t_var_id:
			node->symbol = scope_lookup(symtab, node->data.id->name, t_symbol_var);
			if (!node->symbol)
			{
				errors++;
				pretty_error(node->line, "undefined variable %s", node->data.id->name);
				node->initialized = false;
			} else
			{
				node->initialized = node->symbol->data.var_data.initialized;
				node->s_type = duplicate_type_decl(node->symbol->data.var_data.type);
			}
		break;

		case t_var_new_op:
			errors += check_new_op(node->data.new_op);
			node->s_type = duplicate_type_decl(node->data.new_op->s_type);
			node->initialized = true;
		break;

		case t_var_array:
			errors += check_var(node->data.array.var);
			errors += check_dims_sized(node->data.array.dims);

			if (errors == 0)
			{
				if (node->data.array.var->s_type->type == t_type_decl_array_decl)
				{
					node->s_type = duplicate_type_decl(node->data.array.var->s_type);
					node->s_type->data.array->dims->size--;
				} else
				{
					errors++;
					pretty_error(node->line, "subscript of unsuscriptable type (%s)",
						typeA = string_type_decl(node->data.array.var->s_type)
					);
					free(typeA);
				}
			}
			node->initialized = true;
		break;

		case t_var_func_call:
			errors += check_func_call(node->data.func_call.call);
			errors += check_dims_sized(node->data.array.dims);

			if (errors == 0)
			{
				if (node->data.func_call.call->s_type->type == t_type_decl_array_decl)
				{
					node->s_type = duplicate_type_decl(node->data.func_call.call->s_type);
					node->s_type->data.array->dims->size--;
				} else
				{
					errors++;
					pretty_error(node->line, "subscript of unsuscriptable type (%s)",
						typeA = string_type_decl(node->data.func_call.call->s_type)
					);
					free(typeA);
				}
			}
			node->initialized = true;
		break;
	}

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

int check_var_defs(is_var_defs* node, bool first_pass)
{
	int errors = 0;

	SYMBOL *symbol;

	is_type_decl *type = NULL;

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

			if (first_pass)
				symbol = scope_insert(symtab, symbol_new_var(it->node->left->id->name, node->line, type, true, globalpos++));
			else
				symbol = scope_insert(symtab, symbol_new_var(it->node->left->id->name, node->line, type, false, symtab->framepos++));

			it->node->left->symbol = symbol;

			if (it->node->var_init) /* check initialization if it exists */
			{
				if (type_var_init_assign_able(type, (type->type == t_type_decl_array_decl ? type->data.array->dims->size : 0), it->node->var_init)) /* FIXME/TODO */
					/* if initialization is valid */
					symbol->data.var_data.initialized = true;
				else
				{
					errors++;
					pretty_error(it->node->line, "%s initalization is invalid", it->node->left->id->name);
				}
			}
		}
	}

	return errors;
}

int check_var_stmt(is_var_stmt* node, bool first_pass)
{
	return check_var_defs(node, first_pass);
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

	int label = ++label_counter; /* setting label for use with loops and break/continue */
	
	node->scope = scope_new(symbol_new_loop(node->line, label), false);
	scope_push(node->scope);
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

		errors += check_stmt(node->body);
		node->terminates = node->body->terminates;
	scope_pop();
	
	return errors;
}

