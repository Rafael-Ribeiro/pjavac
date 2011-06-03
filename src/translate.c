#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRANSLATE_C

#include "inc/structures.h"
#include "inc/translate.h"
#include "inc/symtab.h"
#include "inc/types.h"

#define OUT(...) fprintf(fout,__VA_ARGS__)

/* LEX */

void translate_id(is_id* node)
{

}

void translate_constant(is_constant* node)
{
	int temp;
	
	temp = temp_counter++;

	switch (node->type)
	{
		case t_constant_bool:
			OUT("\tbool _temp_%d = %s;\n", temp, node->value.bool_val ? "true": "false");
		break;

		case t_constant_int:
			OUT("\tint _temp_%d = %d;\n", temp, node->value.int_val);
		break;

		case t_constant_long:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_constant_double:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_constant_float:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_constant_char:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_constant_string:
			OUT("FIXME %d\n", __LINE__);
		break;
	}
}


/* YACC */
void translate_dims_empty_list(is_dims_empty_list* val)
{
	OUT("FIXME %d\n", __LINE__);
}


/* enums */
void translate_class_stmt_privacy(is_class_stmt_privacy val)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_type_native(is_type_native val)
{
	OUT("FIXME %d\n", __LINE__);
}


/* nodes */
void translate_application(is_application* node)
{
	temp_counter = 0;

	translate_header();
	
	translate_class_def(node);
	
	translate_footer();
}

