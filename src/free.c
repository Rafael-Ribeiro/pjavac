#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/structures.h"
#include "inc/free.h"

void free_application(is_application* application)
{
}

/*
void free_type_decl(is_type_decl* node)
{
	/ TODO /
}
*/

void free_id(is_id* node)
{
	free(node->name);
	free(node);
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
	/*FIXME
	free_type_object(node->type);
	*/
	free(node);
}

void free_assign_op (is_assign_op* node)
{
	/*FIXME
	free_var(node->var);
	free_expr(node->expr);
	*/
	free(node);
}

void free_binary_op_operation (is_binary_op* node)
{
	/*FIXME
	free_expr(node->data.operands.left);
	free_expr(node->data.operands.right);
	*/

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
	/*FIXME
	free_class_stmt(node->node);
	*/

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
	/*FIXME
	free_class_stmt_privacy(node->privacy);
	free_class_stmt_scope(node->scope);
	free_member_stmt(node->stmt);
	*/

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
	/*FIXME
	free_label(node->label);
	*/
	free(node);
}

void free_dims (is_dims* node)
{
	/*FIXME
	free_dims_sized_list(node->sized);
	*/
	free(node);
}

void free_dims_sized_list (is_dims_sized_list* node)
{
	/*FIXME
	free_dims_sized(node->node);
	*/

	if (node->next)
		free_dims_sized_list(node->next);

	free(node);
}

void free_do_while (is_do_while* node)
{
	/*FIXME
	free_stmt(node->body);
	free_expr(node->cond);
	*/

	free(node);
}

void free_expr_var(is_expr* node)
{
	/*FIXME
	free_var(node->data.var);
	*/
	free(node);
}

void free_expr_new_op(is_expr* node)
{
	/*FIXME
	free_new_op(node->data.new_op);
	*/
	free(node);
}

void free_expr_constant(is_expr* node)
{
	/*FIXME
	free_constant(node->data.constant);
	*/
	free(node);
}

void free_expr_func_call(is_expr* node)
{
	/*FIXME
	free_func_call(node->data.func_call);
	*/
	free(node);
}

void free_expr_expr_op(is_expr* node)
{
	/*FIXME
	free_expr_op(node->data.operation);
	*/
	free(node);
}

void free_expr_list (is_expr_list* node)
{
	/*FIXME
	free_expr(node->node);
	*/

	if(node->next)
		free_expr_list(node->next);

	free(node);
}

void free_expr_op_unary (is_expr_op* node)
{
	/*FIXME
	free_unary_op(node->data.unary);
	*/
	free(node);
}

void free_expr_op_binary(is_expr_op* node)
{
	/*FIXME
	free_binary_op(node->data.binary);
	*/
	free(node);
}

void free_expr_op_ternary(is_expr_op* node)
{
	/*FIXME
	free_ternary_op(node->data.ternary);
	*/
	free(node);
}

void free_for(is_for* node)
{
	/*FIXME
	free_for_init(node->init);
	free_for_cond(node->cond);
	free_for_inc(node->inc);
	free_stmt(node->body);
	*/

	free(node);
}

void free_for_expr_incr(is_for_expr* node)
{
	/*FIXME
	free_incr_op(node->data.incr);
	*/
	free(node);
}

void free_for_expr_assign(is_for_expr* node)
{
	/*FIXME
	free_assign_op(node->data.assign);
	*/
	free(node);
}

void free_for_expr_func_call(is_for_expr* node)
{
	/*FIXME
	free_func_call(node->data.func_call);
	*/
	free(node);
}

void free_for_expr_list(is_for_expr_list* node)
{
	/*FIXME
	free_for_expr(node->node);
	*/
	if (node->next)
		free_for_expr_list(node->next);

	free(node);
}

void free_for_init_var_defs(is_for_init* node)
{
	/*FIXME
	free_var_defs(node->data.var_defs);
	*/
	free(node);
}

void free_for_init_for_expr_list(is_for_init* node)
{
	/*FIXME
	free_for_expr_list(node->data.expr_list);
	*/
	free(node);
}

void free_for_inc(is_for_inc* node)
{
	/* TODO */
}

void free_func_call_id(is_func_call* node)
{
	free_id(node->id);
	/*FIXME
	free_func_call_arg_list(node->args);
	*/

	free(node);
}

void free_func_call_sysout(is_func_call* node)
{
	/*FIXME
	free_func_call_arg_list(node->args);
	*/

	free(node);
}

