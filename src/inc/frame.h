#ifndef FRAME_H
#define FRAME_H

#define MAX_LOCALS
#define MAX_ARGS

typedef struct
{
	void *args[MAX_ARGS];
	int nargs;

	void *locals[MAX_LOCALS];
	
	void *retval;
	int retaddress; /* not really an "address", but a unique identifier (label) placed after every call to a function */
} FRAME;

#endif
