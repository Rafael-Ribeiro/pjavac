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
struct _is_dims_empty_list;
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
struct _is_var_def_left;
struct _is_var_defs;
struct _is_var_initializer;
struct _is_var_initializer_list;
struct _is_var_stmt;
struct _is_while;

/***********************************************************************/
/* just because we can, this ones will be in the structures themselves */
typedef struct _is_expr is_dims_sized;
typedef struct _is_expr is_for_cond;
typedef struct _is_for_expr_list is_for_inc;
typedef struct _is_var_defs is_var_stmt;
typedef struct _is_class_def is_application;
typedef struct _is_expr_list is_func_call_arg_list;
typedef struct _is_func_def_arg_list is_func_def_args;

/***********************************************************************/

/* semantics */
struct _SCOPE;
struct _SYMBOL;

typedef struct _is_array_decl
{
	int line;

	struct _is_type_object* type;
	struct _is_dims_empty_list* dims;
} is_array_decl;

typedef enum
{
	t_assign_op_eq = 0,
	t_assign_op_shift_r_eq = 1,
	t_assign_op_shift_l_eq = 2,
	t_assign_op_add_eq = 3,
	t_assign_op_sub_eq = 4,
	t_assign_op_mul_eq = 5,
	t_assign_op_div_eq = 6,
	t_assign_op_mod_eq = 7,
	t_assign_op_and_eq = 8,
	t_assign_op_xor_eq = 9,
	t_assign_op_or_eq = 10
} type_assign_op;

typedef struct _is_assign_op
{
	int line;

	type_assign_op type;
	struct _is_var* var;
	struct _is_expr* expr;

	/* semantics */
	struct _is_type_decl* s_type;

	int temp;
} is_assign_op;

typedef enum
{
	t_binary_op_add = 11,
	t_binary_op_sub = 12,
	t_binary_op_mul = 13,
	t_binary_op_div = 14,
	t_binary_op_mod = 15,
	t_binary_op_and = 16,
	t_binary_op_or = 17,
	t_binary_op_xor = 18,
	t_binary_op_shift_r = 19,
	t_binary_op_shift_l = 20,
	t_binary_op_logic_and = 21,
	t_binary_op_logic_or = 22,
	t_binary_op_eq = 23,
	t_binary_op_ne = 24,
	t_binary_op_l = 25,
	t_binary_op_g = 26,
	t_binary_op_le = 27,
	t_binary_op_ge = 28,
	t_binary_op_eq3 = 29,
	t_binary_op_ne3 = 30,
	t_binary_op_assign
} type_binary_op;

typedef struct _is_binary_op
{
	int line;

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

	/* semantics */
	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
} is_binary_op;

typedef struct _is_break
{
	int line;

	struct _is_id* label;	/* nullable */
	struct _SCOPE* scope;
} is_break;

typedef struct _is_class_def
{
	int line;

	struct _is_id* id;
	struct _is_class_stmt_list* body;

	/* semantics */
	struct _SCOPE* scope;
} is_class_def;

typedef enum
{
	t_class_stmt_privacy_public,
	t_class_stmt_privacy_private
} is_class_stmt_privacy;

typedef struct _is_class_stmt_scope
{
	int line;

	bool b_final;
	bool b_static;
} is_class_stmt_scope;

typedef struct _is_class_stmt
{
	int line;

	is_class_stmt_privacy* privacy; /* nullable */
	struct _is_class_stmt_scope* scope;	/* nullable */
	struct _is_member_stmt* stmt;
} is_class_stmt;

typedef struct _is_class_stmt_list
{
	int line;

	struct _is_class_stmt* node;
	struct _is_class_stmt_list* next;
} is_class_stmt_list;

typedef enum
{
	t_constant_bool,
	t_constant_int,
	t_constant_long,
	t_constant_double,
	t_constant_float,
	t_constant_char,
	t_constant_string
} type_constant;

typedef struct _is_constant
{
	int line;

	type_constant type;
	union
	{
		bool bool_val;
		int int_val;
		long long long_val;
		long double double_val;
		float float_val;

		/* char char_val; it's not used since char is now a '<char>' string (including the inverted commas) */
		char* string_val;
	} value;

	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
} is_constant;

typedef struct _is_continue
{
	int line;

	struct _is_id* label;	/* nullable */
	struct _SCOPE* scope;
} is_continue;

typedef struct _is_dims
{
	int line;

	struct _is_dims_sized_list* sized;
	struct _is_dims_empty_list* empty; /* NOT nullable, 0 if not existant, 1+ otherwise */

	/* semantics */
	int length;
} is_dims;

typedef struct _is_dims_empty_list
{
	int line;

	int size;
} is_dims_empty_list;