void translate_array_decl(is_array_decl* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_assign_op(is_assign_op* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_binary_op(is_binary_op* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_break(is_break* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_class_def(is_class_def* node)
{
	translate_class_stmt_list(node->body);
}

void translate_class_stmt(is_class_stmt* node)
{
	translate_member_stmt(node->stmt);
}
 
void translate_class_stmt_list(is_class_stmt_list* node)
{
	if (node)
	{
		translate_class_stmt(node->node);
		translate_class_stmt_list(node->next);
	}
}
 
void translate_class_stmt_scope(is_class_stmt_scope* node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_continue(is_continue* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_dims(is_dims* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_dims_sized(is_dims_sized* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_dims_sized_list(is_dims_sized_list* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_do_while(is_do_while* node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_expr(is_expr* node)
{
	char *type;
	int temp;

	type = string_type_decl(node->s_type);

	switch (node->type)
	{
		case t_expr_var:
			OUT("FIXME %d\n", __LINE__);
		break;
	
		case t_expr_new_op:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_type_cast:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_constant:
			translate_constant(node->data.constant);
		break;

		case t_expr_func_call:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_operation:
			OUT("FIXME %d\n", __LINE__);
		break;
	}

	temp = temp_counter++;
	OUT("\t%s _temp_%d;\n", type,temp);

	switch (node->type)
	{
		case t_expr_var:
			OUT("FIXME %d\n", __LINE__);
		break;
	
		case t_expr_new_op:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_type_cast:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_constant:
			OUT("\t_temp_%d = (%s)_temp_%d\n", temp, type, node->data.constant->temp);
		break;

		case t_expr_func_call:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_operation:
			OUT("FIXME %d\n", __LINE__);
		break;
	}

	OUT("\n");
	free(type);
}

void translate_expr_list(is_expr_list* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_expr_op(is_expr_op* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_footer()
{
	OUT("\t_fp->retaddr = 1;\n");
	OUT("\tgoto label_0;\n");
	OUT("\n");
	
	label_counter++;
	translate_redirector();

	OUT("label_%d:\n", label_counter);
	OUT("\treturn 0;\n");
	OUT("}\n");
}

void translate_for(is_for* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_for_cond(is_for_cond* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_for_expr(is_for_expr* node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_for_expr_list(is_for_expr_list* node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_for_inc(is_for_inc* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_for_init(is_for_init* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_func_call(is_func_call* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_func_call_arg_list(is_func_call_arg_list* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_func_def(is_func_def* node)
{
	OUT("label_%d:\n", node->scope->symbol->data.func_data.label);

	/* TODO: copy args to locals? */

	translate_stmt_list(node->body);

	OUT("\tgoto redirector;\n");
	OUT("\n");	
}

void translate_func_def_arg(is_func_def_arg* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_func_def_arg_list(is_func_def_arg_list* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_func_def_args(is_func_def_args* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_header()
{
	OUT("#include <stdio.h>\n");
	OUT("#include <stdlib.h>\n");
	OUT("#include <stdbool.h>\n");
	OUT("#include <string.h>\n");
	OUT("#include <strings.h>\n");
	OUT("\n");
	OUT("#include \"runtime/frame.h\"\n");
	OUT("\n");
	OUT("int main()\n");	/* TODO: main arguments */
	OUT("{\n");
	OUT("\tint _ra;\n");
	OUT("\tFRAME _globals;\n");
	OUT("\tFRAME *_fp = NULL;\n");
	OUT("\n");

	/* TODO: create main's frame */
	OUT("\t\n");
}

void translate_if(is_if* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_incr_op(is_incr_op* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_loop_stmt(is_loop_stmt* node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_member_stmt(is_member_stmt* node)
{
	switch (node->type)
	{
		case t_member_stmt_var:
			translate_var_stmt(node->data.var);
			break;

		case t_member_stmt_func_def:
			translate_func_def(node->data.func_def);
			break;
	}
}

void translate_new_op(is_new_op* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_redirector()
{
	int i;

	OUT("redirector:\n");

	for (i = 0; i <= label_counter; i++)
	{
		OUT("\tif (_ra == %d)\n", i);
		OUT("\t\tgoto label_%d;\n", i);
	}
}

void translate_return(is_return* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_stmt(is_stmt* node)
{
	switch (node->type)
	{
		case t_stmt_stmt_list:
			translate_stmt_list(node->data.stmt_list.list);
		break;

		case t_stmt_var_stmt:
			translate_var_stmt(node->data.var);
		break;

		case t_stmt_assign:
			translate_assign_op(node->data.assign);
		break;

		case t_stmt_incr:
			translate_incr_op(node->data.incr);
		break;

		case t_stmt_if:
			translate_if(node->data.if_stmt);
		break;

		case t_stmt_loop:
			translate_loop_stmt(node->data.loop);
		break;

		case t_stmt_func_call:
			translate_func_call(node->data.func_call);
		break;

		case t_stmt_switch:
			translate_switch(node->data.switch_stmt);
		break;

		case t_stmt_break:
			translate_break(node->data.break_stmt);
		break;

		case t_stmt_continue:
			translate_continue(node->data.continue_stmt);
		break;

		case t_stmt_return:
			translate_return(node->data.return_stmt);
		break;
	}
}

void translate_stmt_list(is_stmt_list* node)
{
	if (node)
	{
		translate_stmt(node->node);
		translate_stmt_list(node->next);
	}
}
 
void translate_switch(is_switch* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_switch_stmt(is_switch_stmt* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_switch_stmt_list(is_switch_stmt_list* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_ternary_op(is_ternary_op* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_type_decl(is_type_decl* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_type_object(is_type_object* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_unary_op(is_unary_op* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_var(is_var* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_var_def(is_var_def* node)
{
	char *typeA;
	SYMBOL* symbol;

	symbol = node->left->symbol;

	if (node->var_init)
		translate_var_initializer(node->var_init);

	typeA = string_type_decl(symbol->data.var_data.type);
	OUT("\t_fp->locals[%d] = (%s*)malloc(sizeof(%s))\n",
		symbol->data.var_data.framepos,
		typeA,
		typeA
	);

	if (node->var_init)
	{
		OUT("\t*((%s*)_fp->locals[%d] = _temp_%d\n",
			typeA,
			symbol->data.var_data.framepos,
			node->var_init->temp
		);
	}

	free(typeA);
}

void translate_var_def_list(is_var_def_list* node)
{
	if (node)
	{
		translate_var_def(node->node);
		translate_var_def_list(node->next);
	}	
}

void translate_var_def_left(is_var_def_left* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_var_defs(is_var_defs* node)
{
	/* TODO: this probably doesnt need to do anything now that each var "knows" it's type */

	translate_var_def_list(node->list);
}

void translate_var_stmt(is_var_stmt* node)
{
	translate_var_defs(node);
}

void translate_var_initializer(is_var_initializer* node)
{
	switch (node->type)
	{
		case t_var_initializer_val_arr:
			OUT("FIXME %d\n", __LINE__); 
		break;

		case t_var_initializer_expr:
			translate_expr(node->data.expr);
			node->temp = node->data.expr->temp;
		break;
	}
}

void translate_var_initializer_list(is_var_initializer_list* node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_while(is_while* node)
{
	OUT("FIXME %d\n", __LINE__);
}
