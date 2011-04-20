#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "inc/structures.h"
#include "inc/free.h"

/* LEX */
char* __strcpy(const char* data)
{
	char* dest;
	int len;

	len = strlen(data) + 1; /* +1 to include \0 on both malloc and strncpy */
	dest = (char*)malloc(sizeof(char)*len);
	strncpy(dest, data, len);

	return dest;
}

is_id* insert_id(char* data)
{
	is_id* node = (is_id*)malloc(sizeof(is_id));
	node->name = __strcpy(data);

	return node;
}

is_constant* insert_constant_bool(bool value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));
	node->value.bool_val = value;

	return node;
}

is_constant* insert_constant_long(long long value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));
	node->value.long_val = value;

	return node;
}

is_constant* insert_constant_double(long double value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));
	node->value.double_val = value;

	return node;
}

is_constant* insert_constant_char(char* value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));
	node->value.string_val = __strcpy(value);

	return node;
}

is_constant* insert_constant_string(char* value)
{
	is_constant* node = (is_constant*)malloc(sizeof(is_constant));
	node->value.string_val = __strcpy(value);

	return node;
}

/* YACC */
is_array_decl* insert_array_decl (is_type_object* type, is_dims_empty_list dims)
{
	is_array_decl *node = (is_array_decl*)malloc(sizeof(is_array_decl));
	node->type = type;
	node->dims = dims;

	return node;
}

is_assign_op* insert_assign_op (is_var* var, type_assign_op type, is_expr* expr)
{
	is_assign_op *node = (is_assign_op*)malloc(sizeof(is_assign_op));

	node->var = var;
	node->type = type;
	node->expr = expr;

	return NULL;
}

is_binary_op* insert_binary_op_operation (is_expr* left, type_binary_op operation, is_expr* right)
{
	return NULL;
}

is_binary_op* insert_binary_op_assign (is_assign_op* assign)
{
	return NULL;
}

is_break* insert_break (is_id* label)
{
	is_break *node = (is_break*)malloc(sizeof(is_break));
	node->label = label;

	return node;
}

is_class_stmt_list* insert_class_stmt_list (is_class_stmt* stmt, is_class_stmt_list* next)
{
	return NULL;
}

is_class_def* insert_class_def (is_id* id, is_class_stmt_list* body)
{
	is_class_def *node = (is_class_def*)malloc(sizeof(is_class_def));
	node->id = id;
	node->body = body;

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

	return node;
}

is_continue* insert_continue (is_id* label)
{
	is_continue *node = (is_continue*)malloc(sizeof(is_continue));
	node->label = label;

	return node;
}

is_dims* insert_dims (is_dims_sized_list* sized, is_dims_empty_list empty)
{
	return NULL;
}

/* this one is left recursive, can we swap it? if not attention to the constructors */
is_dims_sized_list* insert_dims_sized_list (is_dims_sized_list* prev, is_dims_sized* dims)
{
	return NULL;
}

is_do_while *insert_do_while (is_stmt* body, is_expr* cond)
{
	is_do_while *node = (is_do_while*)malloc(sizeof(is_do_while));
	node->body = body;
	node->cond = cond;

	return node;
}

is_expr* insert_expr_var(is_var* var)
{
	return NULL;
}

is_expr* insert_expr_new_op(is_new_op* new_op)
{
	return NULL;
}

is_expr* insert_expr_constant(is_constant* constant)
{
	return NULL;
}

is_expr* insert_expr_func_call(is_func_call* func_call)
{
	return NULL;
}

is_expr* insert_expr_expr_op(is_expr_op* expr_op)
{
	return NULL;
}

is_expr_list* insert_expr_list (is_expr* expr, is_expr_list* next)
{
	return NULL;
}

is_expr_op* insert_expr_op_unary (is_unary_op* op)
{
	return NULL;
}

is_expr_op* insert_expr_op_binary(is_binary_op* op)
{
	return NULL;
}

is_expr_op* insert_expr_op_ternary(is_ternary_op* op)
{
	return NULL;
}

is_for* insert_for(is_for_init *init, is_for_cond *cond, is_for_inc *inc, is_stmt* body)
{
	is_for *node = (is_for*)malloc(sizeof(is_for));

	node->init = init;
	node->cond = cond;
	node->inc = inc;
	node->body = body;

	return node;
}

is_for_expr* insert_for_expr_incr(is_incr_op* incr)
{
	return NULL;
}

is_for_expr* insert_for_expr_assign(is_assign_op* assign)
{
	return NULL;
}

