#ifndef STRUCTURES_H
#define STRUCTURES_H

/* just because we can? */
typedef is_class_def is_application;

typedef struct
{
	is_type_object* ito;
	is_dims_empty_list* idel;
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
	is_id* label;	
} is_break;


/*****************************************************SEPARATOR*****************************************************/

typedef struct
{
	is_expr* iexpr;
	is_compound_stmt* ics;
} is_while;
#endif
