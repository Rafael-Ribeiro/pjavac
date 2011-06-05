#include <stdbool.h>
#include <string.h>
#include "../inc/builtins.h"

#define MAX_BUFFER_SIZE 200

char buffer[MAX_BUFFER_SIZE];

LABEL_SYSTEM_OUT_PRINTLN:
	/* no need to alocate a stack frame */
	printf("%s\n", *(char**)_fp->args[0]);
	goto redirector;

bool_to_string:
	if (*(bool*)_fp->args[0] == true)
		goto bool_to_string_true;

	/* else: */
		_fp->retval = strdup("false");
		goto bool_to_string_end;

	bool_to_string_true:
		_fp->retval = strdup("true");

	bool_to_string_end:
	goto redirector;

byte_to_string:
	sprintf(buffer, "%hhd", *(char*)_fp->args[0]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

char_to_string:
	sprintf(buffer, "%c", *(char*)_fp->args[0]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

double_to_string:
	sprintf(buffer, "%lf", *(double*)_fp->args[0]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

float_to_string:
	sprintf(buffer, "%f", *(float*)_fp->args[0]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

int_to_string:
	sprintf(buffer, "%d", *(int*)_fp->args[0]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

long_to_string:
	sprintf(buffer, "%lld", *(long long*)_fp->args[0]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

short_to_string:
	sprintf(buffer, "%d", *(short*)_fp->args[0]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

string_concat:
	sprintf(buffer, "%s%s", *(char**)_fp->args[0], *(char**)_fp->args[1]);
	_fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy((char*)_fp->retval, buffer);

	goto redirector;

