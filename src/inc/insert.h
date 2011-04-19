#ifndef INSERT_H
#define INSERT_H

is_array_decl* insert_array_decl(is_type_object* type, is_dims_empty_list dims);
is_assign_op* insert_assign_op(is_var* var, type_assign_op type, is_expr* expr);
is_binary_op* insert_binary_op_operation(is_expr* left, t_binary_op_add, is_expr* right);
is_binary_op* insert_binary_op_assign(is_assign_op* assign);

is_break insert_break(is_id* label);

is_class_stmt_list* insert_class_decl_list(is_class_stmt* decl, is_class_stmt_list* next); 

is_class_def* insert_class_def(is_id* id, is_class_stmt_list* body);

is_class_stmt* insert_class_stmt(is_class_stmt_privacy* privacy, is_class_stmt_scope* scope, is_member_stmt* stmt); 

is_class_stmt_scope* insert_class_stmt_scope(bool final, bool static);

is_continue* insert_continue(is_id* label);

is_dims* insert_dims(is_sized_dims_list* sized, is_empty_dims_list empty);

/* this one is left recursive, can we swap it? if not attention to the constructors */
is_dims_sized_list* insert_dims_sized_list(is_dims_sized_list* prev, is_dims_sized* dims);

is_do_while insert_do_while($2, $5); 

is_expr* insert_expr_var($1);
is_expr* insert_expr_new_op($1);
is_expr* insert_expr_constant($1); 
is_expr* insert_expr_func_call($1); 
is_expr* insert_expr_expr_op($1); 

is_expr_list* insert_expr_list($1, NULL);

is_expr_op* insert_expr_op_unary($1);
is_expr_op* insert_expr_op_binary($1);
is_expr_op* insert_expr_op_ternary($1);

is_for* insert_for($3, $5, $7, $9);

is_for_expr* insert_for_expr_incr($1); 
is_for_expr* insert_for_expr_assign($1);

is_for_expr_list* insert_for_expr_list($1, NULL); 

is_for_init* insert_for_init_vars($1);
is_for_init* insert_for_init_expr_list($1);
 	
is_func_call* insert_func_call_id($1, $2); 
is_func_call* insert_func_call_sysout($2);
	;
is_func_def* insert_func_def($1, $2, $3, NULL);

is_func_def_arg* insert_func_def_arg($1, $2);

is_func_def_arg_list* insert_func_def_arg_list($1, NULL);

is_if* insert_if($3, $5, NULL);

is_incr_op* insert_incr_op(t_incr_op_inc, true);

is_loop_stmt* insert_loop_stmt_for($1); 
is_loop_stmt* insert_loop_stmt_while($1);
is_loop_stmt* insert_loop_stmt_do_while($1);

is_member_stmt* insert_member_stmt_var($1);
is_member_stmt* insert_member_stmt_func($1);

is_new_op* insert_new_op($2, $3);

is_return* insert_return(NULL);

is_stmt* insert_stmt_stmt_list($2);
is_stmt* insert_stmt_var_stmt($1);
is_stmt* insert_stmt_assign_op($1);
is_stmt* insert_stmt_incr_op($1);
is_stmt* insert_stmt_if($1);
is_stmt* insert_stmt_loop_stmt($1);
is_stmt* insert_stmt_func_call($1);
is_stmt* insert_stmt_switch($1);
is_stmt* insert_stmt_break($1);
is_stmt* insert_stmt_continue($1);
is_stmt* insert_stmt_return($1);

is_stmt_list* insert_stmt_list($1, $2); 
is_switch* insert_switch($3, $6);

is_switch_stmt* insert_switch_stmt_default(NULL);
is_switch_stmt* insert_switch_stmt_case($2, NULL);

is_switch_stmt_list* insert_switch_stmt_list($1, NULL);

is_ternary_op insert_ternary_op($1, $3, $5);

is_type_decl* insert_type_decl_object($1);
is_type_decl* insert_type_decl_array($1);

is_type_object* insert_type_object($1);

is_unary_op* insert_unary_op_incr($1);
is_unary_op* insert_unary_op_plus($2);
is_unary_op* insert_unary_op_minus($2);
is_unary_op* insert_unary_op_not($2);
is_unary_op* insert_unary_op_bin_not($2);

is_var* insert_var_id($1);
is_var* insert_var_new_op($2);
is_var* insert_var_var_subscript($1, $2);
is_var* insert_var_func_subscript($1, $2);

is_var_def* insert_var_def($1, $2, $4);

is_var_def_list* insert_var_def_list($1, NULL);

is_var_defs* insert_var_defs($1, $2);

is_var* insert_var_initializer_array($2);
is_var* insert_var_expr($1);

is_var_initializer* insert_var_initializer_list($1, $2);

is_while* insert_while($3, $5);

#endif
