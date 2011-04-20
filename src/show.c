#include <stdio.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/show.h"

void tab(int tablevel)
{
	int i;
	for (i = 0; i < tablevel; i++)
		printf("\t");
}

/* LEX */
void show_id(is_id* node)
{
	printf("%s", node->name);
}

void show_constant(is_constant* node)
{
	switch(node->type)
	{
		case t_constant_bool:
			if (node->value.bool_val)
				printf("true");
			else
				printf("false");
			break;

		case t_constant_long:
			printf("%lld", node->value.long_val);
			break;

		case t_constant_double:
			printf("%.3Lf", node->value.double_val);
			break;

		case t_constant_char:
			printf("'%c'", node->value.char_val);
			break;

		case t_constant_string:
			printf("%s", node->value.string_val);
			break;
	}
}

/* YACC */
void show_application(is_application* node, int tablevel)
{
	show_class_def(node, 0);
}

void show_array_decl(is_array_decl* node)
{
	show_type_object(node->type);
	show_dims_empty_list(node->dims);
}

void show_assign_op(is_assign_op* node)
{
	show_var(node->var);
	
	switch (node->type)
	{
		case t_assign_op_eq:
			printf("=");
			break;

		case t_assign_op_shift_r_eq:
			printf(">>=");
			break;

		case t_assign_op_shift_l_eq:
			printf("<<=");
			break;

		case t_assign_op_add_eq:
			printf("+=");
			break;

		case t_assign_op_sub_eq:
			printf("-=");
			break;

		case t_assign_op_mul_eq:
			printf("*=");
			break;

		case t_assign_op_div_eq:
			printf("/=");
			break;

		case t_assign_op_mod_eq:
			printf("%%=");
			break;

		case t_assign_op_and_eq:
			printf("&=");
			break;

		case t_assign_op_xor_eq:
			printf("^=");
			break;

		case t_assign_op_or_eq:
			printf("|=");
			break;
	}

	show_expr(node->expr);
}

void show_binary_op_operation(is_binary_op* node, int tablevel)
{
	if (node->type == t_binary_op_assign)
	{
		show_assign_op(node->data.assign);
		return;
	}

	printf("(");
	show_expr(node->data.operands.left);
	switch (node->type)
	{
		case t_binary_op_add:
			printf("+");
			break;

		case t_binary_op_sub:
			printf("-");
			break;

		case t_binary_op_mul:
			printf("*");
			break;

		case t_binary_op_div:
			printf("/");
			break;

		case t_binary_op_mod:
			printf("%%");
			break;

		case t_binary_op_and:
			printf("&");
			break;

		case t_binary_op_or:
			printf("|");
			break;

		case t_binary_op_xor:
			printf("^");
			break;

		case t_binary_op_shift_r:
			printf(">>");
			break;

		case t_binary_op_shift_l:
			printf("<<");
			break;

		case t_binary_op_logic_and:
			printf("&&");
			break;

		case t_binary_op_logic_or:
			printf("||");
			break;

		case t_binary_op_eq:
			printf("==");
			break;

		case t_binary_op_ne:
			printf("!=");
			break;

		case t_binary_op_l:
			printf("<");
			break;

		case t_binary_op_g:
			printf(">");
			break;

		case t_binary_op_le:
			printf("<=");
			break;

		case t_binary_op_ge:
			printf(">=");
			break;

		case t_binary_op_eq3:
			printf("===");
			break;

		case t_binary_op_ne3:
			printf("!==");
			break;

		default: /* never happens, remove warning because of assign */
			break;
	}

	show_expr(node->data.operands.right);
	printf(")");
}

void show_break(is_break* node, int tablevel)
{
	printf("break");

	if (node->label)
	{
		printf(" ");
		show_id(node->label);
	}
}
 
void show_class_def(is_class_def* node, int tablevel)
{
	tab(tablevel);
	printf("class ");
	show_id(node->id);
	printf("\n");

	tab(tablevel);
	printf("{\n");
	show_class_stmt_list(node->body, tablevel+1);

	tab(tablevel);
	printf("}\n");
}

void show_class_stmt(is_class_stmt* node, int tablevel)
{
	tab(tablevel);
	
	if (node->privacy)
	{
		show_class_stmt_privacy(*node->privacy);
		printf(" ");
	}

	if (node->scope)
	{
		show_class_stmt_scope(node->scope);
		printf(" ");
	}

	show_member_stmt(node->stmt, tablevel);
}

void show_class_stmt_list(is_class_stmt_list* node, int tablevel)
{
	if (node)
	{
		show_class_stmt(node->node, tablevel);
		show_class_stmt_list(node->next, tablevel);
	}
} 
 
void show_class_stmt_privacy(is_class_stmt_privacy val)
{
	switch(val)
	{
		case t_class_stmt_privacy_public:
			printf("public");
			break;

		case t_class_stmt_privacy_private:
			printf("private");
			break;
	}
}

void show_class_stmt_scope(is_class_stmt_scope* node)
{
	if (node->b_final)
		printf("final");
	
	if (node->b_static)
	{
		if (node->b_final);
			printf(" ");

		printf("static");
	}
}
 
void show_continue(is_continue* node, int tablevel)
{
	printf("continue");

	if (node->label)
	{
		printf(" ");
		show_id(node->label);
	}
}

