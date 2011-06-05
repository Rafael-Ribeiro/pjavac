#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TRANSLATE_C

#include "inc/structures.h"
#include "inc/translate.h"
#include "inc/symtab.h"
#include "inc/insert.h"
#include "inc/free.h"
#include "inc/types.h"

#define OUT(...) fprintf(fout,__VA_ARGS__)

/* LEX */

void translate_id(is_id *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_constant(is_constant *node)
{
	node->temp = temp_counter++;

	switch (node->type)
	{
		case t_constant_bool:
			OUT("\tbool _temp_%d = %s;\n", node->temp, node->value.bool_val ? "true": "false");
		break;

		case t_constant_int:
			OUT("\tint _temp_%d = %d;\n", node->temp, node->value.int_val);
		break;

		case t_constant_long:
			OUT("\tlong long _temp_%d = %lld;\n", node->temp, node->value.long_val);
		break;

		case t_constant_double:
			OUT("\tlong double _temp_%d = %Lf;\n", node->temp, node->value.double_val);
		break;

		case t_constant_float:
			OUT("\tfloat _temp_%d = %ff;\n", node->temp, node->value.float_val);
		break;

		case t_constant_char:
			OUT("\tchar _temp_%d = %s;\n", node->temp, node->value.string_val);
		break;

		case t_constant_string:	
			OUT("\tchar* _temp_%d = strdup(%s);\n",
				node->temp,
				node->value.string_val
			);
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
void translate_application(is_application *node)
{
	temp_counter = 0;

	translate_header();
	
	translate_class_def(node);
	
	translate_footer();
}

void translate_array_decl(is_array_decl *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_assign_op(is_assign_op *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_binary_op(is_binary_op *node)
{
	is_type_decl* string;
	bool isStringLeft, isStringRight;
	char *operator, *type, *typeLeft, *typeRight;
	int tempLeft, tempRight;
	int tempLabel;

	switch (node->type)
	{
		case t_binary_op_assign:
			translate_assign_op(node->data.assign);
			node->temp = node->data.assign->temp;
		break;

		default:
			translate_expr(node->data.operands.left);
			translate_expr(node->data.operands.right);
	
			string = insert_type_decl_object(insert_type_object(t_type_native_string));
			type = string_type_decl(node->s_type);
	
			if (node->type == t_binary_op_add)
			{
				isStringLeft = type_type_equal(string, node->data.operands.left->s_type);
				isStringRight = type_type_equal(string, node->data.operands.right->s_type);

				if (isStringLeft || isStringRight)
				{
					if (!isStringLeft)
					{
						tempLeft = temp_counter++;
						tempLabel = ++label_counter;
						typeLeft = string_type_decl(node->data.operands.left->s_type);

						OUT("\t/* conversion from %s to string */\n", typeLeft);
						OUT("\t_fp->retaddr = %d;\n", tempLabel);
						OUT("\t_fp->args[0] = (%s*)malloc(sizeof(%s));\n", typeLeft, typeLeft);
						OUT("\t*_fp->args[0] = *_temp_%d;\n", node->data.operands.left->temp);
						OUT("\tgoto %s_to_string;\n", typeLeft);
						OUT("\n");
						OUT("label_%d:\n", tempLabel);
						OUT("\tchar* _temp_%d = (char*)fp->retval;\n", tempLeft);
						OUT("\n");

						free(typeLeft);
					} else
						tempLeft = node->data.operands.left->temp;
	
					if (!isStringRight)
					{
						tempRight = temp_counter++;
						tempLabel = ++label_counter;
						typeRight = string_type_decl(node->data.operands.right->s_type);

						OUT("\t/* conversion from %s to string */\n", typeRight);
						OUT("\t_fp->retaddr = %d;\n", tempLabel);
						OUT("\t_fp->args[0] = (%s*)malloc(sizeof(%s));\n", typeRight, typeRight);
						OUT("\t*_fp->args[0] = *_temp_%d;\n", node->data.operands.right->temp);
						OUT("\tgoto %s_to_string;\n", typeRight);
						OUT("\n");
						OUT("label_%d:\n", tempLabel);
						OUT("\tchar* _temp_%d = (char*)fp->retval;\n", tempRight);
						OUT("\n");

						free(typeRight);
					} else
						tempRight = node->data.operands.right->temp;

					node->temp = temp_counter++;
					tempLabel = ++label_counter;

					OUT("\t/* string + string */\n");
					OUT("\t_fp->retaddr = %d;\n", tempLabel);
					OUT("\t_fp->args[0] = (char**)malloc(sizeof(char*));\n");
					OUT("\t_fp->args[1] = (char**)malloc(sizeof(char*));\n");
					OUT("\t*_fp->args[0] = *_temp_%d;\n", node->data.operands.left->temp);
					OUT("\t*_fp->args[1] = *_temp_%d;\n", node->data.operands.right->temp);
					OUT("\tgoto string_concat;\n");
					OUT("\n");
					OUT("label_%d:\n", tempLabel);
					OUT("\t_temp_%d = (char*)fp->retval;\n", node->temp);
					OUT("\n");
				} else
				{
					node->temp = temp_counter++;

					OUT("\t%s _temp_%d = _temp_%d + _temp_%d;\n",
						type,
						node->temp,
						node->data.operands.left->temp,
						node->data.operands.right->temp
					);
				}
			} else if (node->type != t_binary_op_eq3 && node->type != t_binary_op_ne3)
			{
				node->temp = temp_counter++;

				operator = string_binary_operator(node->type);
				OUT("\t%s _temp_%d = _temp_%d %s _temp_%d;\n",
					type,
					node->temp,
					node->data.operands.left->temp,
					operator,
					node->data.operands.right->temp
				);

				free(operator);
			} else
				OUT("FIXME === or !== %d\n", __LINE__);

			free(type);
		break;
	}

	
	free_type_decl(string);
}

void translate_break(is_break *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_class_def(is_class_def *node)
{
	translate_class_stmt_list(node->body);
}

void translate_class_stmt(is_class_stmt *node)
{
	translate_member_stmt(node->stmt);
}
 
void translate_class_stmt_list(is_class_stmt_list *node)
{
	if (node)
	{
		translate_class_stmt(node->node);
		translate_class_stmt_list(node->next);
	}
}
 
void translate_class_stmt_scope(is_class_stmt_scope *node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_continue(is_continue *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_dims(is_dims *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_dims_sized(is_dims_sized *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_dims_sized_list(is_dims_sized_list *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_do_while(is_do_while *node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_expr(is_expr *node)
{
	char *type;

	switch (node->type)
	{
		case t_expr_var:
			translate_var(node->data.var);
			
			type = string_type_decl(node->s_type);

			node->temp = temp_counter++;
			OUT("\t%s _temp_%d = *_temp_%d;\n\n",
				type,
				node->temp,
				node->data.var->temp
			);

			free(type);
		break;
	
		case t_expr_new_op:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_type_cast:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_expr_constant:
			translate_constant(node->data.constant);
			node->temp = node->data.constant->temp;
		break;

		case t_expr_func_call:
			translate_func_call(node->data.func_call);
			node->temp = node->data.func_call->temp;
		break;

		case t_expr_operation:
			translate_expr_op(node->data.operation);
			node->temp = node->data.operation->temp;
		break;
	}
}

void translate_expr_list(is_expr_list *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_expr_op(is_expr_op *node)
{
	switch (node->type)
	{
		case t_expr_op_unary:
			translate_unary_op(node->data.unary);
			node->temp = node->data.unary->temp;
		break;

		case t_expr_op_binary:
			translate_binary_op(node->data.binary);
			node->temp = node->data.binary->temp;
		break;

		case t_expr_op_ternary:
			translate_ternary_op(node->data.ternary);
			node->temp = node->data.ternary->temp;
		break;
	}
}

void translate_footer()
{
	OUT("\t/* entry point */\n");
	OUT("\tgoto label_0;\n");
	OUT("\n");
	
	translate_redirector();

	OUT("\n");
	OUT("label_end:\n");
	OUT("\treturn 0;\n");
	OUT("}\n");
}

void translate_for(is_for *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_for_cond(is_for_cond *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_for_expr(is_for_expr *node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_for_expr_list(is_for_expr_list *node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_for_inc(is_for_inc *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_for_init(is_for_init *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_func_call(is_func_call *node)
{
	char *type, *type_arg;
	is_func_call_arg_list* arg;
	int label, i, temp;
	is_type_decl* type_void;

	type_void = new_type_decl_void(0);

	label = ++label_counter;

	for (arg = node->args; arg != NULL; arg = arg->next)
	{
		translate_expr(arg->node);
		OUT("\n");
	}

	OUT("\t/* function call: %s */\n", node->id->name);
	OUT("\t_fp->retaddr = %d;\n", label);

	if (!type_type_equal(type_void, node->symbol->data.func_data.type))
	{
		type = string_type_decl(node->symbol->data.func_data.type);
		OUT("\t_fp->retval = malloc(sizeof(%s));\n", type);
		OUT("\n");
	}

	for (i = 0, arg = node->args; arg != NULL; i++, arg = arg->next)
	{
		type_arg = string_type_decl(node->symbol->data.func_data.args[i]->type);

		OUT("\t/* argument %d */\n", i);
		OUT("\t_fp->args[%d] = (%s*)malloc(sizeof(%s));\n", i, type_arg, type_arg);
		OUT("\t*(%s*)_fp->args[%d] = (%s)_temp_%d;\n", type_arg, i, type_arg, arg->node->temp);
		OUT("\n");

		free(type_arg);
	}

	OUT("\tgoto label_%d;\n", node->symbol->data.func_data.label);
	OUT("\n");
	OUT("label_%d:\n", label);

	/* FIXME: what about frees of frees? */
	for (i = 0; i < node->symbol->data.func_data.nArgs; i++)
		OUT("\tfree(_fp->args[%d]);\n", i);
	
	if (!type_type_equal(type_void, node->symbol->data.func_data.type))
	{
		temp = temp_counter++;
		OUT("\t%s* _temp_%d = (%s*)malloc(sizeof(%s));\n", type, temp, type, type);
		OUT("\t*_temp_%d = *(%s*)_fp->retval;\n", temp, type);
		OUT("\t_free(_fp->retval);\n");

		node->temp = temp;
		free(type);
	}	
}

void translate_func_def(is_func_def *node)
{
	int i, temp;
	char *arg_type, *func_type;
	is_type_decl *void_type;

	func_type = string_type_decl(node->scope->symbol->data.func_data.type);


	OUT("\tgoto label_%d_postend;\n", node->scope->symbol->data.func_data.label);
	OUT("\n");
	OUT("label_%d:\n\t; /* %s */\n", node->scope->symbol->data.func_data.label, node->id->name);

	/* alloc new frame */
	OUT("\t_temp_frame = (FRAME*)malloc(sizeof(FRAME));\n");
	OUT("\t_temp_frame->parent = _fp;\n");
	OUT("\n");

	/* copy args to locals */
	if (strcmp(node->id->name, "main") == 0)
	{
		if (node->scope->symbol->data.func_data.nArgs == 1)
		{
			temp = temp_counter++;

			OUT("\t/* start of args setup */\n");
			OUT("\t_temp_frame->locals[0] = (char**)malloc(_argc * sizeof(char*));\n");
			OUT("\tint _temp_%d = _argc;\n", temp);
			OUT("\n");
			OUT("label_main_args:\n");
			OUT("\tif (!_temp_%d)\n", temp);
			OUT("\t\tgoto label_main_args_end;\n");
			OUT("\t((char**)_temp_frame->locals[0])[_temp_%d-1] = strdup(_argv[_temp_%d-1]);\n", temp, temp);
			OUT("\t_temp_%d--;\n", temp);
			OUT("\tgoto label_main_args;\n");
			OUT("\n");
			OUT("label_main_args_end:\n");
			OUT("\t; /* end of args setup */\n");
			OUT("\n");
		}
	} else
	{
		for (i = 0; i < node->scope->symbol->data.func_data.nArgs; i++)
		{
			arg_type = string_type_decl(node->scope->symbol->data.func_data.args[i]->type);
			OUT("\t_temp_frame->locals[%d] = (%s*)malloc(sizeof(%s));\n", i, arg_type, arg_type);
			OUT("\t*(%s*)(_temp_frame->locals[%d]) = *(%s*)(_fp->args[%d]);\n", arg_type, i, arg_type, i);
			OUT("\n");
			free(arg_type);
		}
	}

	OUT("\t_fp = _temp_frame;\n");
	
	void_type = new_type_decl_void(0);
	if (!type_type_equal(node->scope->symbol->data.func_data.type, void_type))
		OUT("\t_temp_ret = malloc(sizeof(%s));\n", func_type);

	OUT("\n");
	OUT("\t/* %s body */\n",  node->id->name);
	
	translate_stmt_list(node->body);

	/* FIXME: free locals */
	
	OUT("\n");
	OUT("label_%d_end:\n\t/* end of %s */\n", node->scope->symbol->data.func_data.label, node->id->name);

	if (!type_type_equal(node->scope->symbol->data.func_data.type, void_type))
	{
		if (strcmp(node->id->name, "main") != 0)
			OUT("\t*(%s*)_fp->parent->retval = *(%s*)_temp_ret;\n", func_type, func_type);

		OUT("\tfree(_temp_ret);\n");
	}

	OUT("\t_temp_frame = _fp->parent;\n");
	OUT("\tfree(_fp);\n");
	OUT("\t_fp = _temp_frame;\n");
	OUT("\n");

	OUT("\tgoto redirector;\n");
	OUT("\n");
	OUT("label_%d_postend:\n", node->scope->symbol->data.func_data.label);
	OUT("\t; /* post end of %s */\n\n", node->id->name);	

	free_type_decl(void_type);
	free(func_type);
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
	OUT("int main(int _argc, char **_argv)\n");	/* TODO: main arguments */
	OUT("{\n");
	OUT("\tvoid* _temp_ret;\n");
	OUT("\tvoid* _globals[MAX_GLOBALS];\n");
	OUT("\tFRAME *_fp = NULL, *_temp_frame;\n");
	OUT("\n");
	
	OUT("\tgoto post_builtins;\n");
	OUT("\t#include \"runtime/builtins.h\"\n");
	OUT("\n");
	OUT("post_builtins: ;\n");
}

void translate_if(is_if *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_incr_op(is_incr_op *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_loop_stmt(is_loop_stmt *node)
{
	OUT("FIXME %d\n", __LINE__);
}
 
void translate_member_stmt(is_member_stmt *node)
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

void translate_new_op(is_new_op *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_redirector()
{
	int i;

	OUT("redirector:\n");

	OUT("\tif (_fp == NULL)\n");
	OUT("\t\tgoto label_end;\n");

	for (i = 0; i <= label_counter; i++)
	{
		OUT("\tif (_fp->retaddr == %d)\n", i);
		OUT("\t\tgoto label_%d;\n", i);
	}
}

void translate_return(is_return *node)
{
	char * type;
	
	if (node->value)
	{
		translate_expr(node->value);

		type = string_type_decl(node->symbol->data.func_data.type);
		OUT("\t*(%s)_temp_ret = *(%s)_temp_%d;\n", type, type, node->value->temp);
		free(type);
	}

	OUT("\tgoto label_%d_end;\n", node->symbol->data.func_data.label);
	OUT("\n");
}

void translate_stmt(is_stmt *node)
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

void translate_stmt_list(is_stmt_list *node)
{
	if (node)
	{
		translate_stmt(node->node);
		translate_stmt_list(node->next);
	}
}
 
void translate_switch(is_switch *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_switch_stmt(is_switch_stmt *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_switch_stmt_list(is_switch_stmt_list *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_ternary_op(is_ternary_op *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_type_decl(is_type_decl *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_type_object(is_type_object *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_unary_op(is_unary_op *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_var(is_var *node)
{
	char *type;
	
	node->temp = temp_counter++;
	type = string_type_decl(node->s_type);

	OUT("\t%s* _temp_%d;\n", type, node->temp);
			
	switch (node->type)
	{
		case t_var_id:
			if (node->symbol->data.var_data.global)
				OUT("\t_temp_%d = (%s*)_globals[%d];\n",
					node->temp,
					type,
					node->symbol->data.var_data.framepos
				);
			else
				OUT("\t_temp_%d = (%s*)_fp->locals[%d];\n", 
					node->temp,
					type,
					node->symbol->data.var_data.framepos
				);
		break;

		case t_var_new_op:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_var_array:
			OUT("FIXME %d\n", __LINE__);
		break;

		case t_var_func_call:
			OUT("FIXME %d\n", __LINE__);
		break;
	}

	free(type);
}

void translate_var_def(is_var_def *node)
{
	char *typeA;
	SYMBOL* symbol;

	symbol = node->left->symbol;

	if (node->var_init)
		translate_var_initializer(node->var_init);

	typeA = string_type_decl(symbol->data.var_data.type);

	if (symbol->data.var_data.global)
	{
		OUT("\t_globals[%d] = (%s*)malloc(sizeof(%s));\n",
			symbol->data.var_data.framepos,
			typeA,
			typeA
		);

		if (node->var_init)
		{
			OUT("\t*((%s*)_globals[%d]) = _temp_%d;\n",
				typeA,
				symbol->data.var_data.framepos,
				node->var_init->temp
			);
		}
	} else
	{
		OUT("\t_fp->locals[%d] = (%s*)malloc(sizeof(%s));\n",
			symbol->data.var_data.framepos,
			typeA,
			typeA
		);

		if (node->var_init)
		{
			OUT("\t*((%s*)_fp->locals[%d]) = _temp_%d;\n",
				typeA,
				symbol->data.var_data.framepos,
				node->var_init->temp
			);
		}
	}
	OUT("\n");
	free(typeA);
}

void translate_var_def_list(is_var_def_list *node)
{
	if (node)
	{
		translate_var_def(node->node);
		translate_var_def_list(node->next);
	}	
}

void translate_var_def_left(is_var_def_left *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_var_defs(is_var_defs *node)
{
	translate_var_def_list(node->list);
}

void translate_var_stmt(is_var_stmt *node)
{
	translate_var_defs(node);
}

void translate_var_initializer(is_var_initializer *node)
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

void translate_var_initializer_list(is_var_initializer_list *node)
{
	OUT("FIXME %d\n", __LINE__);
}

void translate_while(is_while *node)
{
	OUT("FIXME %d\n", __LINE__);
}
