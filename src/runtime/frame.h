#ifndef FRAME_H
#define FRAME_H

#define MAX_GLOBALS 64
#define MAX_LOCALS 64
#define MAX_REGISTERS 64
#define MAX_ARGS 16

typedef char REGISTER[8];

typedef struct _FRAME
{
	void *args[MAX_ARGS];
	void *locals[MAX_LOCALS];
	REGISTER registers[MAX_REGISTERS];

	void *retval;
	int retaddr; /* not really an "address", but a unique identifier (label) placed after every call to a function */

	struct _FRAME *parent;
} FRAME;

#endif