void show_dims(is_dims* node)
{
	show_dims_sized_list(node->sized);
	show_dims_empty_list(node->empty);
}

void show_dims_empty_list(is_dims_empty_list list)
{
	int i;
	for (i = 0; i < list; i++)
		printf("[]");
}

void show_dims_sized(is_dims_sized* node)
{
	printf("[");
	show_expr(node);
	printf("]");
}

void show_dims_sized_list(is_dims_sized_list* node)
{
	while (node)
	{
		show_dims_sized(node->node);
		show_dims_sized_list(node->next);
	}
}

void show_do_while(is_do_while* node, int tablevel)
{
	printf("do\n");
	show_stmt(node->body, tablevel+1);
	printf(" while(");
	show_expr(node->cond);
	printf(");");
}
 
void show_expr(is_expr* node)
{
	switch(node->type)
	{
		case t_expr_var:
			show_var(node->data.var);
			break;

		case t_expr_new_op:
			show_new_op(node->data.new_op);
			break;

		case t_expr_constant:
			show_constant(node->data.constant);
			break;

		case t_expr_func_call:
			show_func_call(node->data.func);
			break;

		case t_expr_operation:
			show_expr_op(node->data.operation);
			break;
	}
}

void show_expr_list(is_expr_list* node, int tablevel)
{

}

void show_expr_op(is_expr_op* node)
{

}

void show_for(is_for* node, int tablevel)
{

}

void show_for_expr(is_for_expr* node, int tablevel)
{

}
 
void show_for_expr_list(is_for_expr_list* node, int tablevel)
{

}
 
void show_for_init(is_for_init* node, int tablevel)
{

}

void show_func_call(is_func_call* node)
{

}

void show_func_def(is_func_def* node, int tablevel)
{

}

void show_func_def_arg(is_func_def_arg* node, int tablevel)
{

}

void show_func_def_arg_list(is_func_def_arg_list* node, int tablevel)
{

}

void show_if(is_if* node, int tablevel)
{

}

void show_incr_op(is_incr_op* node, int tablevel)
{

}

void show_loop_stmt(is_loop_stmt* node, int tablevel)
{

}
 
void show_member_stmt(is_member_stmt* node, int tablevel)
{
	tab(tablevel);

	switch (node->type)
	{
		case t_member_stmt_var:
			show_var_stmt(node->data.var, tablevel);
			break;

		case t_member_stmt_func:
			show_func_def(node->data.func, tablevel);
			break;
	}
}

void show_new_op(is_new_op* node)
{

}

void show_return(is_return* node, int tablevel)
{
	printf("return");

	if (node->value)
	{
		printf(" ");
		show_expr(node->value);
	}
}

void show_stmt(is_stmt* node, int tablevel)
{

}

void show_stmt_list(is_stmt_list* node, int tablevel)
{

}
 
void show_switch(is_switch* node, int tablevel)
{

}

void show_switch_stmt(is_switch_stmt* node, int tablevel)
{

}

void show_switch_stmt_list(is_switch_stmt_list* node, int tablevel)
{

}

void show_ternary_op(is_ternary_op* node, int tablevel)
{

}

void show_type_decl(is_type_decl* node)
{
	switch (node->type)
	{
		case t_type_decl_type_object:
			show_type_object(node->data.type_object);
			break;

		case t_type_decl_array_decl:
			show_array_decl(node->data.array);
			break;
	}
}

void show_type_native(is_type_native val)
{
	switch (val)
	{
		case t_type_native_bool:
			printf("bool");
			break;

		case t_type_native_byte:
			printf("byte");
			break;

		case t_type_native_char:
			printf("char");
			break;

		case t_type_native_double:
			printf("double");
			break;

		case t_type_native_float:
			printf("float");
			break;

		case t_type_native_int:
			printf("int");
			break;

		case t_type_native_long:
			printf("long");
			break;

		case t_type_native_short:
			printf("shor");
			break;

		case t_type_native_void:
			printf("void");
			break;
	}
}

void show_type_object(is_type_object* node)
{
	show_type_native(node->type);
}

void show_unary_op(is_unary_op* node, int tablevel)
{

}

void show_var(is_var* node)
{
	switch (node->type)
	{
		case t_var_id:
			show_id(node->data.id);
			break;

		case t_var_new_op:
			printf("(");			
			show_new_op(node->data.new_op);
			printf(")");
			break;

		case t_var_array:
			show_var(node->data.array.var);
			show_dims_sized(node->data.array.dims);
			break;

		case t_var_func_call:
			show_func_call(node->data.func_call.call);
			show_dims_sized(node->data.func_call.dims);
			break;
	}
}

void show_var_def(is_var_def* node, int tablevel)
{

}

void show_var_def_list(is_var_def_list* node, int tablevel)
{
	
}

void show_var_defs(is_var_defs* node, int tablevel)
{
	show_type_decl(node->type);
	show_var_def_list(node->list, tablevel);
}

void show_var_initializer(is_var_initializer* node, int tablevel)
{

}

void show_var_initializer_list(is_var_initializer_list* node, int tablevel)
{

}

void show_var_stmt(is_var_stmt* node, int tablevel)
{
	show_var_defs(node, tablevel);
}

void show_while(is_while* node, int tablevel)
{

}

