#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/free.h"

extern int yyline;

/* LEX */
is_id* insert_id(char* data)
{
	is_id* node = (is_id*)malloc(sizeof(is_id));
	node->name = __strdup(data);
	node->line = yyline;

	return node;
}

is_constant* insert_constant_bool(bool value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));

	node->type = t_constant_bool;
	node->value.bool_val = value;
	node->line = yyline;

	return node;
}

is_constant* insert_constant_long(long long value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));

	node->type = t_constant_long;
	node->value.long_val = value;
	node->line = yyline;

	return node;
}

is_constant* insert_constant_double(long double value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));

	node->type = t_constant_double;
	node->value.double_val = value;
	node->line = yyline;

	return node;
}

is_constant* insert_constant_char(char* value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));

	node->type = t_constant_char;
	node->value.string_val = __strdup(value);
	node->line = yyline;

	return node;
}

is_constant* insert_constant_string(char* value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));

	node->type = t_constant_string;
	node->value.string_val = __strdup(value);
	node->line = yyline;

	return node;
}

/* YACC */
is_array_decl* insert_array_decl (is_type_object* type, is_dims_empty_list* dims)
{
	is_array_decl *node = (is_array_decl*)malloc(sizeof(is_array_decl));
	node->type = type;
	node->dims = dims;
	node->line = yyline;

	return node;
}

is_assign_op* insert_assign_op (is_var* var, type_assign_op type, is_expr* expr)
{
	is_assign_op *node = (is_assign_op*)malloc(sizeof(is_assign_op));

	node->var = var;
	node->type = type;
	node->expr = expr;
	node->line = yyline;

	return node;
}

is_binary_op* insert_binary_op_operation (is_expr* left, type_binary_op type, is_expr* right)
{
	is_binary_op* node = (is_binary_op*)malloc(sizeof(is_binary_op));

	node->type = type;
	node->data.operands.left = left;
	node->data.operands.right = right;
	node->line = yyline;

	return node;
}

is_binary_op* insert_binary_op_assign (is_assign_op* assign)
{
	is_binary_op* node = (is_binary_op*)malloc(sizeof(is_binary_op));

	node->type = t_binary_op_assign;
	node->data.assign = assign;
	node->line = yyline;

	return node;
}

is_break* insert_break (is_id* label)
{
	is_break *node = (is_break*)malloc(sizeof(is_break));

	node->label = label;
	node->line = yyline;

	return node;
}

is_class_stmt_list* insert_class_stmt_list (is_class_stmt* stmt, is_class_stmt_list* next)
{
	is_class_stmt_list* node = (is_class_stmt_list*)malloc(sizeof(is_class_stmt_list));
	
	node->node = stmt;
	node->next = next;
	node->line = yyline;

	return node;
}

is_class_def* insert_class_def (is_id* id, is_class_stmt_list* body)
{
	is_class_def *node = (is_class_def*)malloc(sizeof(is_class_def));

	node->id = id;
	node->body = body;
	node->line = yyline;

	return node;
}

is_class_stmt* insert_class_stmt (is_class_stmt_privacy* privacy, is_class_stmt_scope* scope, is_member_stmt* stmt)
{
	is_class_stmt *node = (is_class_stmt*)malloc(sizeof(is_class_stmt));

	node->privacy = privacy;
	node->scope = scope;
	node->stmt = stmt;

	return node;
}

is_class_stmt_privacy* insert_class_stmt_privacy(is_class_stmt_privacy type)
{
	is_class_stmt_privacy* node = (is_class_stmt_privacy*)malloc(sizeof(is_class_stmt_privacy));
	*node = type;
	
	return node;
}

is_class_stmt_scope* insert_class_stmt_scope (bool b_final, bool b_static) /* static is a reserved keyword */
{
	is_class_stmt_scope *node = (is_class_stmt_scope*)malloc(sizeof(is_class_stmt_scope));

	node->b_final = b_final;
	node->b_static = b_static;
	node->line = yyline;

	return node;
}

is_continue* insert_continue (is_id* label)
{
	is_continue *node = (is_continue*)malloc(sizeof(is_continue));
	node->label = label;
	node->line = yyline;

	return node;
}

is_dims* insert_dims(is_dims_sized_list* sized, is_dims_empty_list* empty)
{
	is_dims* node = (is_dims*)malloc(sizeof(is_dims));

	node->sized = sized;
	node->empty = empty;
	node->line = yyline;

	return node;
}

is_dims_empty_list* insert_dims_empty_list(is_dims_empty_list* prev)
{
	is_dims_empty_list* node;

	if (prev)
	{
		prev->size++;
		return prev;
	}

	node = (is_dims_empty_list*)malloc(sizeof(is_dims_empty_list));
	node->size = 1;
	node->line = yyline;

	return node;
}

