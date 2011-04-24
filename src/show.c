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
	switch (node->type)
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
			printf("%s", node->value.string_val);
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
	printf(" ");
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
	printf(" ");
	show_expr(node->expr);
}

void show_binary_op(is_binary_op* node)
{
	if (node->type == t_binary_op_assign)
	{
		show_assign_op(node->data.assign);
		return;
	}

	printf("(");
	show_expr(node->data.operands.left);
	printf(" ");
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

	printf(" ");
	show_expr(node->data.operands.right);
	printf(")");
}

void show_break(is_break* node)
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
 
void show_continue(is_continue* node)
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
	if (node)
	{
		show_dims_sized_list(node->sized);
		show_dims_empty_list(node->empty);
	}
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
	if (node)
	{
		show_dims_sized(node->node);
		show_dims_sized_list(node->next);
	}
}

void show_do_while(is_do_while* node, int tablevel)
{
	printf("do\n");
	show_stmt(node->body, tablevel+1);
	tab(tablevel);
	printf("while(");
	show_expr(node->cond);
	printf(");");
}
 
void show_expr(is_expr* node)
{
	printf("(");
	switch(node->type)
	{
		case t_expr_var:
			show_var(node->data.var);
			break;

		case t_expr_new_op:
			show_new_op(node->data.new_op);
			break;

		case t_expr_type_cast:
			printf("(");
			show_type_decl(node->data.type_cast.type);
			printf(")");
			show_expr(node->data.type_cast.expr);
			break;

		case t_expr_constant:
			show_constant(node->data.constant);
			break;

		case t_expr_func_call:
			show_func_call(node->data.func_call);
			break;

		case t_expr_operation:
			show_expr_op(node->data.operation);
			break;
	}
	printf(")");
}

void show_expr_list(is_expr_list* node)
{
	if (node)
	{
		show_expr(node->node);
		if (node->next)
		{
			printf(", ");
			show_expr_list(node->next);
		}
	}
}

void show_expr_op(is_expr_op* node)
{
	switch(node->type)
	{
		case t_expr_op_unary:
			show_unary_op(node->data.unary);
			break;

		case t_expr_op_binary:
			show_binary_op(node->data.binary);
			break;

		case t_expr_op_ternary:
			show_ternary_op(node->data.ternary);
			break;
	}
}

void show_for(is_for* node, int tablevel)
{
	printf("for (");
	show_for_init(node->init);
	printf("; ");
	show_for_cond(node->cond);
	printf("; ");
	show_for_inc(node->inc);
	printf(")\n");
	
	show_stmt(node->body, tablevel+1);
}

void show_for_cond(is_for_cond* node)
{
	if (node)
		show_expr(node);
}

void show_for_expr(is_for_expr* node)
{
	switch (node->type)
	{
		case t_for_expr_incr:
			show_incr_op(node->data.incr);
			break;

		case t_for_expr_assign:
			show_assign_op(node->data.assign);
			break;

		case t_for_expr_func_call:
			show_func_call(node->data.func_call);
			break;
	}
}
 
void show_for_expr_list(is_for_expr_list* node)
{
	if (node)
	{
		show_for_expr(node->node);
		if (node->next)
		{
			printf(", ");
			show_for_expr_list(node->next);
		}
	}
}

void show_for_inc(is_for_inc* node)
{
	if (node)
		show_for_expr_list(node);
}

void show_for_init(is_for_init* node)
{
	if (node)
	{
		switch (node->type)
		{
			case t_for_init_var_defs:
				show_var_defs(node->data.var_defs);
				break;

			case t_for_init_for_expr_list:
				show_for_expr_list(node->data.expr_list);
				break;
		}
	}
}

void show_func_call(is_func_call* node)
{
	switch (node->type)
	{
		case t_func_call_id:
			show_id(node->id);
			break;

		case t_func_call_sysout:
			printf("System.out.println");
			break;
	}

	show_func_call_arg_list(node->args);
}

void show_func_call_arg_list(is_func_call_arg_list* node)
{
	printf("(");
	show_expr_list(node);
	printf(")");
}