is_for_expr* insert_for_expr_func_call(is_func_call* func_call)
{
	return NULL;
}

is_for_expr_list* insert_for_expr_list(is_for_expr* expr, is_for_expr_list* next)
{
	return NULL;
}

is_for_init* insert_for_init_var_defs(is_var_defs* var_defs)
{
	return NULL;
}

is_for_init* insert_for_init_expr_list(is_for_expr_list* expr_list)
{
	return NULL;
}

is_func_call* insert_func_call_id(is_id* id, is_func_call_arg_list* args)
{
	return NULL;
}

is_func_call* insert_func_call_sysout(is_func_call_arg_list* args)
{
	return NULL;
}

is_func_def* insert_func_def(is_type_decl* type, is_id* id, is_func_def_arg_list* args, is_stmt_list* body)
{
	return NULL;
}

is_func_def_arg* insert_func_def_arg(is_type_decl* type, is_id* id)
{
	return NULL;
}

is_func_def_arg_list* insert_func_def_arg_list(is_func_def_arg* arg, is_func_def_arg_list* next)
{
	return NULL;
}

is_if* insert_if(is_expr* cond, is_stmt* then_body, is_stmt* else_body)
{
	is_if *node = (is_if*)malloc(sizeof(is_if));
	node->cond = cond;
	node->then_body = then_body;
	node->else_body = else_body;

	return node;
}

is_incr_op* insert_incr_op(type_incr_op type, bool pre)
{
	return NULL;
}

is_loop_stmt* insert_loop_stmt_for(is_for* for_stmt)
{
	return NULL;
}

is_loop_stmt* insert_loop_stmt_while(is_while* while_stmt)
{
	return NULL;
}

is_loop_stmt* insert_loop_stmt_do_while(is_do_while* do_while_stmt)
{
	return NULL;
}

is_member_stmt* insert_member_stmt_var(is_var_stmt* var)
{
	return NULL;
}

is_member_stmt* insert_member_stmt_func(is_func_def* func_def)
{
	return NULL;
}

is_new_op* insert_new_op(is_type_object* type, is_dims* dims)
{
	return NULL;
}

is_return* insert_return(is_expr* value)
{
	is_return *node = (is_return*)malloc(sizeof(is_return));
	node->value = value;

	return node;
}

is_stmt* insert_stmt_stmt_list(is_stmt_list* stmt_list)
{
	return NULL;
}

is_stmt* insert_stmt_var_stmt(is_var_stmt* var_stmt)
{
	return NULL;
}

is_stmt* insert_stmt_assign_op(is_assign_op* assign_op)
{
	return NULL;
}

is_stmt* insert_stmt_incr_op(is_incr_op* incr_op)
{
	return NULL;
}

is_stmt* insert_stmt_if(is_if* if_stmt)
{
	return NULL;
}

is_stmt* insert_stmt_loop_stmt(is_loop_stmt* loop_stmt)
{
	return NULL;
}

is_stmt* insert_stmt_func_call(is_func_call* func_call)
{
	return NULL;
}

is_stmt* insert_stmt_switch(is_switch* switch_stmt)
{
	return NULL;
}

is_stmt* insert_stmt_break(is_break* break_stmt)
{
	return NULL;
}

is_stmt* insert_stmt_continue(is_continue* continue_stmt)
{
	return NULL;
}

is_stmt* insert_stmt_return(is_return* return_stmt)
{
	return NULL;
}

is_stmt_list* insert_stmt_list(is_stmt* stmt, is_stmt_list* next)
{
	return NULL;
}

is_switch* insert_switch(is_expr* expr, is_switch_stmt_list* list)
{
	is_switch *node = (is_switch*)malloc(sizeof(is_switch));

	node->expr = expr;
	node->list = list;

	return node;
}

is_switch_stmt* insert_switch_stmt_default(is_stmt_list* stmt_list)
{
	is_switch_stmt* node = (is_switch_stmt*)malloc(sizeof(is_switch_stmt*));
	
	node->type = t_switch_stmt_default;
	node->data.default_stmt_list = stmt_list;

	return node;
}

is_switch_stmt* insert_switch_stmt_case(is_constant* constant, is_stmt_list* stmt_list)
{
	is_switch_stmt* node = (is_switch_stmt*)malloc(sizeof(is_switch_stmt*));
	
	node->type = t_switch_stmt_case;
	node->data.case_stmt.constant = constant;
	node->data.case_stmt.list = stmt_list;

	return node;
}

