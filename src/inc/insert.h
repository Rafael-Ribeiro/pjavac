#ifndef INSERT_H
#define INSERT_H

/* LEX */

char* __strcpy(const char*);

is_id* insert_id(char* data);

is_constant* insert_constant_bool(bool value);
is_constant* insert_constant_int(int value);
is_constant* insert_constant_long(long long value);
is_constant* insert_constant_float(float value);
is_constant* insert_constant_double(long double value);
is_constant* insert_constant_char(char* value);
is_constant* insert_constant_string(char* value);

/* YACC */
is_array_decl* insert_array_decl(is_type_object* type, is_dims_empty_list* dims);
is_assign_op* insert_assign_op(is_var* var, type_assign_op type, is_expr* expr);
is_binary_op* insert_binary_op_operation(is_expr* left, type_binary_op operation, is_expr* right);
is_binary_op* insert_binary_op_assign(is_assign_op* assign);

is_break* insert_break(is_id* label);

is_class_stmt_list* insert_class_stmt_list(is_class_stmt* stmt, is_class_stmt_list* next); 

is_class_def* insert_class_def(is_id* id, is_class_stmt_list* body);

is_class_stmt* insert_class_stmt(is_class_stmt_privacy* privacy, is_class_stmt_scope* scope, is_member_stmt* stmt); 

is_class_stmt_privacy* insert_class_stmt_privacy(is_class_stmt_privacy type);
is_class_stmt_scope* insert_class_stmt_scope(bool _final, bool _static); /* static is a reserved keyword */

is_continue* insert_continue(is_id* label);

is_dims* insert_dims(is_dims_sized_list* sized, is_dims_empty_list* empty);

is_dims_empty_list* new_dims_empty_list(int line, int size);
is_dims_empty_list* insert_dims_empty_list(is_dims_empty_list* prev);
is_dims_sized_list* insert_dims_sized_list(is_dims_sized_list* prev, is_dims_sized* dims);

is_do_while* insert_do_while(is_stmt* stmt, is_expr* cond); 

is_expr* insert_expr_var(is_var* var);
is_expr* insert_expr_new_op(is_new_op* new_op);
is_expr* insert_expr_type_cast(is_expr* expr, is_type_decl* type); 
is_expr* insert_expr_constant(is_constant* constant); 
is_expr* insert_expr_func_call(is_func_call* func_call); 
is_expr* insert_expr_expr_op(is_expr_op* expr_op); 

is_expr_list* insert_expr_list(is_expr* expr, is_expr_list* next);

is_expr_op* insert_expr_op_unary(is_unary_op* op);
is_expr_op* insert_expr_op_binary(is_binary_op* op);
is_expr_op* insert_expr_op_ternary(is_ternary_op* op);

is_for* insert_for(is_for_init* init, is_for_cond* cond, is_for_inc* inc, is_stmt* body);

is_for_expr* insert_for_expr_incr(is_incr_op* incr); 
is_for_expr* insert_for_expr_assign(is_assign_op* assign);
is_for_expr* insert_for_expr_func_call(is_func_call* func_call);

is_for_expr_list* insert_for_expr_list(is_for_expr* expr, is_for_expr_list* next); 

is_for_init* insert_for_init_var_defs(is_var_defs* var_defs);
is_for_init* insert_for_init_for_expr_list(is_for_expr_list* expr_list);
 	
is_func_call* insert_func_call(is_id* id, is_func_call_arg_list* args);

is_func_def* insert_func_def(is_type_decl* type, is_id* id, is_func_def_arg_list* args, is_stmt_list* body);

is_func_def_arg* insert_func_def_arg(is_type_decl* type, is_id* id);

is_func_def_arg_list* insert_func_def_arg_list(is_func_def_arg* arg, is_func_def_arg_list* next);

is_if* insert_if(is_expr* cond, is_stmt* then_body, is_stmt* else_body);

is_incr_op* insert_incr_op(type_incr_op type, bool pre, is_var* var);

is_loop_stmt* insert_loop_stmt_for(is_id* loop_label, is_for* for_stmt); 
is_loop_stmt* insert_loop_stmt_while(is_id* loop_label, is_while* while_stmt);
is_loop_stmt* insert_loop_stmt_do_while(is_id* loop_label, is_do_while* do_while_stmt);

is_member_stmt* insert_member_stmt_var(is_var_stmt* var);
is_member_stmt* insert_member_stmt_func_def(is_func_def* func_def);

is_new_op* insert_new_op(is_type_object* type, is_dims* dims);

is_return* insert_return(is_expr* value);

is_stmt* insert_stmt_stmt_list(is_stmt_list* stmt_list);
is_stmt* insert_stmt_var_stmt(is_var_stmt* var_stmt);
is_stmt* insert_stmt_assign_op(is_assign_op* assign_op);
is_stmt* insert_stmt_incr_op(is_incr_op* incr_op);
is_stmt* insert_stmt_if(is_if* if_stmt);
is_stmt* insert_stmt_loop_stmt(is_loop_stmt* loop_stmt);
is_stmt* insert_stmt_func_call(is_func_call* func_call);
is_stmt* insert_stmt_switch(is_switch* switch_stmt);
is_stmt* insert_stmt_break(is_break* break_stmt);
is_stmt* insert_stmt_continue(is_continue* continue_stmt);
is_stmt* insert_stmt_return(is_return* return_stmt);

is_stmt_list* insert_stmt_list(is_stmt* stmt, is_stmt_list* next); 
is_switch* insert_switch(is_label* label, is_expr* expr, is_switch_stmt_list* list);

is_switch_stmt* insert_switch_stmt_default(is_stmt_list* stmt_list);
is_switch_stmt* insert_switch_stmt_case(is_constant* constant, is_stmt_list* stmt_list);

is_switch_stmt_list* insert_switch_stmt_list(is_switch_stmt* stmt, is_switch_stmt_list* next);

is_ternary_op* insert_ternary_op(is_expr* cond, is_expr* then_expr, is_expr* else_expr);

is_type_decl* new_type_decl_void(int line);
is_type_decl* new_type_decl_string(int line);
is_type_decl* new_type_decl_object_dims(int line, is_type_object* object, is_dims* dims);
is_type_decl* insert_type_decl_object(is_type_object* object);
is_type_decl* insert_type_decl_array(is_array_decl* array);

is_type_object* insert_type_object(is_type_native type);

is_unary_op* insert_unary_op_incr(is_incr_op* incr_op);
is_unary_op* insert_unary_op_operation(type_unary_op_operator op, is_expr* expr);

is_var* insert_var_id(is_id* id);
is_var* insert_var_new_op(is_new_op* new_op);
is_var* insert_var_var_subscript(is_var* var, is_dims_sized* position);
is_var* insert_var_func_subscript(is_func_call* func_call, is_dims_sized* position);

is_var_def* insert_var_def(is_var_def_left* left, is_var_initializer* init);

is_var_def_list* insert_var_def_list(is_var_def* var_def, is_var_def_list* next);

is_var_def_left* insert_var_def_left(is_id* id, is_dims_empty_list* empty);

is_var_defs* insert_var_defs(is_type_decl* type, is_var_def_list* list);

is_var_initializer* insert_var_initializer_array(is_var_initializer_list* list);
is_var_initializer* insert_var_initializer_expr(is_expr* expr);

is_var_initializer_list* insert_var_initializer_list(is_var_initializer_list* prev, is_var_initializer* var_init);

is_while* insert_while(is_expr* cond, is_stmt* body);

#endif