void show_func_def(is_func_def* node, int tablevel)
{
	show_type_decl(node->type);
	printf(" ");
	
	show_id(node->id);
	show_func_def_args(node->args);
	printf("\n");

	tab(tablevel);
	printf("{\n");
	show_stmt_list(node->body, tablevel+1);
	tab(tablevel);
	printf("}\n");
}

void show_func_def_arg(is_func_def_arg* node)
{
	show_type_decl(node->type);
	printf(" ");
	show_id(node->id);
}

void show_func_def_arg_list(is_func_def_arg_list* node)
{
	if (node)
	{
		show_func_def_arg(node->node);
		if (node->next)
		{
			printf(", ");
			show_func_def_arg_list(node->next);
		}
	}
}

void show_func_def_args(is_func_def_args* node)
{
	printf("(");
	show_func_def_arg_list(node);
	printf(")");
}

void show_if(is_if* node, int tablevel)
{
	printf("if (");
	show_expr(node->cond);
	printf(")\n");
	show_stmt(node->then_body, tablevel+1);

	if (node->else_body)
	{
		tab(tablevel);
		printf("else\n");
		show_stmt(node->else_body, tablevel+1);
	}
}

void show_incr_op(is_incr_op* node)
{
	if (node->pre)
		show_var(node->var);
	
	switch (node->type)
	{
		case t_incr_op_inc:
			printf("++");
			break;

		case t_incr_op_dec:
			printf("--");
			break;
	}

	if (!node->pre)
		show_var(node->var);
}

void show_loop_stmt(is_loop_stmt* node, int tablevel)
{
	switch (node->type)
	{	
		case t_loop_stmt_for:
			show_for(node->data.for_stmt, tablevel);
			break;

		case t_loop_stmt_while:
			show_while(node->data.while_stmt, tablevel);
			break;

		case t_loop_stmt_do_while:
			show_do_while(node->data.do_while_stmt, tablevel);
			break;
	} 
}
 
void show_member_stmt(is_member_stmt* node, int tablevel)
{
	if (!node)
	{
		printf(";\n");
		return;
	}

	switch (node->type)
	{
		case t_member_stmt_var:
			show_var_stmt(node->data.var);
			break;

		case t_member_stmt_func_def:
			show_func_def(node->data.func_def, tablevel);
			break;
	}
}

void show_new_op(is_new_op* node)
{
	printf("new ");
	show_type_object(node->type_object);
	show_dims(node->dims);}

void show_return(is_return* node)
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
	if (!node)
	{
		tab(tablevel);
	
		printf(";\n");
		return;
	}

	if (node->type != t_stmt_stmt_list)
		tab(1);

	tab(tablevel-1);
	switch (node->type)
	{
		case t_stmt_stmt_list:
			printf("{\n");
	
			show_stmt_list(node->data.list, tablevel);		

			tab(tablevel-1);
			printf("}\n");
			break;

		case t_stmt_var_stmt:
			show_var_stmt(node->data.var); /* prints its own ';' to be according to yacc */
			break;

		case t_stmt_assign:
			show_assign_op(node->data.assign);
			printf(";\n");
			break;

		case t_stmt_incr:
			show_incr_op(node->data.incr);
			printf(";\n");
			break;

		case t_stmt_if:
			show_if(node->data.if_stmt, tablevel);
			printf("\n");			/* empty line after if/else */
			break;

		case t_stmt_loop:
			show_loop_stmt(node->data.loop, tablevel);
			printf("\n"); 			/* empty line after loops */
			break;

		case t_stmt_func_call:
			show_func_call(node->data.func_call);
			printf(";\n");
			break;

		case t_stmt_switch:
			show_switch(node->data.switch_stmt, tablevel);
			printf("\n");			/* empty line after switch */
			break;

		case t_stmt_break:
			show_break(node->data.break_stmt);
			printf(";\n");
			break;

		case t_stmt_continue:
			show_continue(node->data.continue_stmt);
			printf(";\n");
			break;

		case t_stmt_return:
			show_return(node->data.return_stmt);
			printf(";\n");
			break;	
	}
}

