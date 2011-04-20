#ifndef STRUCTURES_H
#define STRUCTURES_H

struct _is_array_decl;
struct _is_assign_op;
struct _is_binary_op;
struct _is_break;
struct _is_class_def;
struct _is_class_stmt;
struct _is_class_stmt_scope;
struct _is_constant;
struct _is_continue;
struct _is_dims;
struct _is_dims_sized_list;
struct _is_do_while;
struct _is_expr;
struct _is_expr_list;
struct _is_expr_op;
struct _is_for;
struct _is_for_expr;
struct _is_for_expr_list;
struct _is_for_init;
struct _is_func_call;
struct _is_func_def;
struct _is_func_def_arg;
struct _is_func_def_arg_list;
struct _is_id;
struct _is_if;
struct _is_incr_op;
struct _is_loop_stmt;
struct _is_member_stmt;
struct _is_new_op;
struct _is_return;
struct _is_stmt;
struct _is_switch;
struct _is_switch_stmt;
struct _is_switch_stmt_list;
struct _is_ternary_op;
struct _is_type_decl;
struct _is_type_object;
struct _is_unary_op;
struct _is_var;
struct _is_var_def;
struct _is_var_def_list;
struct _is_var_defs;
struct _is_var_initializer;
struct _is_var_initializer_list;
struct _is_var_stmt;
struct _is_while;

/***********************************************************************/
/* just because we can, this ones will be in the structures themselves */
typedef int is_dims_empty_list;
typedef struct _is_expr is_dims_sized;
typedef struct _is_expr is_for_cond;
typedef struct _is_for_expr_list is_for_inc;
typedef struct _is_var_defs is_var_stmt;
typedef struct _is_class_def is_application;
typedef struct _is_expr_list is_func_call_arg_list;
typedef struct _is_func_def_arg_list is_func_def_args;

/***********************************************************************/

typedef struct _is_array_decl
{
	struct _is_type_object* type;
	is_dims_empty_list dims;
} is_array_decl;

typedef enum
{
	t_assign_op_eq,
	t_assign_op_shift_r_eq,
	t_assign_op_shift_l_eq,
	t_assign_op_add_eq,
	t_assign_op_sub_eq,
	t_assign_op_mul_eq,
	t_assign_op_div_eq,
	t_assign_op_mod_eq,
	t_assign_op_and_eq,
	t_assign_op_xor_eq,
	t_assign_op_or_eq
} type_assign_op;

typedef struct _is_assign_op
{
	type_assign_op type;
	struct _is_var* var;
	struct _is_expr* expr;
} is_assign_op;

typedef enum
{
	t_binary_op_add,
	t_binary_op_sub,
	t_binary_op_mul,
	t_binary_op_div,
	t_binary_op_mod,
	t_binary_op_and,
	t_binary_op_or,
	t_binary_op_xor,
	t_binary_op_shift_r,
	t_binary_op_shift_l,
	t_binary_op_logic_and,
	t_binary_op_logic_or,
	t_binary_op_eq,
	t_binary_op_ne,
	t_binary_op_l,
	t_binary_op_g,
	t_binary_op_le,
	t_binary_op_ge,
	t_binary_op_eq3,
	t_binary_op_ne3,
	t_binary_op_assign
} type_binary_op;

typedef struct _is_binary_op
{
	type_binary_op type;

	union
	{
		struct
		{
			struct _is_expr* left;
			struct _is_expr* right;
		} operands;
		struct _is_assign_op* assign;
	} data;
} is_binary_op;

typedef struct _is_break
{
	struct _is_id* label;	/* nullable */
} is_break;

typedef struct _is_class_def
{
	struct _is_id* id;
	struct _is_class_stmt_list* body;
} is_class_def;

typedef enum
{
	t_class_stmt_privacy_public,
	t_class_stmt_privacy_private
} is_class_stmt_privacy;

typedef struct _is_class_stmt_scope
{
	bool b_final;
	bool b_static;
} is_class_stmt_scope;

typedef struct _is_class_stmt
{
	is_class_stmt_privacy* privacy; /* nullable */
	struct _is_class_stmt_scope* scope;	/* nullable */
	struct _is_member_stmt* stmt;
} is_class_stmt;

typedef struct _is_class_stmt_list
{
	struct _is_class_stmt* node;
	struct _is_class_stmt_list* next;
} is_class_stmt_list;

typedef enum {t_constant_bool, t_constant_long, t_constant_double, t_constant_char, t_constant_string} type_constant;
typedef struct _is_constant
{
	type_constant type;
	union
	{
		bool bool_val;
		long long long_val;
		long double double_val;
		char char_val;
		char* string_val;
	} value;
} is_constant;