is_dims_sized_list* insert_dims_sized_list(is_dims_sized_list* prev, is_dims_sized* dims)
{
	is_dims_sized_list* last;
	is_dims_sized_list* node = (is_dims_sized_list*)malloc(sizeof(is_dims_sized_list));

	node->node = dims;
	node->next = NULL;
	node->line = yyline;

	if (!prev)
		return node;

	last = prev;
	while (last->next != NULL)
		last = last->next;

	last->next = node;
	return prev;
}

is_do_while *insert_do_while(is_stmt* body, is_expr* cond)
{
	is_do_while *node = (is_do_while*)malloc(sizeof(is_do_while));

	node->body = body;
	node->cond = cond;
	node->line = yyline;

	return node;
}

is_expr* insert_expr_var(is_var* var)
{
	is_expr* node = (is_expr*)malloc(sizeof(is_expr));

	node->type = t_expr_var;
	node->data.var = var;
	node->line = yyline;

	return node;
}

is_expr* insert_expr_new_op(is_new_op* new_op)
{
	is_expr* node = (is_expr*)malloc(sizeof(is_expr));

	node->type = t_expr_new_op;
	node->data.new_op = new_op;
	node->line = yyline;

	return node;
}

is_expr* insert_expr_type_cast(is_expr* expr, is_type_decl* type)
{
	is_expr* node = (is_expr*)malloc(sizeof(is_expr));

	node->type = t_expr_type_cast;

	node->data.type_cast.expr = expr;
	node->data.type_cast.type = type;
	node->line = yyline;

	return node;
}

is_expr* insert_expr_constant(is_constant* constant)
{
	is_expr* node = (is_expr*)malloc(sizeof(is_expr));

	node->type = t_expr_constant;
	node->data.constant = constant;
	node->line = yyline;

	return node;
}

is_expr* insert_expr_func_call(is_func_call* func_call)
{
	is_expr* node = (is_expr*)malloc(sizeof(is_expr));

	node->type = t_expr_func_call;
	node->data.func_call = func_call;
	node->line = yyline;

	return node;
}

is_expr* insert_expr_expr_op(is_expr_op* expr_op)
{
	is_expr* node = (is_expr*)malloc(sizeof(is_expr));

	node->type = t_expr_operation;
	node->data.operation = expr_op;
	node->line = yyline;

	return node;
}

is_expr_list* insert_expr_list (is_expr* expr, is_expr_list* next)
{
	is_expr_list* node = (is_expr_list*)malloc(sizeof(is_expr_list));
	
	node->node = expr;
	node->next = next;
	node->line = yyline;

	return node;
}

is_expr_op* insert_expr_op_unary (is_unary_op* op)
{
	is_expr_op* node = (is_expr_op*)malloc(sizeof(is_expr_op));

	node->type = t_expr_op_unary;
	node->data.unary = op;
	node->line = yyline;

	return node;
}

is_expr_op* insert_expr_op_binary(is_binary_op* op)
{
	is_expr_op* node = (is_expr_op*)malloc(sizeof(is_expr_op));

	node->type = t_expr_op_binary;
	node->data.binary = op;
	node->line = yyline;

	return node;
}

is_expr_op* insert_expr_op_ternary(is_ternary_op* op)
{
	is_expr_op* node = (is_expr_op*)malloc(sizeof(is_expr_op));

	node->type = t_expr_op_ternary;
	node->data.ternary = op;
	node->line = yyline;

	return node;
}

is_for* insert_for(is_for_init *init, is_for_cond *cond, is_for_inc *inc, is_stmt* body)
{
	is_for *node = (is_for*)malloc(sizeof(is_for));

	node->init = init;
	node->cond = cond;
	node->inc = inc;
	node->body = body;
	node->line = yyline;

	return node;
}

is_for_expr* insert_for_expr_incr(is_incr_op* incr)
{
	is_for_expr* node = (is_for_expr*)malloc(sizeof(is_for_expr));

	node->type = t_for_expr_incr;
	node->data.incr = incr;
	node->line = yyline;

	return node;
}

is_for_expr* insert_for_expr_assign(is_assign_op* assign)
{
	is_for_expr* node = (is_for_expr*)malloc(sizeof(is_for_expr));

	node->type = t_for_expr_assign;
	node->data.assign = assign;
	node->line = yyline;

	return node;
}

