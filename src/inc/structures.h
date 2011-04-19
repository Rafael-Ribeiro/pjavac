#ifndef STRUCTURES_H
#define STRUCTURES_H

/* just because we can? */
typedef is_class_def is_application;

typedef struct
{
	is_type_object* ito;
	is_dims_empty_list* idel;
} is_array_decl;

typedef enum {t_eq, t_shift_r, t_shift_l, t_add, t_sub, t_mul, t_div, t_mod, t_and, t_xor, t_or} type_assign_op;
typedef struct
{
	type_assign_op type;
	is_var* var;
	is_expr* expr;
} is_assign_op;


#endif