typedef struct _is_continue
{
	struct _is_id* label;	/* nullable */
} is_continue;

typedef struct _is_dims
{
	struct _is_dims_sized_list* sized;
	is_dims_empty_list empty; /* NOT nullable, 0 if not existant, 1+ otherwise */
} is_dims;

typedef struct _is_dims_sized_list
{
	is_dims_sized* node;
	struct _is_dims_sized_list* next;
} is_dims_sized_list;

typedef struct _is_do_while
{
	struct _is_stmt* body;
	struct _is_expr* cond;
} is_do_while;

typedef enum
{
	t_expr_var,
	t_expr_new_op,
	t_expr_constant,
	t_expr_func_call,
	t_expr_operation
} type_expr;

typedef struct _is_expr
{
	type_expr type;
	union
	{
		struct _is_var* var;
		struct _is_new_op* new_op;
		struct _is_constant* constant;
		struct _is_func_call* func_call;
		struct _is_expr_op* operation;
	} data;
} is_expr;

typedef struct _is_expr_list
{
	struct _is_expr* node;
	struct _is_expr_list* next;
} is_expr_list;

typedef enum
{
	t_expr_op_unary,
	t_expr_op_binary,
	t_expr_op_ternary
} type_expr_op;

typedef struct _is_expr_op
{
	type_expr_op type;
	union
	{
		struct _is_unary_op* unary;
		struct _is_binary_op* binary;
		struct _is_ternary_op* ternary;
	} data;
} is_expr_op;

typedef struct _is_for
{
	struct _is_for_init* init; 	/* nullable */
	is_for_cond* cond; 		/* nullable */
	is_for_inc* inc; 	/* nullable */
	struct _is_stmt* body;
} is_for;

typedef enum
{
	t_for_expr_incr,
	t_for_expr_assign,
	t_for_expr_func_call
} type_for_expr;

typedef struct _is_for_expr
{
	type_for_expr type;
	union
	{
		struct _is_incr_op* incr;
		struct _is_assign_op* assign;
		struct _is_func_call* func_call;
	} data;
} is_for_expr;

typedef struct _is_for_expr_list
{
	struct _is_for_expr* node;
	struct _is_for_expr_list* next;
} is_for_expr_list;

typedef enum
{
	t_for_init_var_defs,
	t_for_init_for_expr_list
} type_for_init;

typedef struct _is_for_init
{
	type_for_init type;
	union
	{
		struct _is_var_defs* var_defs;
		struct _is_for_expr_list* expr_list;
	} data;
} is_for_init;

typedef enum
{
	t_func_call_id,
	t_func_call_sysout
} type_func_call;

typedef struct _is_func_call
{
	type_func_call type;
	struct _is_id* id; /* nullable (if sysout) */
	is_func_call_arg_list* args; /* nullable (no args provided) */
} is_func_call;

typedef struct _is_func_def
{
	struct _is_type_decl* type;
	struct _is_id* id;
	is_func_def_args* args;
	struct _is_stmt_list* body;
} is_func_def;

typedef struct _is_func_def_arg
{
	struct _is_type_decl* type;
	struct _is_id* id;
} is_func_def_arg;

typedef struct _is_func_def_arg_list
{
	struct _is_func_def_arg* node;
	struct _is_func_def_arg_list* next;
} is_func_def_arg_list;

typedef struct _is_id
{
	char* name;
} is_id;

typedef struct _is_if
{
	struct _is_expr* cond;
	struct _is_stmt* then_body;
	struct _is_stmt* else_body; /* nullable */
} is_if;

typedef enum
{
	t_incr_op_inc,
	t_incr_op_dec
} type_incr_op;

typedef struct _is_incr_op
{
	type_incr_op type;
	bool pre;
	struct _is_var* var;
} is_incr_op;

typedef enum
{
	t_loop_stmt_for,
	t_loop_stmt_while,
	t_loop_stmt_do_while
} type_loop_stmt;

typedef struct _is_loop_stmt
{
	/* TODO: is_id* label; */
	type_loop_stmt type;

	union
	{
		struct _is_for* for_stmt;
		struct _is_while* while_stmt;
		struct _is_do_while* do_while;
	} data;
} is_loop_stmt;

typedef enum
{
	t_member_stmt_var,
	t_member_stmt_func
} type_member_stmt;

typedef struct _is_member_stmt
{
	type_member_stmt type;
	union
	{
		is_var_stmt* var;
		struct _is_func_def* func;
	} data;
} is_member_stmt;

typedef struct _is_new_op
{
	struct _is_type_object *type_object;
	struct _is_dims *dims;
} is_new_op;

typedef struct _is_return
{
	is_expr *value; /* nullable */
} is_return;