is_for_expr* insert_for_expr_func_call(is_func_call* func_call)
{
	is_for_expr* node = (is_for_expr*)malloc(sizeof(is_for_expr));

	node->type = t_for_expr_func_call;
	node->data.func_call = func_call;
	node->line = yyline;

	return node;
}

is_for_expr_list* insert_for_expr_list(is_for_expr* expr, is_for_expr_list* next)
{
	is_for_expr_list* node = (is_for_expr_list*)malloc(sizeof(is_for_expr_list));
	
	node->node = expr;
	node->next = next;
	node->line = yyline;

	return node;
}

is_for_init* insert_for_init_var_defs(is_var_defs* var_defs)
{
	is_for_init* node = (is_for_init*)malloc(sizeof(is_for_init));

	node->type = t_for_init_var_defs;
	node->data.var_defs = var_defs;
	node->line = yyline;

	return node;
}

is_for_init* insert_for_init_for_expr_list(is_for_expr_list* expr_list)
{
	is_for_init* node = (is_for_init*)malloc(sizeof(is_for_init));

	node->type = t_for_init_for_expr_list;
	node->data.expr_list = expr_list;
	node->line = yyline;

	return node;
}

is_func_call* insert_func_call(is_id* id, is_func_call_arg_list* args)
{
	is_func_call* node = (is_func_call*)malloc(sizeof(is_func_call));

	node->id = id;
	node->args = args;
	node->line = yyline;

	return node;
}


is_func_def* insert_func_def(is_type_decl* type, is_id* id, is_func_def_arg_list* args, is_stmt_list* body)
{
	is_func_def* node = (is_func_def*)malloc(sizeof(is_func_def));

	node->type = type;
	node->id = id;
	node->args = args;
	node->body = body;
	node->line = yyline;

	return node;
}

is_func_def_arg* insert_func_def_arg(is_type_decl* type, is_id* id)
{
	is_func_def_arg* node = (is_func_def_arg*)malloc(sizeof(is_func_def_arg));

	node->type = type;
	node->id = id;
	node->line = yyline;

	return node;
}

is_func_def_arg_list* insert_func_def_arg_list(is_func_def_arg* arg, is_func_def_arg_list* next)
{
	is_func_def_arg_list* node = (is_func_def_arg_list*)malloc(sizeof(is_func_def_arg_list));
	
	node->node = arg;
	node->next = next;
	node->line = yyline;

	return node;
}

is_if* insert_if(is_expr* cond, is_stmt* then_body, is_stmt* else_body)
{
	is_if *node = (is_if*)malloc(sizeof(is_if));
	node->cond = cond;
	node->then_body = then_body;
	node->else_body = else_body;
	node->line = yyline;

	return node;
}

is_incr_op* insert_incr_op(type_incr_op type, bool pre, is_var* var)
{
	is_incr_op* node = (is_incr_op*)malloc(sizeof(is_incr_op));

	node->type = type;
	node->pre = pre;
	node->var = var;
	node->line = yyline;

	return node;
}

is_loop_stmt* insert_loop_stmt_for(is_id* loop_label, is_for* for_stmt)
{
	is_loop_stmt *node = (is_loop_stmt*)malloc(sizeof(is_loop_stmt));

	node->type = t_loop_stmt_for;
	node->loop_label = loop_label;
	node->data.for_stmt = for_stmt;
	node->line = yyline;

	return node;
}

is_loop_stmt* insert_loop_stmt_while(is_id* loop_label, is_while* while_stmt)
{
	is_loop_stmt *node = (is_loop_stmt*)malloc(sizeof(is_loop_stmt));

	node->type = t_loop_stmt_while;
	node->loop_label = loop_label;
	node->data.while_stmt = while_stmt;
	node->line = yyline;

	return node;
}

is_loop_stmt* insert_loop_stmt_do_while(is_id* loop_label, is_do_while* do_while_stmt)
{
	is_loop_stmt *node = (is_loop_stmt*)malloc(sizeof(is_loop_stmt));

	node->type = t_loop_stmt_do_while;
	node->loop_label = loop_label;
	node->data.do_while_stmt = do_while_stmt;
	node->line = yyline;

	return node;
}

is_member_stmt* insert_member_stmt_var(is_var_stmt* var)
{
	is_member_stmt* node = (is_member_stmt*)malloc(sizeof(is_member_stmt));

	node->type = t_member_stmt_var;
	node->data.var = var;
	node->line = yyline;

	return node;
}

is_member_stmt* insert_member_stmt_func_def(is_func_def* func_def)
{
	is_member_stmt* node = (is_member_stmt*)malloc(sizeof(is_member_stmt));

	node->type = t_member_stmt_func_def;
	node->data.func_def = func_def;
	node->line = yyline;

	return node;
}