typedef struct _is_dims_sized_list
{
	int line;

	/* semantics */
	int length;

	is_dims_sized* node;
	struct _is_dims_sized_list* next;

} is_dims_sized_list;

typedef struct _is_do_while
{
	int line;

	struct _is_expr* cond;
	struct _is_stmt* body;

	/* semantics */
	struct _SCOPE* scope;
	bool terminates;
} is_do_while;

typedef enum
{
	t_expr_var,
	t_expr_new_op,
	t_expr_type_cast,
	t_expr_constant,
	t_expr_func_call,
	t_expr_operation
} type_expr;

typedef struct _is_expr
{
	int line;

	type_expr type;
	union
	{
		struct _is_var* var;
		struct _is_new_op* new_op;
		struct
		{
			struct _is_expr* expr;
			struct _is_type_decl* type;
		} type_cast;		
		struct _is_constant* constant;
		struct _is_func_call* func_call;
		struct _is_expr_op* operation;
	} data;

	/* semantics */
	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
} is_expr;

typedef struct _is_expr_list
{
	int line;

	struct _is_expr* node;
	struct _is_expr_list* next;

	/* semantics */
	int length;
} is_expr_list;

typedef enum
{
	t_expr_op_unary,
	t_expr_op_binary,
	t_expr_op_ternary
} type_expr_op;

typedef struct _is_expr_op
{
	int line;

	type_expr_op type;
	union
	{
		struct _is_unary_op* unary;
		struct _is_binary_op* binary;
		struct _is_ternary_op* ternary;
	} data;

	/* semantics */
	struct _is_type_decl* s_type;
	
	/* code generation */
	int temp;
} is_expr_op;

typedef struct _is_for
{
	int line;

	struct _is_for_init* init; 	/* nullable */
	is_for_cond* cond; 		/* nullable */
	is_for_inc* inc; 	/* nullable */
	struct _is_stmt* body;

	/* semantics */
	struct _SCOPE* scope;
	bool terminates;
} is_for;

typedef enum
{
	t_for_expr_incr,
	t_for_expr_assign,
	t_for_expr_func_call
} type_for_expr;

typedef struct _is_for_expr
{
	int line;

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
	int line;

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
	int line;

	type_for_init type;
	union
	{
		struct _is_var_defs* var_defs;
		struct _is_for_expr_list* expr_list;
	} data;
} is_for_init;

typedef struct _is_func_call
{
	int line;

	struct _is_id* id; /* NOT nullable */
	is_func_call_arg_list* args; /* nullable (no args provided) */

	/* semantics */
	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
	struct _SYMBOL* symbol;
} is_func_call;

typedef struct _is_func_def
{
	int line;

	struct _is_type_decl* type;
	struct _is_id* id;
	is_func_def_args* args;
	struct _is_stmt_list* body;

	/* semantics */
	struct _SCOPE* scope;
} is_func_def;

typedef struct _is_func_def_arg
{
	int line;

	struct _is_type_decl* type;
	struct _is_id* id;
} is_func_def_arg;

typedef struct _is_func_def_arg_list
{
	int line;

	struct _is_func_def_arg* node;
	struct _is_func_def_arg_list* next;

	/* semantics */
	int length;
} is_func_def_arg_list;

typedef struct _is_id
{
	int line;

	char* name;
} is_id;

typedef struct _is_if
{
	int line;

	struct _is_expr* cond;
	struct _is_stmt* then_body;
	struct _is_stmt* else_body; /* nullable */

	/* semantics */
	bool terminates;
} is_if;

typedef enum
{
	t_incr_op_inc = 0,
	t_incr_op_dec = 1
} type_incr_op;

typedef struct _is_incr_op
{
	int line;

	type_incr_op type;
	bool pre;
	struct _is_var* var;

	/* semantics */
	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
	bool used;
} is_incr_op;

typedef enum
{
	t_loop_stmt_for,
	t_loop_stmt_while,
	t_loop_stmt_do_while
} type_loop_stmt;

typedef struct _is_loop_stmt
{
	int line;

	type_loop_stmt type;
	struct _is_id* loop_label; /* nullable */
	union
	{
		struct _is_for* for_stmt;
		struct _is_while* while_stmt;
		struct _is_do_while* do_while_stmt;
	} data;

	/* semantics */
	bool terminates;
} is_loop_stmt;

typedef enum
{
	t_member_stmt_var,
	t_member_stmt_func_def
} type_member_stmt;

typedef struct _is_member_stmt
{
	int line;

	type_member_stmt type;
	union
	{
		is_var_stmt* var;
		struct _is_func_def* func_def;
	} data;
} is_member_stmt;

typedef struct _is_new_op
{
	int line;

	struct _is_type_object *type_object;
	struct _is_dims *dims;

	/* semantics */
	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
} is_new_op;