void show_stmt_list(is_stmt_list* node, int tablevel)
{
	if (node)
	{
		show_stmt(node->node, tablevel);
		show_stmt_list(node->next, tablevel);
	}
}
 
void show_switch(is_switch* node, int tablevel)
{
	printf("switch(");
	show_expr(node->expr);
	printf(")\n");

	tab(tablevel);
	printf("{\n");

	show_switch_stmt_list(node->list, tablevel+1);

	tab(tablevel);
	printf("}\n");
}

void show_switch_stmt(is_switch_stmt* node, int tablevel)
{
	tab(tablevel);

	switch (node->type)
	{
		case t_switch_stmt_default:
			printf("default:\n");
			break;

		case t_switch_stmt_case:
			printf("case ");
			show_constant(node->constant);
			printf(":\n");
	}

	show_stmt_list(node->list, tablevel+1);
}

void show_switch_stmt_list(is_switch_stmt_list* node, int tablevel)
{
	if (node)
	{
		show_switch_stmt(node->node, tablevel);
		if (node->next)
		{
			printf("\n");
			show_switch_stmt_list(node->next, tablevel);
		}
	}
}

void show_ternary_op(is_ternary_op* node)
{
	printf("(");
	show_expr(node->if_expr);
	printf(" ? ");
	show_expr(node->then_expr);
	printf(" : ");
	show_expr(node->else_expr);
	printf(")");
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
			printf("short");
			break;

		case t_type_native_string:
			printf("String");
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

void show_unary_op(is_unary_op* node)
{
	switch (node->type)
	{
		case t_unary_op_incr_op:
			show_incr_op(node->data.incr);
			break;

		case t_unary_op_operation:
			switch (node->data.operation.op)
			{
				case t_unary_op_operator_plus:
					printf("+");
					break;

				case t_unary_op_operator_minus:
					printf("-");
					break;

				case t_unary_op_operator_not:
					printf("!");
					break;

				case t_unary_op_operator_bin_not:
					printf("~");
					break;
			}
			show_expr(node->data.operation.expr);
			break;
	}

}

void show_var(is_var* node)
{
	switch (node->type)
	{
		case t_var_id:
			show_id(node->data.id);
			break;

		case t_var_new_op:
			show_new_op(node->data.new_op);
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

void show_var_def(is_var_def* node)
{
	show_var_def_left(node->left);

	if (node->var_init)
	{
		printf(" = ");
		show_var_initializer(node->var_init);
	}
}

void show_var_def_list(is_var_def_list* node)
{
	if (node)
	{
		show_var_def(node->node);
		if (node->next)
		{
			printf(", ");
			show_var_def_list(node->next);
		}
	}
}

void show_var_def_left(is_var_def_left* node)
{
	show_id(node->id);

	switch (node->type)
	{
		case t_var_def_left_empty:
			show_dims_empty_list(node->data.empty);
			break;

		case t_var_def_left_dims:
			show_dims(node->data.dims);
			break;
	}
}

void show_var_defs(is_var_defs* node)
{
	show_type_decl(node->type);
	printf(" ");
	show_var_def_list(node->list);
}

void show_var_initializer(is_var_initializer* node)
{
	switch (node->type)
	{
		case t_var_initializer_val_arr:
			printf("{");
			show_var_initializer_list(node->data.array);
			printf("}");
			break;

		case t_var_initializer_expr:
			show_expr(node->data.expr);
			break;
	}
}

void show_var_initializer_list(is_var_initializer_list* node)
{
	if (node)
	{
		show_var_initializer(node->node);
		if (node->next)
		{
			printf(", ");
			show_var_initializer_list(node->next);
		}
	}
}

void show_var_stmt(is_var_stmt* node)
{
	show_var_defs(node);
	printf(";\n");
}

void show_while(is_while* node, int tablevel)
{
	printf("while(");
	show_expr(node->cond);
	printf(")\n");
	show_stmt(node->body, tablevel+1);
}
