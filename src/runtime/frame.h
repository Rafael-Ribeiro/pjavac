#ifndef FRAME_H
#define FRAME_H

#define MAX_GLOBALS 64
#define MAX_LOCALS 64
#define MAX_REGISTERS 64
#define MAX_ARGS 16

typedef long long REGISTER;

typedef struct _FRAME
{
	REGISTER args[MAX_ARGS];
	REGISTER locals[MAX_LOCALS];
	REGISTER registers[MAX_REGISTERS];

	REGISTER retval;
	REGISTER retaddr; /* not really an "address", but a unique identifier (label) placed after every call to a function */

	struct _FRAME *parent;
} FRAME;

#endif