void free_func_def(is_func_def* node)
{
	/*FIXME
	free_type_decl(node->type);
	*/
	free_id(node->id);
	/*FIXME
	free_func_def_arg_list(node->args);
	free_stmt_list(node->body);
	*/

	free(node);
}

void free_func_def_arg(is_func_def_arg* node)
{
	/*FIXME
	free_type_decl(node->type);
	*/
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

/*
is_if* free_if(is_expr* cond, is_stmt* then_body, is_stmt* else_body)
{
	is_if *node = (is_if*)malloc(sizeof(is_if));
	node->cond = cond;
	node->then_body = then_body;
	node->else_body = else_body;

	free(node);
}

is_incr_op* free_incr_op(type_incr_op type, bool pre, is_var* var)
{
	is_incr_op* node = (is_incr_op*)malloc(sizeof(is_incr_op));

	node->type = type;
	node->pre = pre;
	node->var = var;

	free(node);
}

is_loop_stmt* free_loop_stmt_for(is_for* for_stmt)
{
	is_loop_stmt *node = (is_loop_stmt*)malloc(sizeof(is_loop_stmt));

	node->type = t_loop_stmt_for;
	node->data.for_stmt = for_stmt;

	free(node);
}

is_loop_stmt* free_loop_stmt_while(is_while* while_stmt)
{
	is_loop_stmt *node = (is_loop_stmt*)malloc(sizeof(is_loop_stmt));

	node->type = t_loop_stmt_while;
	node->data.while_stmt = while_stmt;

	free(node);
}

is_loop_stmt* free_loop_stmt_do_while(is_do_while* do_while_stmt)
{
	is_loop_stmt *node = (is_loop_stmt*)malloc(sizeof(is_loop_stmt));

	node->type = t_loop_stmt_do_while;
	node->data.do_while_stmt = do_while_stmt;

	free(node);
}

is_member_stmt* free_member_stmt_var(is_var_stmt* var)
{
	is_member_stmt* node = (is_member_stmt*)malloc(sizeof(is_member_stmt));

	node->type = t_member_stmt_var;
	node->data.var = var;

	free(node);
}

is_member_stmt* free_member_stmt_func_def(is_func_def* func_def)
{
	is_member_stmt* node = (is_member_stmt*)malloc(sizeof(is_member_stmt));

	node->type = t_member_stmt_func_def;
	node->data.func_def = func_def;

	free(node);
}

is_new_op* free_new_op(is_type_object* type, is_dims* dims)
{
	is_new_op* node = (is_new_op*)malloc(sizeof(is_new_op));

	node->type_object = type;
	node->dims = dims;

	free(node);
}

is_return* free_return(is_expr* value)
{
	is_return *node = (is_return*)malloc(sizeof(is_return));
	node->value = value;

	free(node);
}

is_stmt* free_stmt_stmt_list(is_stmt_list* stmt_list)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_stmt_list;
	node->data.stmt_list = stmt_list;

	free(node);
}

is_stmt* free_stmt_var_stmt(is_var_stmt* var_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_var_stmt;
	node->data.var = var_stmt;

	free(node);
}

is_stmt* free_stmt_assign_op(is_assign_op* assign_op)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_assign;
	node->data.assign = assign_op;

	free(node);
}

is_stmt* free_stmt_incr_op(is_incr_op* incr_op)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_incr;
	node->data.incr = incr_op;

	free(node);
}

is_stmt* free_stmt_if(is_if* if_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_if;
	node->data.if_stmt = if_stmt;

	free(node);
}

is_stmt* free_stmt_loop_stmt(is_loop_stmt* loop_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_loop;
	node->data.loop = loop_stmt;

	free(node);
}

is_stmt* free_stmt_func_call(is_func_call* func_call)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_func_call;
	node->data.func_call = func_call;

	free(node);
}

is_stmt* free_stmt_switch(is_switch* switch_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_switch;
	node->data.switch_stmt = switch_stmt;

	free(node);
}

is_stmt* free_stmt_break(is_break* break_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_break;
	node->data.break_stmt = break_stmt;

	free(node);
}

is_stmt* free_stmt_continue(is_continue* continue_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_continue;
	node->data.continue_stmt = continue_stmt;

	free(node);
}

is_stmt* free_stmt_return(is_return* return_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_return;
	node->data.return_stmt = return_stmt;

	free(node);
}

is_stmt_list* free_stmt_list(is_stmt* stmt, is_stmt_list* next)
{
	is_stmt_list* node = (is_stmt_list*)malloc(sizeof(is_stmt_list));
	
	node->node = stmt;
	node->next = next;

	free(node);
}

is_switch* free_switch(is_expr* expr, is_switch_stmt_list* list)
{
	is_switch *node = (is_switch*)malloc(sizeof(is_switch));

	node->expr = expr;
	node->list = list;

	free(node);
}

is_switch_stmt* free_switch_stmt_default(is_stmt_list* stmt_list)
{
	is_switch_stmt* node = (is_switch_stmt*)malloc(sizeof(is_switch_stmt*));
	
	node->type = t_switch_stmt_default;
	node->data.default_stmt_list = stmt_list;

	free(node);
}

is_switch_stmt* free_switch_stmt_case(is_constant* constant, is_stmt_list* stmt_list)
{
	is_switch_stmt* node = (is_switch_stmt*)malloc(sizeof(is_switch_stmt*));
	
	node->type = t_switch_stmt_case;
	node->data.case_stmt.constant = constant;
	node->data.case_stmt.list = stmt_list;

	free(node);
}

is_switch_stmt_list* free_switch_stmt_list(is_switch_stmt* stmt, is_switch_stmt_list* next)
{
	is_switch_stmt_list* node = (is_switch_stmt_list*)malloc(sizeof(is_switch_stmt_list*));
	
	node->node = stmt;
	node->next = next;

	free(node);
}

is_ternary_op* free_ternary_op(is_expr* cond, is_expr* then_expr, is_expr* else_expr)
{
	is_ternary_op* node = (is_ternary_op*)malloc(sizeof(is_ternary_op));

	node->if_expr = cond;
	node->then_expr = then_expr;
	node->else_expr = else_expr;

	free(node);
}

is_type_decl* free_type_decl_object(is_type_object* object)
{
	is_type_decl* node = (is_type_decl*)malloc(sizeof(is_type_decl));

	node->type = t_type_decl_type_object;
	node->data.type_object = object;

	free(node);
}

is_type_decl* free_type_decl_array(is_array_decl* array)
{
	is_type_decl* node = (is_type_decl*)malloc(sizeof(is_type_decl));

	node->type = t_type_decl_array_decl;
	node->data.array = array;

	free(node);
}

is_type_object* free_type_object(is_type_native type)
{
	is_type_object* node = (is_type_object*)malloc(sizeof(is_type_object));

	node->type = type;

	free(node);
}

is_unary_op* free_unary_op_incr(is_incr_op* incr_op)
{
	is_unary_op* node = (is_unary_op*)malloc(sizeof(is_unary_op));

	node->type = t_unary_op_incr_op;
	node->data.incr = incr_op;
	
	free(node);
}

is_unary_op* free_unary_op_operation(type_unary_op_operator op, is_expr* expr)
{
	is_unary_op* node = (is_unary_op*)malloc(sizeof(is_unary_op));

	node->type = t_unary_op_operation;
	node->data.operation.op = op;
	node->data.operation.expr = expr;
 
	free(node);
}

is_var* free_var_id(is_id* id)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_id;
	node->data.id = id;

	free(node);
}

is_var* free_var_new_op(is_new_op* new_op)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_new_op;
	node->data.new_op = new_op;

	free(node);
}

is_var* free_var_var_subscript(is_var* var, is_dims_sized* position)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_array;
	node->data.array.var = var;
	node->data.array.dims = position;

	free(node);
}

is_var* free_var_func_subscript(is_func_call* func_call, is_dims_sized* position)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_func_call;
	node->data.func_call.call = func_call;
	node->data.func_call.dims = position;

	free(node);
}

is_var_def* free_var_def(is_id* id, is_dims_empty_list dims, is_var_initializer* init)
{
	is_var_def* node = (is_var_def*)malloc(sizeof(is_var_def));

	node->id = id;
	node->dims = dims;
	node->var_init = init;

	free(node);
}

is_var_def_list* free_var_def_list(is_var_def* var_def, is_var_def_list* next)
{
	is_var_def_list* node = (is_var_def_list*)malloc(sizeof(is_var_def_list));
	
	node->node = var_def;
	node->next = next;

	free(node);
}

*/

void free_var_defs(is_var_defs* node)
{
	if (node)
	{
		free_type_decl(type);
		free_
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
		}, 
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

void free_while(is_while* node)
{
	if (node)
	{
		free_expr(node->cond);
		free_stmt(node->body);
		free(node);
	}
}

