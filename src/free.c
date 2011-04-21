#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/structures.h"
#include "inc/free.h"

void free_application(is_application* application)
{
}

void free_id(is_id* node)
{
	free(node->name);
	free(node);
}

void free_constant(is_constant* node)
{
	/* TODO */
}

void free_constant_bool(is_constant* node)
{
	free(node);
}

void free_constant_long(is_constant* node)
{
	free(node);
}

void free_constant_double(is_constant* node)
{
	free(node);
}

void free_constant_char(is_constant* node)
{
	free(node->value.string_val);
	free(node);
}

void free_constant_string(is_constant* node)
{
	free(node->value.string_val);
	free(node);
}

void free_array_decl (is_array_decl* node)
{
	free_type_object(node->type);
	free(node);
}

void free_assign_op (is_assign_op* node)
{
	free_var(node->var);
	free_expr(node->expr);

	free(node);
}

void free_binary_op(is_binary_op* node)
{
	/* TODO */
}

void free_binary_op_operation (is_binary_op* node)
{
	free_expr(node->data.operands.left);
	free_expr(node->data.operands.right);

	free(node);
}

void free_binary_op_assign (is_binary_op* node)
{
	free_assign_op(node->data.assign);
	free(node);
}

void free_break (is_break* node)
{
	free_id(node->label);
	free(node);
}

void free_class_stmt_list (is_class_stmt_list* node)
{
	free_class_stmt_list(node->next);
	free_class_stmt(node->node);

	free(node);
}

void free_class_def (is_class_def* node)
{
	free_id(node->id);
	free_class_stmt_list(node->body);

	free(node);
}

void free_class_stmt (is_class_stmt* node)
{
	free_class_stmt_privacy(node->privacy);
	free_class_stmt_scope(node->scope);
	free_member_stmt(node->stmt);

	free(node);
}

void free_class_stmt_privacy(is_class_stmt_privacy* node)
{
	free(node);
}

void free_class_stmt_scope (is_class_stmt_scope* node)
{
	free(node);
}

void free_continue (is_continue* node)
{
	free_id(node->label);

	free(node);
}

void free_dims (is_dims* node)
{
	free_dims_sized_list(node->sized);

	free(node);
}

void free_dims_sized (is_dims_sized* node)
{
	/* TODO */
}

void free_dims_sized_list (is_dims_sized_list* node)
{
	free_dims_sized(node->node);

	if (node->next)
		free_dims_sized_list(node->next);

	free(node);
}

void free_do_while (is_do_while* node)
{
	free_stmt(node->body);
	free_expr(node->cond);

	free(node);
}

void free_expr(is_expr* node)
{
	/* TODO */
}

void free_expr_var(is_expr* node)
{
	free_var(node->data.var);

	free(node);
}

void free_expr_new_op(is_expr* node)
{
	free_new_op(node->data.new_op);

	free(node);
}

void free_expr_constant(is_expr* node)
{
	free_constant(node->data.constant);

	free(node);
}

void free_expr_func_call(is_expr* node)
{
	free_func_call(node->data.func_call);

	free(node);
}

void free_expr_expr_op(is_expr* node)
{
	free_expr_op(node->data.operation);

	free(node);
}

void free_expr_list (is_expr_list* node)
{
	free_expr(node->node);

	if(node->next)
		free_expr_list(node->next);

	free(node);
}

void free_expr_op (is_expr_op* node)
{
	/* TODO */
}

void free_expr_op_unary (is_expr_op* node)
{
	free_unary_op(node->data.unary);

	free(node);
}

void free_expr_op_binary(is_expr_op* node)
{
	free_binary_op(node->data.binary);

	free(node);
}

void free_expr_op_ternary(is_expr_op* node)
{
	free_ternary_op(node->data.ternary);

	free(node);
}

void free_for(is_for* node)
{
	free_for_init(node->init);
	free_for_cond(node->cond);
	free_for_inc(node->inc);
	free_stmt(node->body);

	free(node);
}

void free_for_cond(is_for_cond* node)
{
	/* TODO */
}

void free_for_expr(is_for_expr *node)
{
	/* TODO */
}

void free_for_expr_incr(is_for_expr* node)
{
	free_incr_op(node->data.incr);

	free(node);
}

void free_for_expr_assign(is_for_expr* node)
{
	free_assign_op(node->data.assign);

	free(node);
}

void free_for_expr_func_call(is_for_expr* node)
{
	free_func_call(node->data.func_call);

	free(node);
}

void free_for_expr_list(is_for_expr_list* node)
{
	free_for_expr(node->node);

	if (node->next)
		free_for_expr_list(node->next);

	free(node);
}

void free_for_init(is_for_init* node)
{
	/* TODO */
}

void free_for_init_var_defs(is_for_init* node)
{
	free_var_defs(node->data.var_defs);

	free(node);
}

void free_for_init_for_expr_list(is_for_init* node)
{
	free_for_expr_list(node->data.expr_list);

	free(node);
}

void free_for_inc(is_for_inc* node)
{
	/* TODO */
}

void free_func_call(is_func_call* node)
{
	/* TODO */
}

void free_func_call_arg_list(is_func_call_arg_list* node)
{
	/* TODO */
}

void free_func_call_id(is_func_call* node)
{
	free_id(node->id);
	free_func_call_arg_list(node->args);

	free(node);
}

void free_func_call_sysout(is_func_call* node)
{
	free_func_call_arg_list(node->args);

	free(node);
}

void free_func_def(is_func_def* node)
{
	free_type_decl(node->type);
	free_id(node->id);
	free_func_def_arg_list(node->args);
	free_stmt_list(node->body);

	free(node);
}

