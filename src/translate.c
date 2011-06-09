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
	/* NOTHING TO DO HERE! */
	OUT("ERROR %d", __LINE__);
}

void translate_constant(is_constant *node)
{
	node->temp = temp_counter++;

	switch (node->type)
	{
		case t_constant_bool:
			OUT("\t*(bool*)& _registers[%d] = %s;\n", node->temp, node->value.bool_val ? "true": "false");
		break;

		case t_constant_int:
			OUT("\t*(int*)& _registers[%d] = %d;\n", node->temp, node->value.int_val);
		break;

		case t_constant_long:
			OUT("\t*(long long*)& _registers[%d] = %lld;\n", node->temp, node->value.long_val);
		break;

		case t_constant_double:
			OUT("\t*(long double*)& _registers[%d] = %Lf;\n", node->temp, node->value.double_val);
		break;

		case t_constant_float:
			OUT("\t*(float*)& _registers[%d] = %ff;\n", node->temp, node->value.float_val);
		break;

		case t_constant_char:
			OUT("\t*(char*)& _registers[%d] = %s;\n", node->temp, node->value.string_val);
		break;

		case t_constant_string:
			OUT("\t*(char**)& _registers[%d]  = strdup(%s);\n",
				node->temp,
				node->value.string_val
			);
		break;
	}
}


/* YACC */
void translate_dims_empty_list(is_dims_empty_list* val)
{
	/* NOTHING TO DO HERE! */
	OUT("ERROR %d", __LINE__);
}

/* enums */
void translate_class_stmt_privacy(is_class_stmt_privacy val)
{
	/* NOTHING TO DO HERE! */
	OUT("ERROR %d", __LINE__);
}

void translate_type_native(is_type_native val)
{
	/* NOTHING TO DO HERE! */
	OUT("ERROR %d", __LINE__);
}


/* nodes */
void translate_application(is_application *node)
{
	temp_counter = 0;

	OUT("/*\n");
	OUT(" * This program was compiled from PJava using\n");
	OUT(" * https://www.assembla.com/code/2010_dei_comp/");
	OUT("\n */\n\n");

	translate_header();
	
	translate_class_def(node);
	
	translate_footer();
}

void translate_array_decl(is_array_decl *node)
{
	/* NOTHING TO DO HERE! */
	OUT("ERROR %d", __LINE__);
}

