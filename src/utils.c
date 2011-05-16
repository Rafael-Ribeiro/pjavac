#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "inc/structures.h"
#include "inc/utils.h"

extern is_type_native operators_native[MAX_OPERATORS][MAX_NATIVE_TYPES][MAX_NATIVE_TYPES];
extern bool has_errors;

int max(int x, int y)
{
	return x > y ? x : y;
}

int pretty_error(int line, char* format, ...)
{
	va_list argp;

	has_errors = true;
	fprintf(stderr, "%d: ", line);

	va_start(argp, format);
	vfprintf(stderr, format, argp);
	va_end(argp);

	fprintf(stderr, "\n");
	return 0;
}

char* __strdup(const char* data)
{
	char* dest;
	int len;

	len = strlen(data) + 1; /* +1 to include \0 on both malloc and strncpy */
	dest = (char*)malloc(sizeof(char)*len);
	strncpy(dest, data, len);

	return dest;
}

bool type_long_like(is_type_decl* s_type)
{
	if (s_type->type != t_type_decl_type_object)
		return false;

	return operators_native[t_assign_op_eq][t_long][node->s_type->data->type_object->type] != ERROR;
}

bool type_bool_like(is_type_decl* s_type)
{
	if (s_type->type != t_type_decl_type_object)
		return false;

	return operators_native[t_assign_op_eq][t_bool][node->s_type->data->type_object->type] != ERROR;
}
