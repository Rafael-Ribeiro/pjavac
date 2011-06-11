#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/symtab.h"
#include "inc/insert.h"
#include "inc/builtins.h"
#include "inc/free.h"

is_func_def_arg_list* builtin_sysout_args = NULL;

void insert_builtins()
{
	is_type_decl* type_void = new_type_decl_void(0);
	is_type_decl* type_int = insert_type_decl_object(insert_type_object(t_type_native_int));
	is_type_decl* type_string = insert_type_decl_object(insert_type_object(t_type_native_string));

	is_id* var_id = insert_id("string");

	SYMBOL *builtin_sysout_symbol = NULL;
	SYMBOL *builtin_sysin_symbol = NULL;

	is_func_def_arg* arg = insert_func_def_arg(type_string, var_id);
	builtin_sysout_args = insert_func_def_arg_list(arg, NULL);
	builtin_sysout_args->length = 1;

	builtin_sysout_symbol = symbol_new_func("System.out.println", 0, type_void, builtin_sysout_args, SYSTEM_OUT_PRINTLN);
	scope_insert(symtab, builtin_sysout_symbol);

	/* nextInt */

	builtin_sysin_symbol = symbol_new_func("System.in.nextInt", 0, type_int, NULL, SYSTEM_IN_NEXTINT);
	scope_insert(symtab, builtin_sysin_symbol);

	/* free only the ret vals because they are copied; the args must be free'd after */
	free_type_decl(type_void);
	free_type_decl(type_int);
}

void free_builtins()
{
	free_func_def_arg_list(builtin_sysout_args);
}
