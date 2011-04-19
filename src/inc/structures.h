#ifndef STRUCTURES_H
#define STRUCTURES_H

/* just because we can? */
typedef is_class_def is_application;

typedef struct
{
	is_type_object* type;
	is_dims_empty_list* dims;
} is_array_decl;

typedef enum {t_eq, t_shift_r_eq, t_shift_l_eq, t_add_eq, t_sub_eq, t_mul_eq, t_div_eq, t_mod_eq, t_and_eq, t_xor_eq, t_or_eq} type_assign_op;
typedef struct
{
	type_assign_op type;
	is_var* var;
	is_expr* expr;
} is_assign_op;

typedef enum {
	t_add, t_sub, t_mul, t_div, t_mod, t_and, t_or,
	t_xor, t_shift_r, t_shift_l, t_logic_and, t_logic_or,
	t_eq, t_ne, t_l, t_g, t_le, t_ge, t_eq3, t_ne3,
	t_assign
} type_binary_op;

typedef struct
{
	type_binary_op type;

	union
	{
		struct
		{
			expr* left;
			expr* right;
		} operands;
		is_assign_op* assign;
	} data;
} is_binary_op;

typedef struct
{
	is_id* label;	/* nullable */
} is_break;

typedef struct _is_class_decl_list
{
	is_class_decl decl;
	struct _is_class_decl_list* next;
} is_class_decl_list;


typedef struct
{
	is_id* id;
	is_class_decl_list* body;
} is_class_def;

typedef struct
{
	is_class_stmt_privacy* privacy; /* nullable */
	is_class_stmt_scope* scope;	/* nullable */
	is_member_stmt* member;
} is_class_stmt;

typedef enum {t_public, t_private} is_class_stmt_privacy;

typedef struct
{
	bool b_final;
	bool b_static;
} is_class_stmt_scope;

typedef struct
{
	is_id* label;	/* nullable */
} is_continue;

typedef struct
{
	is_dims_sized_list* sized;
	is_dims_empty_list empty; /* NOT nullable, 0 if not existant, 1+ otherwise */
} is_dims;

typedef int is_dims_empty_list;

typedef is_expr is_dims_sized;

typedef struct _is_dims_sized_list
{
	is_dims_sized* size;
	struct _is_dims_sized_list* next;
} is_dims_sized_list;

typedef struct
{
	is_stmt* body;
	is_expr* condition;
} is_do_while;

typedef enum {t_var, t_new_op, t_constant, t_func_call, t_operation} type_expr
typedef struct
{
	type_expr expr;
	union
	{
		is_var* var;
		is_new_op* new_op;
		is_constant* constant;
		is_func_call* func;
		is_expr_op* operation;
	} data;
} is_expr;

typedef struct _is_expr_list;
{
	is_expr* expr;
	struct *_is_expr_list next;
} is_expr_list;

typedef enum {t_unary, t_binary, t_ternary} type_expr_op
typedef struct
{
	type_expr_op type;
	union
	{
		is_unary_op* unary;
		is_binary_op* binary;
		is_ternary_op* ternary;
	} data;
} is_expr_op;

typedef struct
{
	is_for_init* init; /* nullable */
	is_for_cond* condition; /* nullable */
	is_for_inc* inc; /* nullable */
	is_stmt* body;
} is_for;

typedef is_expr is_for_cond;

typedef enum {t_incr, t_assign} type_for_expr;
typedef struct
{
	type_for_expr;
	union
	{
		is_incr_op* incr;
		is_assing_op* assign;
	} data;
} is_for_expr;

typedef struct _is_for_expr_list
{
	is_for_expr expr;
	struct _is_for_expr_list* next;
} is_for_expr_list


typedef enum {t_var_defs, t_for_expr_list} type_for_init;
typedef struct
{
	type_for_init;
	union
	{
		is_var_defs* vars;
		is_for_expr_list* expr_list;
	} data; 
} is_for_init;

typedef enum {t_id, t_sysout} type_func_call;
typedef struct
{
	type_func_call type;
	union
	{
		is_id* id; /* nullable */
		is_func_call_arg_list* args;
	} data;
} is_func_call; 

typedef is_expr_list is_func_call_arg_list;

typedef struct
{
	is_type_decl* type;
	is_id* id;
	is_func_def_args* args;
	is_stmt_list* body;
} is_func_def;