typedef enum
{
	t_stmt_empty,
	t_stmt_var_stmt,
	t_stmt_assign,
	t_stmt_incr,
	t_stmt_if,
	t_stmt_loop,
	t_stmt_func_call,
	t_stmt_switch,
	t_stmt_break,
	t_stmt_continue,
	t_stmt_return
} type_stmt;

typedef struct _is_stmt
{
	type_stmt type;
	union
	{
		is_var_stmt *var;
		struct _is_assign_op *assign;
		struct _is_incr_op *incr;
		struct _is_if *if_stmt;
		struct _is_loop_stmt *loop;
		struct _is_func_call *func_call;
		struct _is_switch *switch_stmt;
		struct _is_break *break_stmt;
		struct _is_continue *continue_stmt;
		struct _is_return *return_stmt;
	} data;
} is_stmt;

/* was missing */
typedef struct _is_stmt_list
{
	struct _is_stmt* node;
	struct _is_stmt_list* next;
} is_stmt_list;

typedef struct _is_switch
{
	struct _is_expr *expr;
	struct _is_switch_stmt_list *list; /* nullable */
} is_switch;

typedef enum
{
	t_switch_stmt_default,
	t_switch_stmt_case
} type_switch_stmt;

typedef struct _is_switch_stmt
{
	type_switch_stmt type;
	union
	{
		struct _is_stmt_list *default_stmt_list;
		struct
		{
			struct _is_stmt_list *list;
			struct _is_constant *constant;
		} case_stmt;
	} data;
} is_switch_stmt;

typedef struct _is_switch_stmt_list
{
	struct _is_switch_stmt *node;
	struct _is_switch_stmt_list *next; /* nullable */
} is_switch_stmt_list;

typedef struct _is_ternary_op
{
	struct _is_expr* if_expr;
	struct _is_expr* then_expr;
	struct _is_expr* else_expr;
} is_ternary_op;

typedef enum
{
	t_type_decl_type_object,
	t_type_decl_array_decl
} type_type_decl;

typedef struct _is_type_decl
{
	type_type_decl type;
	union
	{
		struct _is_type_object* type_object;
		struct _is_array_decl* array;
	} data;
} is_type_decl;

typedef enum
{
	t_type_native_bool,
	t_type_native_byte,
	t_type_native_char,
	t_type_native_double,
	t_type_native_float,
	t_type_native_int,
	t_type_native_long,
	t_type_native_short,
	t_type_native_void
} is_type_native;

typedef struct _is_type_object
{
	is_type_native type;
} is_type_object;

typedef enum
{
	t_unary_op_operation,
	t_unary_op_incr_op
} type_unary_op;

typedef enum
{
	t_unary_op_operator_plus,
	t_unary_op_operator_minus,
	t_unary_op_operator_not,
	t_unary_op_operator_bin_not
} type_unary_op_operator;

/* FIXME: refactor disto para como esta agora; ou é uma incr op, ou é uma operaçao, que recebe o operador OK? */
typedef struct _is_unary_op
{
	type_unary_op type;
	union
	{
		struct
		{
			type_unary_op_operator op;
			is_expr *expr;
		} operation;
		is_incr_op *incr;
	} data;
} is_unary_op;

typedef enum
{
	t_var_id,
	t_var_new_op,
	t_var_array,
	t_var_func_call
} type_var;

typedef struct _is_var
{
	type_var type;
	union
	{
		struct _is_id* id;
		struct _is_new_op* new_op;
		struct
		{
			struct _is_var* var;
			is_dims_sized* dims;
		} array;
		struct
		{
			struct _is_func_call* call;
			is_dims_sized* dims;
		} func_call;
	} data;
} is_var;

typedef struct _is_var_def
{
	struct _is_id* id;
	struct _is_var_initializer* var_init; /* nullable */
	is_dims_empty_list dims;
} is_var_def;

typedef struct _is_var_def_list
{
	struct _is_var_def *node;
	struct _is_var_def_list* next; /* nullable */
} is_var_def_list;

typedef struct _is_var_defs
{
	struct _is_type_decl* type;
	struct _is_var_def_list* list;
} is_var_defs;

typedef enum {t_var_initializer_val_arr, t_var_initializer_expr} type_var_initializer;
typedef struct _is_var_initializer
{
	type_var_initializer type;

	union
	{
		struct _is_var_initializer_list* array; /* nullable */
		struct _is_expr* expr;
	} data;
} is_var_initializer;

typedef struct _is_var_initializer_list
{
	struct _is_var_initializer *node;
	struct _is_var_initializer_list *next; /* nullable */
} is_var_initializer_list;

typedef struct _is_while
{
	struct _is_expr* cond;
	struct _is_stmt* body;
} is_while;

#endif
