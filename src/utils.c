#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "inc/structures.h"
#include "inc/utils.h"

extern bool has_errors;
int last_line = -1;

int max(int x, int y)
{
	return x > y ? x : y;
}

int pretty_error(int line, char* format, ...)
{
	va_list argp;

	if (line == last_line)
		return 0;

	has_errors = true;
	fprintf(stderr, "%d: ", line);

	va_start(argp, format);
	vfprintf(stderr, format, argp);
	va_end(argp);

	fprintf(stderr, "\n");
	last_line = line;

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