typedef struct
{
	is_type_decl* type;
	is_var* var;
} is_func_def_arg;

typedef struct _is_func_def_arg_list
{
	is_func_def_arg arg;
	struct is_func_def_arg_list* next;
} is_func_def_arg_list;

typedef is_func_def_arg_list is_func_def_args;

typedef struct
{
	is_expr* condition;
	is_stmt* then_body;
	is_stmt* else_body; /* nullable */
} is_if;

typedef enum {t_inc, t_dec} type_incr_op
typedef struct
{
	type_incr_op type;
	bool pre;
	is_var* var;
} is_incr_op;

typedef enum {t_for, t_while, t_do_while} type_loop_stmt;
typedef struct
{
	/* TODO: is_id* label; */
	type_loop_stmt type;
	union
	{
		is_for* for_stmt;
		is_while* while_stmt;
		is_do_while* do_while;
	} data;
} is_loop_stmt;

typedef enum {t_var, t_func} type_member_stmt;
typedef struct
{
	type_member_stmt type;
	union
	{
		is_var_stmt* var;
		is_func_def* func;
	} data;
} is_member_stmt;

typedef struct
{
	is_type_object *type_object;
	is_dims *dims;
} is_new_op;

typedef struct
{
	is_expr *expr;
} is_return;

typedef enum {t_empty, t_var_stmt, t_assign, t_incr, t_if, t_loop, t_func_call, t_switch, t_break, t_continue, t_return} type_stmt;
typedef struct
{
	type_stmt type;
	union
	{
		is_var_stmt *var;
		is_assign_op *assign;
		is_incr_op *incr;
		is_if *if_stmt;
		is_loop_stmt *loop;
		is_func_call *func_call;
		is_switch *switch_stmt;
		is_break *break_stmt;
		is_continue *continue_stmt;
		is_return *return_stmt;
	} data;
} is_stmt;

typedef struct
{
	is_expr *expr;
	is_switch_stmt_list *list;
} is_switch;

typedef enum {t_default, t_case} type_switch_stmt;
typedef struct
{
	type_switch_stmt type;
	is_stmt_list *list;
} is_switch_stmt;

typedef struct _is_switch_stmt_list
{
	is_switch_stmt *switch_case;
	struct _is_switch_stmt_list *next;
} is_switch_stmt_list;

typedef struct
{
	is_expr* if_expr;
	is_expr* then_expr;
	is_expr* else_expr;
} is_ternary_op;

typedef enum {t_type_object, t_array_decl} type_type_decl;
typedef struct
{
	type_type_decl type;
	union
	{
		is_type_object* type_object;
		is_array_decl* array;
	} data;
} is_type_decl;

typedef enum {t_bool, t_byte, t_char, t_double, t_float, t_int, t_long, t_short, t_void} is_type_native;
typedef struct
{
	is_type_native type;
} is_type_object;

typedef enum {t_plus, t_minus, t_not, t_bin_not} type_unary_op;
typedef struct
{
	type_unary_op type;
	union
	{
		is_expr *expr;
		is_incr_op *incr;
	} data;
} is_unary_op;

typedef enum {t_id, t_new_op, t_array, t_func_call} type_var;
typedef struct _is_var
{
	type_var type;
	union
	{
		is_id* id;
		is_new_op* new_op;
		struct
		{
			struct _is_var* var;
			is_dims_sized* dims;
		} array;
		struct
		{
			is_func_call* call;
			is_dims_sized* dims;
		} func_call;
	} data;
} is_var;

typedef struct
{
	is_id* id;
	is_var_initializer* var_init;
	is_dims_empty_list dims;
} is_var_def;

typedef struct _is_var_def_list
{
	is_var_def* var_def;
	struct _is_var_def_list* next;
} is_var_def_list;

typedef struct
{
	is_type_decl type;
	is_var_def_list list;
} is_var_defs;

typedef enum {t_val_arr, t_expr} type_var_initializer;
typedef struct
{
	type_var_initializer type;

	union
	{
		is_var_initializer_list* array;
		is_expr* expr;
	} data;
} is_var_initializer;

typedef struct _is_var_initializer_list
{
	is_var_initializer* init;
	struct _is_var_initializer_list* next;
} is_var_initializer_list;

typedef struct
{
	is_var_defs* defs;
} is_var_stmt;

typedef struct
{
	is_expr* condition;
	is_stmt* body;
} is_while;

#endif