void translate_assign_op(is_assign_op *node)
{
	char *operator, *typeExpr;
	int label, labelConvert, tempConvert;
	is_type_decl *type_string;

	type_string = new_type_decl_string(0);

	translate_expr(node->expr);

	translate_var(node->var);

	if (node->type == t_assign_op_add_eq && type_type_equal(type_string, node->var->s_type))
	{
		label = ++label_counter;

		if (!type_type_equal(type_string, node->expr->s_type))
		{
			tempConvert = temp_counter++;
			labelConvert = ++label_counter;
			typeExpr = string_type_decl(node->expr->s_type);

			OUT("\t/* conversion from %s to string */\n", typeExpr);
			OUT("\t_fp->retaddr = %d;\n", labelConvert);
			OUT("\t_fp->args[0] = _register[%d];\n", node->expr->temp);
			OUT("\tgoto %s_to_string;\n", typeExpr);
			OUT("\n");
			OUT("label_%d:\n", labelConvert);
			OUT("\t_registers[%d] = _fp->retval;\n", tempConvert);
			OUT("\n");

			free(typeExpr);
		} else
			tempConvert = node->expr->temp;

		var_type = string_type_decl(node->var->s_type);

		OUT("\t/* string += string */\n");
		OUT("\t_fp->retaddr = %d;\n", label);
		OUT("\t_fp->args[0] = *(char**)& _registers[%d]; /* var */\n", var_type, node->var->temp);
		OUT("\t_fp->args[1] = _registers[%d]; /* expr */\n", tempConvert);
		OUT("\tgoto string_concat;\n");
		OUT("\n");
		OUT("label_%d:\n", label);
		OUT("\t; /* temp_%d gets the concatenated string */\n", node->var->temp);
		OUT("\t*(char**)& _registers[%d] = (char*)_fp->retval;\n", node->var->temp);
		OUT("\n");

		/* FIXME: fp->locals */
		free(var_type);
	} else
	{
		operator = string_assign_operator(node->type);
		OUT("\t**(%s**)& _registers[%d] = %s *(%s*)& _registers[%d];\n",
			var_type, node->var->temp, operator, var_type, node->expr->temp);
		free(operator);
	}

	free_type_decl(type_string);
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
						OUT("\t_fp->args[0] = &_temp_%d;\n", node->data.operands.left->temp);
						OUT("\tgoto %s_to_string;\n", typeLeft);
						OUT("\n");
						OUT("label_%d:\n", tempLabel);
						OUT("\t; /* temp_%d gets the string */\n", tempLeft);
						OUT("\tchar* _temp_%d = (char*)_fp->retval;\n", tempLeft);
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
						OUT("\t_fp->args[0] = &_temp_%d;\n", node->data.operands.right->temp);
						OUT("\tgoto %s_to_string;\n", typeRight);
						OUT("\n");
						OUT("label_%d: ;\n", tempLabel);
						OUT("\t; /* temp_%d gets the string */\n", tempRight);
						OUT("\tchar* _temp_%d = (char*)_fp->retval;\n", tempRight);
						OUT("\n");

						free(typeRight);
					} else
						tempRight = node->data.operands.right->temp;

					node->temp = temp_counter++;
					tempLabel = ++label_counter;

					OUT("\t/* string + string */\n");
					OUT("\t_fp->retaddr = %d;\n", tempLabel);
					OUT("\t_fp->args[0] = &_temp_%d;\n", tempLeft);
					OUT("\t_fp->args[1] = &_temp_%d;\n", tempRight);
					OUT("\tgoto string_concat;\n");
					OUT("\n");
					OUT("label_%d:\n", tempLabel);
					OUT("\t; /* temp_%d gets the concatenated string */\n", node->temp);
					OUT("\tchar* _temp_%d = (char*)_fp->retval;\n", node->temp);
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

			free_type_decl(string);
			free(type);
		break;
	}

}

void translate_break(is_break *node)
{
	OUT("\t/* breaking loop */");
	OUT("\tgoto label_%d_end;\n", node->scope->symbol->data.loop_data.label);
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
	OUT("\t/* continuing loop */");
	OUT("\tgoto label_%d_continue;\n", node->scope->symbol->data.loop_data.label);
}

void translate_dims(is_dims *node)
{
	translate_dims_sized_list(node->sized);
	translate_dims_empty_list(node->empty);
}

void translate_dims_sized(is_dims_sized *node)
{
	translate_expr(node);
	OUT("\n");
}

void translate_dims_sized_list(is_dims_sized_list *node)
{
	if (node)
	{
		translate_dims_sized(node->node);
		translate_dims_sized_list(node->next);
	}
}

void translate_do_while(is_do_while *node)
{
	OUT("label_%d:\n",node->scope->symbol->data.loop_data.label);
	OUT("label_%d_continue:\n",node->scope->symbol->data.loop_data.label);
	OUT("\t; /* do_while loop */\n");

	OUT("\t/* do_while body */\n");
	translate_stmt(node->body);
	OUT("\n");

	OUT("\t/* do_while condition */\n");
	translate_expr(node->cond);
	OUT("\n");

	OUT("\tif (_temp_%d)\n",node->cond->temp);
	OUT("\t\tgoto label_%d;\n",node->scope->symbol->data.loop_data.label);

	OUT("\t/* end of do_while */\n");
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
			translate_new_op(node->data.new_op);
			node->temp = node->data.new_op->temp;
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
	if (!node)
		return;

	translate_expr(node->node);
	OUT("\n");

	translate_expr_list(node->next);
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
	OUT("\t/* for loop */\n");
	if (node->init)
	{
		OUT("\t/* for loop initialization */\n");
		translate_for_init(node->init);
	}

	OUT("label_%d:\n", node->scope->symbol->data.loop_data.label);
	OUT("\t; /* for loop (condition, body, inc) */\n");
	if (node->cond)
	{
		OUT("\t/* for loop condition */\n");
		translate_for_cond(node->cond);

		OUT("\tif (!_temp_%d)\n", node->cond->temp);
		OUT("\t\tgoto label_%d_end;\n", node->scope->symbol->data.loop_data.label);
	}

	OUT("\n");
	if (node->body)
	{
		OUT("\t/* for loop body */\n");
		translate_stmt(node->body);
	}

	OUT("label_%d_continue:\n", node->scope->symbol->data.loop_data.label);
	OUT("\t; /* for continue label */");

	if (node->inc)
		translate_for_inc(node->inc);

	OUT("\tgoto label_%d;\n", node->scope->symbol->data.loop_data.label);

	OUT("label_%d_end:\n", node->scope->symbol->data.loop_data.label);
	OUT("\t; /* for loop end */\n\n");
}

