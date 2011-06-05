#include "../inc/builtins.h"

LABEL_SYSTEM_OUT_PRINTLN:
	/* no need to alocate a stack frame */
	printf("%s\n", *(char**)_fp->args[0]);
	goto redirector;

bool_to_string:

	goto redirector;

byte_to_string:

	goto redirector;

char_to_string:

	goto redirector;

double_to_string:

	goto redirector;

float_to_string:

	goto redirector;

int_to_string:

	goto redirector;

long_to_string:

	goto redirector;

short_to_string:

	goto redirector;

