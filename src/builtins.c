#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/symtab.h"
#include "inc/insert.h"
#include "inc/builtins.h"

void insert_builtins()
{
	SYMBOL *symbol;

	is_type_decl* type_void = new_type_decl_void(0);
	is_type_decl* type_string = insert_type_decl_object(insert_type_object(t_type_native_string));
	is_id* var_id = insert_id("varname");

	is_func_def_arg* arg = insert_func_def_arg(type_string, var_id);
	is_func_def_arg_list* args = insert_func_def_arg_list(arg, NULL);
	args->length = 1;

	symbol = symbol_new_func("System.out.println", 0, type_void, args, SYSTEM_OUT_PRINTLN);
	scope_insert(symtab, symbol);
}