void translate_for_cond(is_for_cond *node)
{
	/* is_for_cond is typedef'd from is_expr */
	translate_expr(node);
}

void translate_for_expr(is_for_expr *node)
{
	switch (node->type)
	{
		case t_for_expr_incr:
			translate_incr_op(node->data.incr);
		break;

		case t_for_expr_assign:
			translate_assign_op(node->data.assign);
		break;

		case t_for_expr_func_call:
			translate_func_call(node->data.func_call);
		break;
	}
}
 
void translate_for_expr_list(is_for_expr_list *node)
{
	if (!node)
		return;

	translate_for_expr(node->node);
	OUT("\n");

	translate_for_expr_list(node->next);
}
 
void translate_for_inc(is_for_inc *node)
{
	/* is_for_inc is typedef'd from is_for_expr_list */
	translate_for_expr_list(node);
}

void translate_for_init(is_for_init *node)
{
	switch (node->type)
	{
		case t_for_init_var_defs:
			translate_var_defs(node->data.var_defs);
		break;

		case t_for_init_for_expr_list:
			translate_for_expr_list(node->data.expr_list);
		break;
	}
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
		type = string_type_decl(node->symbol->data.func_data.type);

	for (i = 0, arg = node->args; arg != NULL; i++, arg = arg->next)
	{
		type_arg = string_type_decl(node->symbol->data.func_data.args[i]->type);
		OUT("\t_fp->args[%d] = &_temp_%d;\n", i, arg->node->temp);
		free(type_arg);
	}

	OUT("\tgoto label_%d;\n", node->symbol->data.func_data.label);
	OUT("\n");
	OUT("label_%d:\n", label);
	OUT("\t; /* end of func call*/\n");

	if (!type_type_equal(type_void, node->symbol->data.func_data.type))
	{
		temp = temp_counter++;
		OUT("\t%s _temp_%d = *(%s*)_fp->retval;\n", type, temp, type);

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

	OUT("\n");
	OUT("\t/* %s body */\n",  node->id->name);
	
	translate_stmt_list(node->body);

	/* FIXME: free locals */
	
	OUT("\n");
	OUT("label_%d_end:\n\t/* end of %s */\n", node->scope->symbol->data.func_data.label, node->id->name);

	if (!type_type_equal(node->scope->symbol->data.func_data.type, void_type) &&
		strcmp(node->id->name, "main") != 0)
		OUT("\t_fp->parent->retval = _temp_ret;\n");

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
	OUT("\tvoid *_temp_ret;\n");
	OUT("\tvoid *_globals[MAX_GLOBALS];\n");
	OUT("\tvoid *_registers[MAX_REGISTERS];\n");
	OUT("\tFRAME *_fp = NULL, *_temp_frame;\n");
	OUT("\n");
	
	OUT("\tgoto post_builtins;\n");
	OUT("\t#include \"runtime/builtins.h\"\n");
	OUT("\n");
	OUT("post_builtins: ;\n");
}

void translate_if(is_if *node)
{
	OUT("\t/* begin of if */\n");

	translate_expr(node->cond);
	int label;

	label = ++label_counter;
	OUT("\tif (!_temp_%d)\n", node->cond->temp);

	if (node->else_body)
		OUT("\t\tgoto label_%d_if_else;\n", label);
	else
		OUT("\t\tgoto label_%d;\n", label);

	OUT("\t/* then */\n");
	translate_stmt(node->then_body);

	if (node->else_body)
	{
		OUT("\tgoto label_%d;\n", label);
		OUT("\n");
		OUT("label_%d_if_else:\n", label);
		OUT("\t; /* else */\n");
		translate_stmt(node->else_body);
	}

	OUT("label_%d:\n", label);
	OUT("\t; /* end of if */\n");
	OUT("\n");
}

void translate_incr_op(is_incr_op *node)
{
	char *type, *operator;

	type = string_type_decl(node->s_type);
	operator = string_incr_operator(node->type);

	translate_var(node->var);

	if (node->used)
	{
		node->temp = temp_counter++;
		if (node->pre)
			OUT("\t%s _temp_%d = %s(*(%s*)_temp_%d);\n", type, node->temp, operator, type, node->var->temp);
		else
			OUT("\t%s _temp_%d = (*(%s*)_temp_%d)%s;\n", type, node->temp, type, node->var->temp, operator);
	} else
	{
		node->temp = -1;
		if (node->pre)
			OUT("\t%s(*(%s*)_temp_%d);\n", operator, type, node->var->temp);
		else
			OUT("\t(*(%s*)_temp_%d)%s;\n", type, node->var->temp, operator);
	}

	free(operator);
	free(type);
}

void translate_loop_stmt(is_loop_stmt *node)
{
	switch (node->type)
	{
		case t_loop_stmt_for:
			translate_for(node->data.for_stmt);
		break;

		case t_loop_stmt_while:
			translate_while(node->data.while_stmt);
		break;

		case t_loop_stmt_do_while:
			translate_do_while(node->data.do_while_stmt);
		break;
	}
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

void translate_new_op_recursive(is_new_op *node, int temp, is_dims_sized_list* dim)
{
	int dimsize, totalsize;
	char* type;

	if (dim == NULL)
		dimsize = 0;
	else
		dimsize = dim->length;

	totalsize = dimsize + node->dims->empty->size;

	type = string_type_native_array(node->type_object->type, totalsize-1);

	OUT("\t%s* _temp_%d_%d = (%s*)malloc(sizeof(%s) * _temp_%d);\n",
		type, temp, dimsize, type, type, dim->node->temp);

	if (dim->next != NULL)
	{
		OUT("\n");
		OUT("\t /* new op: subdimension */\n");
		OUT("\tint _temp_%d_%d_i = 0;\n", temp, dimsize);
		
		OUT("label_%d_%d_new:\n", temp, dimsize);
		OUT("\t; /* new op at subdimension %d*/\n", dimsize);

		translate_new_op_recursive(node, temp, dim->next);

		OUT("\n");
		OUT("\t_temp_%d_%d[_temp_%d_%d_i] = _temp_%d_%d;\n", temp, dimsize, temp, dimsize, temp, dimsize-1);
		OUT("\t_temp_%d_%d_i++;\n", temp, dimsize);
		OUT("\n");
		OUT("\tif (_temp_%d_%d_i != _temp_%d)\n", temp, dimsize, dim->node->temp);
		OUT("\t\t goto label_%d_%d_new;\n", temp, dimsize);
		OUT("\t/* new op: end of subdimension*/\n");
	}

	free(type);
}

void translate_new_op(is_new_op *node)
{
	char *type;
	
	translate_dims(node->dims);

	OUT("\t /* begin of new op */\n");

	node->temp = temp_counter++;
	translate_new_op_recursive(node, node->temp, node->dims->sized);
	
	type = string_type_native_array(node->type_object->type, node->dims->length);

	OUT("\n");
	OUT("\t%s _temp_%d = _temp_%d_%d;\n", type, node->temp, node->temp, node->dims->sized->length);
	OUT("\t /* end of new op */\n\n");

	free(type);
}

void translate_redirector()
{
	int i;

	OUT("redirector:\n");

	OUT("\tif (*(int*)& _fp == NULL)\n");
	OUT("\t\tgoto label_end;\n");

	for (i = 0; i <= label_counter; i++)
	{
		OUT("\tif (*(int*)& _fp->retaddr == %d)\n", i);
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
		OUT("\t_temp_ret = _registers[%d];\n", node->value->temp);
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
	int label;

	label = ++label_counter;
	node->temp = temp_counter++;

	OUT("\t/* ternary op */\n");
	OUT("\n");

	translate_expr(node->if_expr);

	OUT("\n");
	OUT("\tif (! *(bool*)& _registers[%d])\n", node->if_expr->temp);
	OUT("\t\tgoto label_%d_else;\n", label);
	OUT("\n");
	OUT("\t/* ternary op then */\n");

	translate_expr(node->then_expr);

	OUT("\n");
	OUT("\t_registers[%d] = _registers[%d];\n", node->temp, node->then_expr->temp);

	OUT("\n");
	OUT("\tgoto label_%d;\n", label);
	OUT("label_%d_else:\n", label);
	OUT("\t; /* ternary op else*/");
	
	translate_expr(node->else_expr);

	OUT("\n");
	OUT("\t_registers[%d] = _registers[%d];\n", node->temp, node->else_expr->temp);

	OUT("\n");
	OUT("label_%d:\n", label);
	OUT("\t; /* ternary op end */\n");
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
	switch (node->type)
	{
		case t_unary_op_operation:
			translate_expr(node->data.operation.expr);

			node->temp = temp_counter++;
			OUT("\t_registers[%d] = %c_registers[%d];\n",
				node->temp,
				string_unary_operator(node->data.operation.op),
				node->data.operation.expr->temp
			);

		break;

		case t_unary_op_incr_op:
			translate_incr_op(node->data.incr);
			node->temp = node->data.incr->temp;
		break;	
	}
}

void translate_var(is_var *node)
{
	char *type;

	node->temp = temp_counter++;

	switch (node->type)
	{
		case t_var_id:
			if (node->symbol->data.var_data.global)
				OUT("\t_registers[%d] = _globals[%d];\n",
					node->temp,
					node->symbol->data.var_data.framepos
				);
			else
				OUT("\t_registers[%d] = _fp->locals[%d];\n", 
					node->temp,
					node->symbol->data.var_data.framepos
				);
		break;

		case t_var_new_op:
			translate_new_op(node->data.new_op);
			OUT("\t_registers[%d] = _registers[%d];\n", node->temp, node->data.new_op->temp);
		break;

		case t_var_array:
			translate_var(node->data.array.var);
			translate_dims_sized(node->data.array.dims);
			OUT("\t_registers[%d] = &(( **(%s*)& _registers[%d])[*(int*)& _registers[%d]]);\n",
				node->temp,
				type = string_type_decl(node->data.array.var->s_type),
				node->data.array.var->temp,
				node->data.array.dims->temp
			);
			OUT("\n");

			free(type);
		break;

		case t_var_func_call:
			OUT("FIXME %d\n", __LINE__);
		break;
	}
}

void translate_var_def(is_var_def *node)
{
	SYMBOL* symbol;

	symbol = node->left->symbol;

	if (node->var_init)
		translate_var_initializer(node->var_init);

	if (symbol->data.var_data.global)
	{
		if (node->var_init)
		{
			OUT("\t_globals[%d] = _registers[%d];\n",
				symbol->data.var_data.framepos,
				node->var_init->temp
			);
		}
	} else
	{
		if (node->var_init)
		{
			OUT("\t_fp->locals[%d] = _registers[%d];\n",
				symbol->data.var_data.framepos,
				node->var_init->temp
			);
		}
	}
	OUT("\n");
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
	OUT("label_%d:\n",node->scope->symbol->data.loop_data.label);
	OUT("label_%d_continue:\n",node->scope->symbol->data.loop_data.label);
	OUT("\t; /* while loop */\n");

	OUT("\t/* while condition */\n");
	translate_expr(node->cond);
	OUT("\n");
	
	OUT("\tif (! *(bool*)& _registers[%d])\n",node->cond->temp);
	OUT("\t\tgoto label_%d_end;\n",node->scope->symbol->data.loop_data.label);

	OUT("\t/* while body */\n");
	translate_stmt(node->body);
	OUT("\n");

	OUT("\tgoto label_%d;\n",node->scope->symbol->data.loop_data.label);

	OUT("label_%d_end:\n",node->scope->symbol->data.loop_data.label);
	OUT("\t; /* end of while */\n");
}
