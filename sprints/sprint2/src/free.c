#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/symtab.h"
#include "inc/free.h"

void free_application(is_application* node)
{
	free_class_def(node);
}

void free_id(is_id* node)
{
	if (node)
	{
		free(node->name);
		free(node);
	}
}

void free_constant(is_constant* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_constant_char:
			case t_constant_string:
				free(node->value.string_val);
				break;

			default:
				break;
		}
		free(node);
	}
}

void free_array_decl (is_array_decl* node)
{
	if (node)
	{
		free_type_object(node->type);
		free(node);
	}
}

void free_assign_op (is_assign_op* node)
{
	if (node)
	{
		free_var(node->var);
		free_expr(node->expr);

		/* semantics */
		free_type_decl(node->s_type);
		free(node);
	}
}

void free_binary_op(is_binary_op* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_binary_op_assign:
				free_assign_op(node->data.assign);
				break;

			default:
				free_expr(node->data.operands.left);
				free_expr(node->data.operands.right);
				break;
		}

		/* semantics */
		free_type_decl(node->s_type);

		free(node);
	}
}

void free_break (is_break* node)
{
	if (node)
	{
		free_id(node->label);
		free(node);
	}
}

void free_class_stmt_list (is_class_stmt_list* node)
{
	if (node)
	{
		free_class_stmt_list(node->next);
		free_class_stmt(node->node);

		free(node);
	}
}

void free_class_def (is_class_def* node)
{
	if (node)
	{
		free_id(node->id);
		free_class_stmt_list(node->body);

		free(node);
	
		if (node->scope)
			scope_delete(node->scope);
	}
}

void free_class_stmt (is_class_stmt* node)
{
	if (node)
	{
		free_class_stmt_privacy(node->privacy);
		free_class_stmt_scope(node->scope);
		free_member_stmt(node->stmt);

		free(node);
	}
}

void free_class_stmt_privacy(is_class_stmt_privacy* node)
{
	if (node)
		free(node);
}

void free_class_stmt_scope (is_class_stmt_scope* node)
{
	if (node)
		free(node);
}

void free_continue (is_continue* node)
{
	if (node)
	{
		free_id(node->label);

		free(node);
	}
}

void free_dims (is_dims* node)
{
	if (node)
	{
		free_dims_sized_list(node->sized);
		free(node);
	}
}

void free_dims_sized (is_dims_sized* node)
{
	free_expr(node);
}

void free_dims_sized_list (is_dims_sized_list* node)
{
	if (node)
	{
		free_dims_sized(node->node);
		free_dims_sized_list(node->next);

		free(node);
	}
}

void free_do_while (is_do_while* node)
{
	if (node)
	{
		free_stmt(node->body);
		free_expr(node->cond);

		scope_delete(node->scope);
		free(node);
	}
}

void free_expr(is_expr* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_expr_var:
				free_var(node->data.var);
				break;

			case t_expr_new_op:
				free_new_op(node->data.new_op);
				break;

			case t_expr_type_cast:
				free_type_decl(node->data.type_cast.type);
				free_expr(node->data.type_cast.expr);
				break;

			case t_expr_constant:
				free_constant(node->data.constant);
				break;

			case t_expr_func_call:
				free_func_call(node->data.func_call);
				break;

			case t_expr_operation:
				free_expr_op(node->data.operation);
				break;
		}

		/* semantics */
		free_type_decl(node->s_type);
		free(node);
	}
}

void free_expr_list (is_expr_list* node)
{
	if (node)
	{
		free_expr(node->node);
		free_expr_list(node->next);

		free(node);
	}
}

void free_expr_op (is_expr_op* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_expr_op_unary:
				free_unary_op(node->data.unary);
				break;

			case t_expr_op_binary:
				free_binary_op(node->data.binary);
				break;

			case t_expr_op_ternary:
				free_ternary_op(node->data.ternary);
				break;
		}

		/* semantics */
		free_type_decl(node->s_type);

		free(node);
	}
}

