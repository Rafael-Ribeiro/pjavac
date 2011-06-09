#include "../inc/builtins.h"

#define MAX_BUFFER_SIZE 200

char buffer[MAX_BUFFER_SIZE];

goto LABEL_SYSTEM_OUT_PRINTLN; /* warning suppression */
LABEL_SYSTEM_OUT_PRINTLN:
	/* no need to alocate a stack frame */
	printf("%s\n", *(char**)& _fp->args[0]);
	goto redirector;

goto LABEL_SYSTEM_IN_NEXTINT;
LABEL_SYSTEM_IN_NEXTINT:
	/* no need to alocate a stack frame */
	scanf("%d", (int*)& _fp->retval);
	goto redirector;

goto bool_to_string; /* warning suppression */
bool_to_string:
	if (*(bool*)& _fp->args[0] == true)
		goto bool_to_string_true;

	/* else: */
		*(char**)& _fp->retval = __strdup("false");
		goto bool_to_string_end;

	bool_to_string_true:
		*(char**)& _fp->retval = __strdup("true");

	bool_to_string_end:
	goto redirector;

goto byte_to_string; /* warning suppression */
byte_to_string:
	sprintf(buffer, "%hhd", *(char*)& _fp->args[0]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

goto char_to_string; /* warning suppression */
char_to_string:
	sprintf(buffer, "%c", *(char*)& _fp->args[0]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

goto double_to_string; /* warning suppression */
double_to_string:
	sprintf(buffer, "%lf", *(double*)& _fp->args[0]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

goto float_to_string; /* warning suppression */
float_to_string:
	sprintf(buffer, "%f", *(float*)& _fp->args[0]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

goto int_to_string; /* warning suppression */
int_to_string:
	sprintf(buffer, "%d", *(int*)& _fp->args[0]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

goto long_to_string; /* warning suppression */
long_to_string:
	sprintf(buffer, "%lld", *(long long*)& _fp->args[0]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

goto short_to_string; /* warning suppression */
short_to_string:
	sprintf(buffer, "%d", *(short*)& _fp->args[0]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

goto string_concat; /* warning suppression */
string_concat:
	sprintf(buffer, "%s%s", *(char**)& _fp->args[0], *(char**)& _fp->args[1]);
	*(char**)& _fp->retval = malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(*(char**)& _fp->retval, buffer);

	goto redirector;

