#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "inc/structures.h"

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
	is_break *break_node = (is_break*)malloc(sizeof(is_break));
	break_node->label = label;

	return break_node;
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

is_class_stmt_scope* insert_class_stmt_scope (bool _final, bool _static) /* static is a reserved keyword */
{
	return NULL;
}

is_continue* insert_continue (is_id* label)
{
	is_continue *continue_node = (is_continue*)malloc(sizeof(is_continue));
	continue_node->label = label;

	return continue_node;
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
	is_do_while *do_while_node = (is_do_while*)malloc(sizeof(is_do_while));
	do_while_node->body = body;
	do_while_node->cond = cond;

	return do_while_node;
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
	is_for *for_node = (is_for*)malloc(sizeof(is_for));

	for_node->init = init;
	for_node->cond = cond;
	for_node->inc = inc;
	for_node->body = body;

	return for_node;
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
	is_if *if_node = (is_if*)malloc(sizeof(is_if));
	if_node->cond = cond;
	if_node->then_body = then_body;
	if_node->else_body = else_body;

	return if_node;
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
	is_return *return_node = (is_return*)malloc(sizeof(is_return));
	return_node->value = value;

	return return_node;
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
	is_switch *switch_node = (is_switch*)malloc(sizeof(is_switch));
	switch_node->expr = expr;
	switch_node->list = list;

	return switch_node;
}

is_switch_stmt* insert_switch_stmt_default(is_stmt_list* stmt_list)
{
	return NULL;
}

is_switch_stmt* insert_switch_stmt_case(is_constant* constant, is_stmt_list* stmt_list)
{
	return NULL;
}

is_switch_stmt_list* insert_switch_stmt_list(is_switch_stmt* stmt, is_switch_stmt_list* next)
{
	return NULL;
}

is_ternary_op* insert_ternary_op(is_expr* cond, is_expr* then_expr, is_expr* else_expr)
{
	return NULL;
}

is_type_decl* insert_type_decl_object(is_type_object* object)
{
	return NULL;
}

is_type_decl* insert_type_decl_array(is_array_decl* array)
{
	return NULL;
}

is_type_object* insert_type_object(is_type_native type)
{
	return NULL;
}

is_unary_op* insert_unary_op_incr(is_incr_op* incr_op)
{
	return NULL;
}

is_unary_op* insert_unary_op_operation(type_unary_op_operator op, is_expr* expr)
{
	return NULL;
}

is_var* insert_var_id(is_id* id)
{
	return NULL;
}

is_var* insert_var_new_op(is_new_op* new_op)
{
	return NULL;
}

is_var* insert_var_var_subscript(is_var* var, is_dims_sized* position)
{
	return NULL;
}

is_var* insert_var_func_subscript(is_func_call* func_call, is_dims_sized* positon)
{
	return NULL;
}

is_var_def* insert_var_def(is_id* id, is_dims_empty_list dims, is_var_initializer* init)
{
	return NULL;
}

is_var_def_list* insert_var_def_list(is_var_def* var_def, is_var_def_list* next)
{
	return NULL;
}

is_var_defs* insert_var_defs(is_type_decl* type, is_var_def_list* list)
{
	return NULL;
}

is_var_initializer* insert_var_initializer_array(is_var_initializer_list* list)
{
	return NULL;
}

is_var_initializer* insert_var_initializer_expr(is_expr* expr)
{
	return NULL;
}

is_var_initializer_list* insert_var_initializer_list(is_var_initializer_list* prev, is_var_initializer* var_init)
{
	return NULL;
}

is_while* insert_while(is_expr* cond, is_stmt* body)
{
	is_while *while_node = (is_while*)malloc(sizeof(is_while));

	while_node->cond = cond;
	while_node->body = body;

	return while_node;
}