void free_for(is_for* node)
{
	if (node)
	{
		free_for_init(node->init);
		free_for_cond(node->cond);
		free_for_inc(node->inc);
		free_stmt(node->body);

		scope_delete(node->scope);
		free(node);
	}
}

void free_for_cond(is_for_cond* node)
{
	free_expr(node);
}

void free_for_expr(is_for_expr *node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_for_expr_incr:
				free_incr_op(node->data.incr);
				break;

			case t_for_expr_assign:
				free_assign_op(node->data.assign);
				break;

			case t_for_expr_func_call:
				free_func_call(node->data.func_call);
				break;
		}

		free(node);
	}
}

void free_for_expr_list(is_for_expr_list* node)
{
	if (node)
	{
		free_for_expr(node->node);
		free_for_expr_list(node->next);

		free(node);
	}
}

void free_for_init(is_for_init* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_for_init_var_defs:
				free_var_defs(node->data.var_defs);
				break;

			case t_for_init_for_expr_list:
				free_for_expr_list(node->data.expr_list);
				break;
		}

		free(node);
	}
}

void free_for_inc(is_for_inc* node)
{
	free_for_expr_list(node);
}

void free_func_call(is_func_call* node)
{
	if (node)
	{
		free_id(node->id);
		free_func_call_arg_list(node->args);

		/* semantics */
		free_type_decl(node->s_type);

		free(node);
	}
}

void free_func_call_arg_list(is_func_call_arg_list* node)
{
	free_expr_list(node);
}

void free_func_def(is_func_def* node)
{
	if (node)
	{
		free_type_decl(node->type);
		free_id(node->id);
		free_func_def_arg_list(node->args);
		free_stmt_list(node->body);

		free(node);
	}
}

void free_func_def_arg(is_func_def_arg* node)
{
	if (node)
	{
		free_type_decl(node->type);
		free_id(node->id);

		free(node);
	}
}

void free_func_def_arg_list(is_func_def_arg_list* node)
{
	if (node)
	{
		free_func_def_arg(node->node);
		free_func_def_arg_list(node->next);

		free(node);
	}
}

void free_if(is_if* node)
{
	if (node)
	{
		free_expr(node->cond);
		free_stmt(node->then_body);
		free_stmt(node->else_body);

		free(node);
	}
}

void free_incr_op(is_incr_op* node)
{
	if (node)
	{
		free_var(node->var);

		/* semantics */
		free_type_decl(node->s_type);

		free(node);
	}
}

void free_loop_stmt(is_loop_stmt* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_loop_stmt_for:
				free_for(node->data.for_stmt);
				break;

			case t_loop_stmt_while:
				free_while(node->data.while_stmt);
				break;

			case t_loop_stmt_do_while:
				free_do_while(node->data.do_while_stmt);
				break;
		}

		free_id(node->loop_label);
		free(node);
	}
}

void free_member_stmt(is_member_stmt* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_member_stmt_var:
				free_var_stmt(node->data.var);
				break;

			case t_member_stmt_func_def:
				free_func_def(node->data.func_def);
				break;
		}

		free(node);
	}
}

void free_new_op(is_new_op* node)
{
	if (node)
	{
		free_type_object(node->type_object);
		free_dims(node->dims);

		/* semantics */
		free_type_decl(node->s_type);

		free(node);
	}
}

void free_return(is_return* node)
{
	if (node)
	{
		free_expr(node->value);

		free(node);
	}
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

void free_switch_stmt_list(is_switch_stmt_list* node)
{
	if (node)
	{
		free_switch_stmt(node->node);
		free_switch_stmt_list(node->next);

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

		/* semantics */
		free_type_decl(node->s_type);

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

		/* semantics */
		free_type_decl(node->s_type);

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

		/* semantics */
		free_type_decl(node->s_type);
		
		free(node);
	}
}

void free_var_def(is_var_def* node)
{
	if (node)
	{
		free_var_def_left(node->left);
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

void free_var_def_left(is_var_def_left* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_var_def_left_dims:
				free_dims(node->data.dims);
				break;

			default:
				break;			
		}

		free_id(node->id);
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

		if (node->scope)
			scope_delete(node->scope);

		free(node);
	}
}

