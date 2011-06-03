#ifndef FRAME_H
#define FRAME_H

#define MAX_LOCALS 64
#define MAX_ARGS 16

typedef struct _FRAME
{
	void *args[MAX_ARGS];
	int nargs;

	void *locals[MAX_LOCALS];
	
	void *retval;
	int retaddr; /* not really an "address", but a unique identifier (label) placed after every call to a function */

	struct _FRAME *parent;
} FRAME;

#endif