is_new_op* insert_new_op(is_type_object* type, is_dims* dims)
{
	is_new_op* node = (is_new_op*)malloc(sizeof(is_new_op));

	node->type_object = type;
	node->dims = dims;
	node->line = yyline;

	return node;
}

is_return* insert_return(is_expr* value)
{
	is_return *node = (is_return*)malloc(sizeof(is_return));
	node->value = value;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_stmt_list(is_stmt_list* stmt_list)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_stmt_list;
	node->data.stmt_list = stmt_list;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_var_stmt(is_var_stmt* var_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_var_stmt;
	node->data.var = var_stmt;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_assign_op(is_assign_op* assign_op)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_assign;
	node->data.assign = assign_op;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_incr_op(is_incr_op* incr_op)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_incr;
	node->data.incr = incr_op;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_if(is_if* if_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_if;
	node->data.if_stmt = if_stmt;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_loop_stmt(is_loop_stmt* loop_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_loop;
	node->data.loop = loop_stmt;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_func_call(is_func_call* func_call)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_func_call;
	node->data.func_call = func_call;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_switch(is_switch* switch_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_switch;
	node->data.switch_stmt = switch_stmt;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_break(is_break* break_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_break;
	node->data.break_stmt = break_stmt;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_continue(is_continue* continue_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_continue;
	node->data.continue_stmt = continue_stmt;
	node->line = yyline;

	return node;
}

is_stmt* insert_stmt_return(is_return* return_stmt)
{
	is_stmt* node = (is_stmt*)malloc(sizeof(is_stmt));

	node->type = t_stmt_return;
	node->data.return_stmt = return_stmt;
	node->line = yyline;

	return node;
}

is_stmt_list* insert_stmt_list(is_stmt* stmt, is_stmt_list* next)
{
	is_stmt_list* node = (is_stmt_list*)malloc(sizeof(is_stmt_list));
	
	node->node = stmt;
	node->next = next;
	node->line = yyline;

	return node;
}

is_switch* insert_switch(is_expr* expr, is_switch_stmt_list* list)
{
	is_switch *node = (is_switch*)malloc(sizeof(is_switch));

	node->expr = expr;
	node->list = list;
	node->line = yyline;

	return node;
}

is_switch_stmt* insert_switch_stmt_default(is_stmt_list* stmt_list)
{
	is_switch_stmt* node = (is_switch_stmt*)malloc(sizeof(is_switch_stmt));
	
	node->type = t_switch_stmt_default;
	node->constant = NULL;
	node->list = stmt_list;
	node->line = yyline;

	return node;
}

is_switch_stmt* insert_switch_stmt_case(is_constant* constant, is_stmt_list* stmt_list)
{
	is_switch_stmt* node = (is_switch_stmt*)malloc(sizeof(is_switch_stmt));
	
	node->type = t_switch_stmt_case;
	node->constant = constant;
	node->list = stmt_list;
	node->line = yyline;

	return node;
}

is_switch_stmt_list* insert_switch_stmt_list(is_switch_stmt* stmt, is_switch_stmt_list* next)
{
	is_switch_stmt_list* node = (is_switch_stmt_list*)malloc(sizeof(is_switch_stmt_list));
	
	node->node = stmt;
	node->next = next;
	node->line = yyline;

	return node;
}

is_ternary_op* insert_ternary_op(is_expr* cond, is_expr* then_expr, is_expr* else_expr)
{
	is_ternary_op* node = (is_ternary_op*)malloc(sizeof(is_ternary_op));

	node->if_expr = cond;
	node->then_expr = then_expr;
	node->else_expr = else_expr;
	node->line = yyline;

	return node;
}

is_type_decl* insert_type_decl_object(is_type_object* object)
{
	is_type_decl* node = (is_type_decl*)malloc(sizeof(is_type_decl));

	node->type = t_type_decl_type_object;
	node->data.type_object = object;
	node->line = yyline;

	return node;
}

is_type_decl* insert_type_decl_array(is_array_decl* array)
{
	is_type_decl* node = (is_type_decl*)malloc(sizeof(is_type_decl));

	node->type = t_type_decl_array_decl;
	node->data.array = array;
	node->line = yyline;

	return node;
}

is_type_object* insert_type_object(is_type_native type)
{
	is_type_object* node = (is_type_object*)malloc(sizeof(is_type_object));

	node->type = type;
	node->line = yyline;

	return node;
}

is_unary_op* insert_unary_op_incr(is_incr_op* incr_op)
{
	is_unary_op* node = (is_unary_op*)malloc(sizeof(is_unary_op));

	node->type = t_unary_op_incr_op;
	node->data.incr = incr_op;
	node->line = yyline;

	return node;
}

is_unary_op* insert_unary_op_operation(type_unary_op_operator op, is_expr* expr)
{
	is_unary_op* node = (is_unary_op*)malloc(sizeof(is_unary_op));

	node->type = t_unary_op_operation;
	node->data.operation.op = op;
	node->data.operation.expr = expr;
 	node->line = yyline;

	return node;
}

is_var* insert_var_id(is_id* id)
{
	is_var* node = (is_var*)malloc(sizeof(is_var));

	node->type = t_var_id;
	node->data.id = id;
	node->line = yyline;

	/* semantics */
	node->s_type = NULL;

	return node;
}

is_var* insert_var_new_op(is_new_op* new_op)
{
	is_var* node = (is_var*)malloc(sizeof(is_var));

	node->type = t_var_new_op;
	node->data.new_op = new_op;
	node->line = yyline;

	/* semantics */
	node->s_type = NULL;

	return node;
}

is_var* insert_var_var_subscript(is_var* var, is_dims_sized* position)
{
	is_var* node = (is_var*)malloc(sizeof(is_var));

	node->type = t_var_array;
	node->data.array.var = var;
	node->data.array.dims = position;
	node->line = yyline;

	/* semantics */
	node->s_type = NULL;

	return node;
}

is_var* insert_var_func_subscript(is_func_call* func_call, is_dims_sized* position)
{
	is_var* node = (is_var*)malloc(sizeof(is_var));

	node->type = t_var_func_call;
	node->data.func_call.call = func_call;
	node->data.func_call.dims = position;
	node->line = yyline;

	/* semantics */
	node->s_type = NULL;

	return node;
}

is_var_def* insert_var_def(is_var_def_left* left, is_var_initializer* init)
{
	is_var_def* node = (is_var_def*)malloc(sizeof(is_var_def));

	node->left = left;
	node->var_init = init;
	node->line = yyline;

	return node;
}

is_var_def_left* insert_var_def_left_dims(is_id* id, is_dims* dims)
{
	is_var_def_left* node = (is_var_def_left*)malloc(sizeof(is_var_def_left));

	node->type = t_var_def_left_dims;	
	node->id = id;
	node->data.dims = dims;
	node->line = yyline;

	return node;
}

is_var_def_left* insert_var_def_left_empty(is_id* id, is_dims_empty_list* empty)
{
	is_var_def_left* node = (is_var_def_left*)malloc(sizeof(is_var_def_left));

	node->type = t_var_def_left_empty;	
	node->id = id;
	node->data.empty = empty;
	node->line = yyline;

	return node;
}

is_var_def_list* insert_var_def_list(is_var_def* var_def, is_var_def_list* next)
{
	is_var_def_list* node = (is_var_def_list*)malloc(sizeof(is_var_def_list));
	
	node->node = var_def;
	node->next = next;
	node->line = yyline;

	return node;
}

is_var_defs* insert_var_defs(is_type_decl* type, is_var_def_list* list)
{
	is_var_defs* node = (is_var_defs*)malloc(sizeof(is_var_defs));
	
	node->type = type;
	node->list = list;
	node->line = yyline;

	return node;
}

is_var_initializer* insert_var_initializer_array(is_var_initializer_list* list)
{
	is_var_initializer* node = (is_var_initializer*)malloc(sizeof(is_var_initializer));

	node->type = t_var_initializer_val_arr;
	node->data.array = list;
	node->line = yyline;

	/* semantics */
	node->s_type = NULL;

	return node;
}

is_var_initializer* insert_var_initializer_expr(is_expr* expr)
{
	is_var_initializer* node = (is_var_initializer*)malloc(sizeof(is_var_initializer));

	node->type = t_var_initializer_expr;
	node->data.expr = expr;
	node->line = yyline;

	/* semantics */
	node->s_type = NULL;

	return node;
}

is_var_initializer_list* insert_var_initializer_list(is_var_initializer_list* prev, is_var_initializer* var_init)
{
	is_var_initializer_list* last;
	is_var_initializer_list* node = (is_var_initializer_list*)malloc(sizeof(is_var_initializer_list));

	node->node = var_init;
	node->next = NULL;
	node->line = yyline;

	/* semantics */
	node->s_type = NULL;

	if (!prev)
		return node;

	last = prev;
	while (last->next != NULL)
		last = last->next;

	last->next = node;
	return prev;
}

is_while* insert_while(is_expr* cond, is_stmt* body)
{
	is_while *node = (is_while*)malloc(sizeof(is_while));

	node->cond = cond;
	node->body = body;
	node->line = yyline;

	return node;
}
