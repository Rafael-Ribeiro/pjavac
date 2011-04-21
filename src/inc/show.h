#ifndef SHOW_H
#define SHOW_H

/* LEX */

void show_id(is_id* node);
void show_constant(is_constant* node);

/* YACC */
void show_dims_empty_list(is_dims_empty_list val);

/* enums */
void show_class_stmt_privacy(is_class_stmt_privacy val);
void show_type_native(is_type_native val);

/* nodes */
void show_application(is_application* node, int tablevel);
void show_array_decl(is_array_decl* node);
void show_assign_op(is_assign_op* node);
void show_binary_op_operation(is_binary_op* node);
void show_break(is_break* node);
void show_class_def(is_class_def* node, int tablevel);
void show_class_stmt(is_class_stmt* node, int tablevel); 
void show_class_stmt_list(is_class_stmt_list* node, int tablevel); 
void show_class_stmt_scope(is_class_stmt_scope* node); 
void show_continue(is_continue* node);
void show_dims(is_dims* node);
void show_dims_sized(is_dims_sized* node);
void show_dims_sized_list(is_dims_sized_list* node);
void show_do_while(is_do_while* node, int tablevel); 
void show_expr(is_expr* node);
void show_expr_list(is_expr_list* node);
void show_expr_op(is_expr_op* node);
void show_for(is_for* node, int tablevel);
void show_for_cond(is_for_cond* node);
void show_for_expr(is_for_expr* node); 
void show_for_expr_list(is_for_expr_list* node); 
void show_for_inc(is_for_inc* node);
void show_for_init(is_for_init* node);
void show_func_call(is_func_call* node);
void show_func_call_arg_list(is_func_call_arg_list* node);
void show_func_def(is_func_def* node, int tablevel);
void show_func_def_arg(is_func_def_arg* node);
void show_func_def_arg_list(is_func_def_arg_list* node);
void show_func_def_args(is_func_def_args* node);
void show_if(is_if* node, int tablevel);
void show_incr_op(is_incr_op* node);
void show_loop_stmt(is_loop_stmt* node, int tablevel); 
void show_member_stmt(is_member_stmt* node, int tablevel);
void show_new_op(is_new_op* node);
void show_return(is_return* node);
void show_stmt(is_stmt* node, int tablevel);
void show_stmt_list(is_stmt_list* node, int tablevel); 
void show_switch(is_switch* node, int tablevel);
void show_switch_stmt(is_switch_stmt* node, int tablevel);
void show_switch_stmt_list(is_switch_stmt_list* node, int tablevel);
void show_ternary_op(is_ternary_op* node);
void show_type_decl(is_type_decl* node);
void show_type_object(is_type_object* node);
void show_unary_op(is_unary_op* node);
void show_var(is_var* node);
void show_var_def(is_var_def* node);
void show_var_def_list(is_var_def_list* node);
void show_var_defs(is_var_defs* node);
void show_var_stmt(is_var_stmt* node);
void show_var_initializer(is_var_initializer* node);
void show_var_initializer_list(is_var_initializer_list* node);
void show_while(is_while* node, int tablevel);

#endif