typedef struct _is_return
{
	int line;

	is_expr *value; /* nullable */

	/* code generation */
	struct _SYMBOL* symbol;
} is_return;

typedef enum
{
	t_stmt_stmt_list,
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
	int line;

	type_stmt type;
	union
	{
		struct
		{
			struct _is_stmt_list * list;
			struct _SCOPE* scope;
		} stmt_list;
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

	/* semantics */
	bool terminates;
} is_stmt;

typedef struct _is_stmt_list
{
	int line;

	struct _is_stmt* node;
	struct _is_stmt_list* next;

	/* semantics */
	int length;
	bool terminated;
} is_stmt_list;

typedef struct _is_switch
{
	int line;

	struct _is_expr *expr;
	struct _is_switch_stmt_list *list; /* nullable */

	/* semantics */
	bool terminates;
} is_switch;

typedef enum
{
	t_switch_stmt_default,
	t_switch_stmt_case
} type_switch_stmt;

typedef struct _is_switch_stmt
{
	int line;

	type_switch_stmt type;
	struct _is_stmt_list *list;
	struct _is_constant *constant; /* nullable, if default */
} is_switch_stmt;

typedef struct _is_switch_stmt_list
{
	int line;

	struct _is_switch_stmt *node;
	struct _is_switch_stmt_list *next; /* nullable */
} is_switch_stmt_list;

typedef struct _is_ternary_op
{
	int line;

	struct _is_expr* if_expr;
	struct _is_expr* then_expr;
	struct _is_expr* else_expr;

	/*
	 * semantics
	 *
	 * the most abrangent type IF it exists, error otherwise (e.g.: String and int)
	 * (note that this only applies while there is a single class hierarchy)
	 */
	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
} is_ternary_op;

typedef enum
{
	t_type_decl_type_object,
	t_type_decl_array_decl
} type_type_decl;

typedef struct _is_type_decl
{
	int line;

	type_type_decl type;
	union
	{
		struct _is_type_object* type_object;
		struct _is_array_decl* array;
	} data;
} is_type_decl;

typedef enum
{
	t_type_native_bool = 0,
	t_type_native_byte = 1,
	t_type_native_char = 2,
	t_type_native_double = 3,
	t_type_native_float = 4,
	t_type_native_int = 5,
	t_type_native_long = 6,
	t_type_native_short = 7,
	t_type_native_string = 8,
	t_type_native_void = 9
} is_type_native;

typedef struct _is_type_object
{
	int line;

	is_type_native type;
} is_type_object;

typedef enum
{
	t_unary_op_operation,
	t_unary_op_incr_op

} type_unary_op;

typedef enum
{
	t_unary_op_operator_plus = 0,
	t_unary_op_operator_minus = 1,
	t_unary_op_operator_not = 2,
	t_unary_op_operator_bin_not = 3
} type_unary_op_operator;

typedef struct _is_unary_op
{
	int line;

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

	/* semantics */
	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
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
	int line;

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

	/* semantics */
	struct _is_type_decl* s_type;
	bool initialized;

	/* code generation */
	int temp; /* temp will store the address of the var in runtime */
	struct _SYMBOL* symbol;
} is_var;

typedef struct _is_var_def
{
	int line;

	struct _is_var_def_left* left;
	struct _is_var_initializer* var_init; /* nullable */
} is_var_def;

typedef struct _is_var_def_list
{
	int line;

	struct _is_var_def *node;
	struct _is_var_def_list* next; /* nullable */
} is_var_def_list;

typedef struct _is_var_def_left
{
	int line;

	struct _is_dims_empty_list* empty;		
	struct _is_id* id;

	/* semantics */
	struct _SYMBOL* symbol;
} is_var_def_left;

typedef struct _is_var_defs
{
	int line;

	struct _is_type_decl* type;
	struct _is_var_def_list* list;
} is_var_defs;

typedef enum {t_var_initializer_val_arr, t_var_initializer_expr} type_var_initializer;
typedef struct _is_var_initializer
{
	int line;

	type_var_initializer type;

	union
	{
		struct _is_var_initializer_list* array; /* nullable */
		struct _is_expr* expr;
	} data;

	struct _is_type_decl* s_type;

	/* code generation */
	int temp;
} is_var_initializer;

typedef struct _is_var_initializer_list
{
	int line;

	struct _is_var_initializer *node;
	struct _is_var_initializer_list *next; /* nullable */

	int temp;
} is_var_initializer_list;

typedef struct _is_while
{
	int line;

	struct _is_expr* cond;
	struct _is_stmt* body;

	/* semantics */
	struct _SCOPE* scope;
	bool terminates;
} is_while;

#endif
