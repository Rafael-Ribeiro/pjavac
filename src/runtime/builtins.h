#include "../inc/builtins.h"

label_SYSTEM_OUT_PRINTLN:
	/* no need to alocate a stack frame */
	printf("%s\n", (char*)_fp->args[0]);
	goto redirector;
