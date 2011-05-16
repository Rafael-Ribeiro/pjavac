#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "inc/utils.h"

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