void free_func_def_arg(is_func_def_arg* node)
{
	free_type_decl(node->type);
	free_id(node->id);

	free(node);
}

void free_func_def_arg_list(is_func_def_arg_list* node)
{
	free_func_def_arg(node->node);

	if (node->next)
		free_func_def_arg_list(node->next);

	free(node);
}

void free_if(is_if* node)
{
	free_expr(node->cond);
	free_stmt(node->then_body);
	free_stmt(node->else_body);

	free(node);
}

void free_incr_op(is_incr_op* node)
{
	free_var(node->var);

	free(node);
}

void free_loop_stmt(is_loop_stmt* node)
{
	/* TODO */
}

void free_loop_stmt_for(is_loop_stmt* node)
{
	free_for(node->data.for_stmt);

	free(node);
}

void free_loop_stmt_while(is_loop_stmt* node)
{
	free_while(node->data.while_stmt);

	free(node);
}

void free_loop_stmt_do_while(is_loop_stmt* node)
{
	free_do_while(node->data.do_while_stmt);

	free(node);
}

void free_member_stmt(is_member_stmt* node)
{
	/* TODO */
}

void free_member_stmt_var(is_member_stmt* node)
{
	free_var_stmt(node->data.var);

	free(node);
}

void free_member_stmt_func_def(is_member_stmt* node)
{
	free_func_def(node->data.func_def);

	free(node);
}

void free_new_op(is_new_op* node)
{
	free_type_object(node->type_object);
	free_dims(node->dims);

	free(node);
}

void free_return(is_return* node)
{
	free_expr(node->value);

	free(node);
}

void free_stmt(is_stmt* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_stmt_stmt_list:
				free_stmt_list(node->data.stmt_list);
				break;

			case t_stmt_var_stmt:
				free_var_stmt(node->data.var);
				break;

			case t_stmt_assign:
				free_assign_op(node->data.assign);
				break;

			case t_stmt_incr:
				free_incr_op(node->data.incr);
				break;

			case t_stmt_if:
				free_if(node->data.if_stmt);
				break;

			case t_stmt_loop:
				free_loop_stmt(node->data.loop);
				break;

			case t_stmt_func_call:
				free_func_call(node->data.func_call);
				break;

			case t_stmt_switch:
				free_switch(node->data.switch_stmt);
				break;

			case t_stmt_break:
				free_break(node->data.break_stmt);
				break;

			case t_stmt_continue:
				free_continue(node->data.continue_stmt);
				break;

			case t_stmt_return:
				free_return(node->data.return_stmt);
				break;
		}
	}

	free(node);
}

void free_stmt_list(is_stmt_list* node)
{

	if (node)
	{
		free_stmt(node->node);
		free_stmt_list(node->next);

		free(node);
	}
}

void free_switch(is_switch* node)
{
	if (node)
	{
		free_expr(node->expr);
		free_switch_stmt_list(node->list);

		free(node);
	}
}

void free_switch_stmt(is_switch_stmt* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_switch_stmt_default:
				break;

			case t_switch_stmt_case:
				free_constant(node->constant);
		}

		free_stmt_list(node->list);
		free(node);
	}
}

void free_ternary_op(is_ternary_op* node)
{
	if (node)
	{
		free_expr(node->if_expr);
		free_expr(node->then_expr);
		free_expr(node->else_expr);

		free(node);
	}
}

void free_type_decl(is_type_decl* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_type_decl_type_object:
				free_type_object(node->data.type_object);
				break;

			case t_type_decl_array_decl:
				free_array_decl(node->data.array);
				break;
		}
		
		free(node);
	}
}

void free_type_object(is_type_object* node)
{
	if (node)
		free(node);
}

void free_unary_op(is_unary_op* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_unary_op_operation:
				free_expr(node->data.operation.expr);
				break;

			case t_unary_op_incr_op:
				free_incr_op(node->data.incr);
				break;
		}

		free(node);
	}
}

void free_var(is_var* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_var_id:
				free_id(node->data.id);
				break;

			case t_var_new_op:
				free_new_op(node->data.new_op);
				break;
	
			case t_var_array:
				free_var(node->data.array.var);
				free_dims_sized(node->data.array.dims);
				break;

			case t_var_func_call:
				free_func_call(node->data.func_call.call);
				free_dims_sized(node->data.func_call.dims);
				break;
		}
		
		free(node);
	}
}

void free_var_def(is_var_def* node)
{
	if (node)
	{
		free_id(node->id);
		free_var_initializer(node->var_init);

		free(node);
	}
}

void free_var_def_list(is_var_def_list* node)
{
	if( node)
	{
		free_var_def(node->node);
		free_var_def_list(node->next);

		free(node);
	}
}


void free_var_defs(is_var_defs* node)
{
	if (node)
	{
		free_type_decl(node->type);
		free_var_def_list(node->list);
		free(node);
	}
}

void free_var_initializer(is_var_initializer* node)
{
	if (node)
	{
		switch(node->type)
		{
			case t_var_initializer_val_arr:
				free_var_initializer_list(node->data.array);
				break;

			case t_var_initializer_expr:
				free_expr(node->data.expr);
				break;
		} 
		free(node);
	}
}

void free_var_initializer_list(is_var_initializer_list* node)
{
	if (node)
	{
		free_var_initializer(node->node);
		free_var_initializer_list(node->next);

		free(node);
	}
}

void free_var_stmt(is_var_stmt* node)
{
	free_var_defs(node);
}

void free_while(is_while* node)
{
	if (node)
	{
		free_expr(node->cond);
		free_stmt(node->body);
		free(node);
	}
}