is_switch_stmt_list* insert_switch_stmt_list(is_switch_stmt* stmt, is_switch_stmt_list* next)
{
	is_switch_stmt_list* node = (is_switch_stmt_list*)malloc(sizeof(is_switch_stmt_list*));
	
	node->node = stmt;
	node->next = next;

	return node;
}

is_ternary_op* insert_ternary_op(is_expr* cond, is_expr* then_expr, is_expr* else_expr)
{
	is_ternary_op* node = (is_ternary_op*)malloc(sizeof(is_ternary_op));

	node->if_expr = cond;
	node->then_expr = then_expr;
	node->else_expr = else_expr;

	return node;
}

is_type_decl* insert_type_decl_object(is_type_object* object)
{
	is_type_decl* node = (is_type_decl*)malloc(sizeof(is_type_decl));

	node->type = t_type_decl_type_object;
	node->data.type_object = object;

	return node;
}

is_type_decl* insert_type_decl_array(is_array_decl* array)
{
	is_type_decl* node = (is_type_decl*)malloc(sizeof(is_type_decl));

	node->type = t_type_decl_array_decl;
	node->data.array = array;

	return node;
}

is_type_object* insert_type_object(is_type_native type)
{
	is_type_object* node = (is_type_object*)malloc(sizeof(is_type_object));

	node->type = type;

	return node;
}

is_unary_op* insert_unary_op_incr(is_incr_op* incr_op)
{
	is_unary_op* node = (is_unary_op*)malloc(sizeof(is_unary_op));

	node->type = t_unary_op_incr_op;
	node->data.incr = incr_op;
	
	return node;
}

is_unary_op* insert_unary_op_operation(type_unary_op_operator op, is_expr* expr)
{
	is_unary_op* node = (is_unary_op*)malloc(sizeof(is_unary_op));

	node->type = t_unary_op_operation;
	node->data.operation.op = op;
	node->data.operation.expr = expr;
 
	return node;
}

is_var* insert_var_id(is_id* id)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_id;
	node->data.id = id;

	return node;
}

is_var* insert_var_new_op(is_new_op* new_op)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_new_op;
	node->data.new_op = new_op;

	return node;
}

is_var* insert_var_var_subscript(is_var* var, is_dims_sized* position)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_array;
	node->data.array.var = var;
	node->data.array.dims = position;

	return node;
}

is_var* insert_var_func_subscript(is_func_call* func_call, is_dims_sized* position)
{
	is_var* node = (is_var*)malloc(sizeof(is_var_def));

	node->type = t_var_func_call;
	node->data.func_call.call = func_call;
	node->data.func_call.dims = position;

	return node;
}

is_var_def* insert_var_def(is_id* id, is_dims_empty_list dims, is_var_initializer* init)
{
	is_var_def* node = (is_var_def*)malloc(sizeof(is_var_def));

	node->id = id;
	node->dims = dims;
	node->var_init = init;

	return node;
}

is_var_def_list* insert_var_def_list(is_var_def* var_def, is_var_def_list* next)
{
	is_var_def_list* node = (is_var_def_list*)malloc(sizeof(is_var_def_list));
	
	node->node = var_def;
	node->next = next;

	return node;
}

is_var_defs* insert_var_defs(is_type_decl* type, is_var_def_list* list)
{
	is_var_defs* node = (is_var_defs*)malloc(sizeof(is_var_defs));
	
	node->type = *type;
	free_type_decl(type);

	node->list = list;

	return node;
}

is_var_initializer* insert_var_initializer_array(is_var_initializer_list* list)
{
	is_var_initializer* node = (is_var_initializer*)malloc(sizeof(is_var_initializer));

	node->type = t_var_initializer_val_arr;
	node->data.array = list;

	return node;
}

is_var_initializer* insert_var_initializer_expr(is_expr* expr)
{
	is_var_initializer* node = (is_var_initializer*)malloc(sizeof(is_var_initializer));

	node->type = t_var_initializer_expr;
	node->data.expr = expr;

	return node;
}

is_var_initializer_list* insert_var_initializer_list(is_var_initializer_list* prev, is_var_initializer* var_init)
{
	is_var_initializer_list* node = (is_var_initializer_list*)malloc(sizeof(is_var_initializer_list));

	node->node = var_init;
	node->next = NULL;

	if (prev)
		prev->next = node;

	return node;
}

is_while* insert_while(is_expr* cond, is_stmt* body)
{
	is_while *node = (is_while*)malloc(sizeof(is_while));

	node->cond = cond;
	node->body = body;

	return node;
}

