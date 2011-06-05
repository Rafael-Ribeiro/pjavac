#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "runtime/frame.h"

int main(int _argc, char **_argv)
{
	void* _temp_ret;
	void* _globals[MAX_GLOBALS];
	FRAME *_fp = NULL, *_temp_frame;

	goto post_builtins;
	#include "runtime/builtins.h"

post_builtins: ;
	goto label_1_postend;

label_1:
	; /* func2 */
	_temp_frame = (FRAME*)malloc(sizeof(FRAME));
	_temp_frame->parent = _fp;

	_fp = _temp_frame;

	/* func2 body */
	int _temp_0 = 1;
	_temp_ret = &_temp_0;
	goto label_1_end;


label_1_end:
	/* end of func2 */
	_fp->parent->retval = _temp_ret;
	_temp_frame = _fp->parent;
	free(_fp);
	_fp = _temp_frame;

	goto redirector;

label_1_postend:
	; /* post end of func2 */

	goto label_2_postend;

label_2:
	; /* func */
	_temp_frame = (FRAME*)malloc(sizeof(FRAME));
	_temp_frame->parent = _fp;

	_fp = _temp_frame;

	/* func body */
	/* function call: func2 */
	_fp->retaddr = 3;
	goto label_1;

label_3:
	; /* end of func call*/
	int _temp_1 = *(int*)_fp->retval;
	_temp_ret = &_temp_1;
	goto label_2_end;


label_2_end:
	/* end of func */
	_fp->parent->retval = _temp_ret;
	_temp_frame = _fp->parent;
	free(_fp);
	_fp = _temp_frame;

	goto redirector;

label_2_postend:
	; /* post end of func */

	goto label_0_postend;

label_0:
	; /* main */
	_temp_frame = (FRAME*)malloc(sizeof(FRAME));
	_temp_frame->parent = _fp;

	_fp = _temp_frame;

	/* main body */
	char* _temp_2 = strdup("");
	/* function call: func */
	_fp->retaddr = 5;
	goto label_2;

label_5:
	; /* end of func call*/
	int _temp_3 = *(int*)_fp->retval;
	/* conversion from int to string */
	_fp->retaddr = 6;
	_fp->args[0] = (int*)malloc(sizeof(int));
	*(int*)_fp->args[0] = _temp_3;
	goto int_to_string;

label_6: ;
	; /* temp_4 gets the string */
	char* _temp_4 = (char*)_fp->retval;

	/* string + string */
	_fp->retaddr = 7;
	_fp->args[0] = (char**)malloc(sizeof(char*));
	_fp->args[1] = (char**)malloc(sizeof(char*));
	*(char**)_fp->args[0] = _temp_2;
	*(char**)_fp->args[1] = _temp_4;
	goto string_concat;

label_7:
	; /* temp_5 gets the concatenated string */
	char* _temp_5 = (char*)_fp->retval;


	/* function call: System.out.println */
	_fp->retaddr = 4;
	_fp->args[0] = &_temp_5;
	goto label_2147483647;

label_4:
	; /* end of func call*/

label_0_end:
	/* end of main */
	_temp_frame = _fp->parent;
	free(_fp);
	_fp = _temp_frame;

	goto redirector;

label_0_postend:
	; /* post end of main */

	/* entry point */
	goto label_0;

redirector:
	if (_fp == NULL)
		goto label_end;
	if (_fp->retaddr == 0)
		goto label_0;
	if (_fp->retaddr == 1)
		goto label_1;
	if (_fp->retaddr == 2)
		goto label_2;
	if (_fp->retaddr == 3)
		goto label_3;
	if (_fp->retaddr == 4)
		goto label_4;
	if (_fp->retaddr == 5)
		goto label_5;
	if (_fp->retaddr == 6)
		goto label_6;
	if (_fp->retaddr == 7)
		goto label_7;

label_end:
	return 0;
}
