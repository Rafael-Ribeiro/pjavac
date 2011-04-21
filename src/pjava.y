%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "inc/structures.h"
#include "inc/insert.h"
#include "inc/show.h"
#include "inc/free.h"

is_application* main_application;
%}

/* TOKENS */
%token<val_constant>CONSTANT

%token BOOL
%token BREAK
%token BYTE
%token CASE
%token CHAR
%token CLASS
%token CONTINUE
%token DEFAULT
%token DO
%token DOUBLE
%token ELSE
%token FINAL
%token FLOAT
%token FOR
%token IF
%token INT
%token LONG
%token NEW
%token PRIVATE
%token PUBLIC
%token RETURN
%token SHORT
%token STATIC
%token SWITCH
%token VOID
%token WHILE

%token SYSOUT
%token<val_id>ID

%token SHIFT_R_ASSIGN
%token SHIFT_L_ASSIGN
%token ADD_ASSIGN
%token SUB_ASSIGN
%token MUL_ASSIGN
%token DIV_ASSIGN
%token MOD_ASSIGN
%token AND_ASSIGN
%token XOR_ASSIGN
%token OR_ASSIGN
%token SHIFT_R
%token SHIFT_L
%token INC_OP
%token DEC_OP
%token AND_OP
%token OR_OP
%token LE_OP
%token GE_OP
%token EQ_OP
%token NE_OP
%token EQ3_OP
%token NE3_OP

%token END

%nonassoc LOW_PREC

/* PRIORITIES */
%right SHIFT_R_ASSIGN SHIFT_L_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%right '='
%left '?' IF
%left ':' ELSE
%left OR_OP
%left AND_OP
%left '|'
%left '^'
%left '&'
%left EQ3_OP NE3_OP
%left EQ_OP NE_OP
%left '>' GE_OP
%left '<' LE_OP
%left SHIFT_R SHIFT_L
%left '+' '-'
%left '*' '%' '/'
%right INC_OP DEC_OP '~' '!' NEW
%left '(' ')'

/* TYPEs */
%union
{
	is_id* val_id;
	is_constant* val_constant;

	is_application* val_application;
	is_class_def* val_class_def;
	is_array_decl* val_array_decl;
	is_assign_op* val_assign_op;
	is_binary_op* val_binary_op;
	is_break* val_break;
	is_class_stmt* val_class_stmt;
	is_class_stmt_list* val_class_stmt_list;
	is_class_stmt_privacy* val_class_stmt_privacy;
	is_class_stmt_scope* val_class_stmt_scope;
	is_continue* val_continue;
	is_dims* val_dims;
	/*%type<val_dims_empty* val_dims_empty*/
	is_dims_empty_list val_dims_empty_list;	
	is_dims_sized* val_dims_sized;
	is_dims_sized_list* val_dims_sized_list;
	is_do_while* val_do_while;
	is_expr* val_expr;
	is_expr_list* val_expr_list;
	is_expr_op* val_expr_op;
	is_for* val_for;
	is_for_cond* val_for_cond;
	is_for_expr* val_for_expr;
	is_for_expr_list* val_for_expr_list;
	is_for_init* val_for_init;
	is_for_inc* val_for_inc;
	is_func_call* val_func_call;
	is_func_call_arg_list* val_func_call_arg_list;
	is_func_def* val_func_def;
	is_func_def_arg* val_func_def_arg;
	is_func_def_arg_list* val_func_def_arg_list;
	is_func_def_args* val_func_def_args;
	is_if* val_if;
	is_incr_op* val_incr_op;
	is_loop_stmt* val_loop_stmt;
	is_member_stmt* val_member_stmt;
	is_new_op* val_new_op;
	is_return* val_return;
	is_stmt* val_stmt;
	is_stmt_list* val_stmt_list;
	is_switch* val_switch;
	is_switch_stmt* val_switch_stmt;
	is_switch_stmt_list* val_switch_stmt_list;
	is_ternary_op* val_ternary_op;
	is_type_decl* val_type_decl;
	is_type_native val_type_native;
	is_type_object* val_type_object;
	is_unary_op* val_unary_op;
	is_var* val_var;
	is_var_def* val_var_def;
	is_var_def_list* val_var_def_list;
	is_var_defs* val_var_defs;
	is_var_initializer* val_var_initializer;
	is_var_initializer_list* val_var_initializer_list;
	is_var_stmt* val_var_stmt;
	is_while* val_while;
}

%type<val_application>application
%type<val_class_def>class_def
%type<val_array_decl>array_decl
%type<val_assign_op>assign_op
%type<val_binary_op>binary_op
%type<val_break>break;
%type<val_class_stmt>class_stmt
%type<val_class_stmt_privacy>class_stmt_privacy
%type<val_class_stmt_scope>class_stmt_scope
%type<val_class_stmt_list>class_stmt_list
%type<val_continue>continue
%type<val_dims>dims
/*%type<val_dims_empty>dims_empty*/
%type<val_dims_empty_list>dims_empty_list
%type<val_dims_sized>dims_sized
%type<val_dims_sized_list>dims_sized_list
%type<val_do_while>do_while
%type<val_expr>expr
%type<val_expr_list>expr_list
%type<val_expr_op>expr_op
%type<val_for>for
%type<val_for_cond>for_cond
%type<val_for_expr>for_expr
%type<val_for_expr_list>for_expr_list
%type<val_for_init>for_init
%type<val_for_inc>for_inc
%type<val_func_call>func_call
%type<val_func_call_arg_list>func_call_arg_list
%type<val_func_def>func_def
%type<val_func_def_arg>func_def_arg
%type<val_func_def_arg_list>func_def_arg_list
%type<val_func_def_args>func_def_args
%type<val_if>if
%type<val_incr_op>incr_op
%type<val_loop_stmt>loop_stmt
%type<val_member_stmt>member_stmt
%type<val_new_op>new_op
%type<val_return>return
%type<val_stmt>stmt
%type<val_stmt_list>stmt_list
%type<val_switch>switch
%type<val_switch_stmt>switch_stmt
%type<val_switch_stmt_list>switch_stmt_list
%type<val_ternary_op>ternary_op
%type<val_type_decl>type_decl
%type<val_type_native>type_native
%type<val_type_object>type_object
%type<val_unary_op>unary_op
%type<val_var>var
%type<val_var_def>var_def
%type<val_var_def_list>var_def_list
%type<val_var_defs>var_defs
%type<val_var_initializer>var_initializer
%type<val_var_initializer_list>var_initializer_list
%type<val_var_stmt>var_stmt
%type<val_while>while
%%
application
	: class_def END													{ $$ = $1; main_application = $1; return 0; }
	;

array_decl
	: type_object dims_empty_list									{ $$ = insert_array_decl($1, $2); }
	;

assign_op
	: var '=' expr													{ $$ = insert_assign_op($1, t_assign_op_eq, $3); }
	| var SHIFT_R_ASSIGN expr										{ $$ = insert_assign_op($1, t_assign_op_shift_r_eq, $3); }
	| var SHIFT_L_ASSIGN expr										{ $$ = insert_assign_op($1, t_assign_op_shift_l_eq, $3); }
	| var ADD_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_add_eq, $3); }
	| var SUB_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_sub_eq, $3); }
	| var MUL_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_mul_eq, $3); }
	| var DIV_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_div_eq, $3); }
	| var MOD_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_mod_eq, $3); }
	| var AND_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_and_eq, $3); }
	| var XOR_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_xor_eq, $3); }
	| var OR_ASSIGN expr											{ $$ = insert_assign_op($1, t_assign_op_or_eq, $3); }
	;

binary_op
	: expr '+' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_add, $3); }
	| expr '-' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_sub, $3); }
	| expr '*' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_mul, $3); }
	| expr '/' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_div, $3); }
	| expr '%' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_mod, $3); }

	| expr '&' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_and, $3); }
	| expr '|' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_or, $3); }
	| expr '^' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_xor, $3); }
	| expr SHIFT_R expr												{ $$ = insert_binary_op_operation($1, t_binary_op_shift_r, $3); }
	| expr SHIFT_L expr												{ $$ = insert_binary_op_operation($1, t_binary_op_shift_l, $3); }
	
	| expr AND_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_logic_and, $3); }
	| expr OR_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_logic_or, $3); }

	| expr EQ_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_eq, $3); }
	| expr NE_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_ne, $3); }
	| expr '<' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_l, $3); }
	| expr '>' expr													{ $$ = insert_binary_op_operation($1, t_binary_op_g, $3); }
	| expr LE_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_le, $3); }
	| expr GE_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_ge, $3); }
	| expr EQ3_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_eq3, $3); }
	| expr NE3_OP expr												{ $$ = insert_binary_op_operation($1, t_binary_op_ne3, $3); }
	| assign_op														{ $$ = insert_binary_op_assign($1); }
	;

break
	: BREAK ';'														{ $$ = insert_break(NULL); }
	| BREAK ID ';'													{ $$ = insert_break($2); } /* TODO labeled loops */
	;

class_def
	: CLASS ID '{' '}'												{ $$ = insert_class_def($2, NULL); }
	| CLASS ID '{' class_stmt_list '}'								{ $$ = insert_class_def($2, $4); }
	;

class_stmt
	: member_stmt													{ $$ = insert_class_stmt(NULL, NULL, $1); }
	| class_stmt_privacy member_stmt								{ $$ = insert_class_stmt($1, NULL, $2); }
	| class_stmt_scope member_stmt									{ $$ = insert_class_stmt(NULL, $1, $2); }
	| class_stmt_privacy class_stmt_scope member_stmt				{ $$ = insert_class_stmt($1, $2, $3); }
	;

class_stmt_privacy
	: PUBLIC														{ $$ = insert_class_stmt_privacy(t_class_stmt_privacy_public); }
	| PRIVATE														{ $$ = insert_class_stmt_privacy(t_class_stmt_privacy_private); }
	;

class_stmt_scope
	: FINAL															{ $$ = insert_class_stmt_scope(true, false); }
	| STATIC														{ $$ = insert_class_stmt_scope(false, true); }
	| STATIC FINAL													{ $$ = insert_class_stmt_scope(true, true); } 
	| FINAL STATIC													{ $$ = insert_class_stmt_scope(true, true); }
	;

class_stmt_list
	: class_stmt													{ $$ = insert_class_stmt_list($1, NULL); }
	| class_stmt class_stmt_list									{ $$ = insert_class_stmt_list($1, $2); }
	;

continue
	: CONTINUE ';'													{ $$ = insert_continue(NULL); }
	| CONTINUE ID ';'												{ $$ = insert_continue($2); } /* TODO labeled loops */
	;

dims
	: dims_sized_list												{ $$ = insert_dims($1, 0); }
	| dims_sized_list dims_empty_list								{ $$ = insert_dims($1, $2); }
	;

dims_empty
	: '[' ']'														{ }
	;

dims_empty_list
	: dims_empty													{ $$ = 1; }
	| dims_empty_list dims_empty									{ $$ = $1 + 1; }
	;

dims_sized
	: '[' expr ']'													{ $$ = $2; }
	;

/* this one is left recursive, can we swap it? if not attention to the constructors */
dims_sized_list 
	: dims_sized													{ $$ = insert_dims_sized_list(NULL, $1); }
	| dims_sized_list dims_sized									{ $$ = insert_dims_sized_list($1, $2); }
	; 

do_while
	: DO stmt WHILE '(' expr ')' ';'								{ $$ = insert_do_while($2, $5); }
	;

expr
	: var %prec LOW_PREC											{ $$ = insert_expr_var($1); }
	| new_op %prec LOW_PREC											{ $$ = insert_expr_new_op($1); }
	| '(' expr ')'													{ $$ = $2; }
	| '(' type_decl ')' expr									 	{ $$ = insert_expr_type_cast($4, $2); }
	| CONSTANT														{ $$ = insert_expr_constant($1); }
	| func_call														{ $$ = insert_expr_func_call($1); }
	| expr_op														{ $$ = insert_expr_expr_op($1); }
	;

expr_list
	: expr															{ $$ = insert_expr_list($1, NULL); }
	| expr ',' expr_list											{ $$ = insert_expr_list($1, $3); }
	;

expr_op
	: unary_op														{ $$ = insert_expr_op_unary($1); }
	| binary_op														{ $$ = insert_expr_op_binary($1); }
	| ternary_op													{ $$ = insert_expr_op_ternary($1); }
	;
for
	: FOR '(' for_init ';' for_cond ';' for_inc ')' stmt			{ $$ = insert_for($3, $5, $7, $9); }
	;

for_cond
	: /* empty */													{ $$ = NULL; }
	| expr															{ $$ = $1; }
	;

for_expr
	: incr_op														{ $$ = insert_for_expr_incr($1); }
	| assign_op														{ $$ = insert_for_expr_assign($1); }
	| func_call														{ $$ = insert_for_expr_func_call($1); }
	;

for_expr_list
	: for_expr													 	{ $$ = insert_for_expr_list($1, NULL); }
	| for_expr ',' for_expr_list									{ $$ = insert_for_expr_list($1, $3); }
	;

for_init
	: /* empty */													{ $$ = NULL; }
	| var_defs														{ $$ = insert_for_init_var_defs($1); }
	| for_expr_list													{ $$ = insert_for_init_for_expr_list($1); }
	;

for_inc
	: /* empty */													{ $$ = NULL; }
	| for_expr_list													{ $$ = $1; }
	;
 	
func_call
	: ID func_call_arg_list											{ $$ = insert_func_call_id($1, $2); }
	| SYSOUT func_call_arg_list										{ $$ = insert_func_call_sysout($2); }
	;

func_call_arg_list
	: '(' ')'														{ $$ = NULL; }
	| '(' expr_list ')'												{ $$ = $2; }
	;

func_def
	: type_decl ID func_def_args '{' '}'							{ $$ = insert_func_def($1, $2, $3, NULL); } 
	| type_decl ID func_def_args '{' stmt_list '}'					{ $$ = insert_func_def($1, $2, $3, $5); }
	;

func_def_arg
	: type_decl ID													{ $$ = insert_func_def_arg($1, $2); }
	;

func_def_arg_list
	: func_def_arg													{ $$ = insert_func_def_arg_list($1, NULL); }
	| func_def_arg ',' func_def_arg_list							{ $$ = insert_func_def_arg_list($1, $3); }
	;

func_def_args
	: '(' ')'														{ $$ = NULL; }
	| '(' func_def_arg_list ')'										{ $$ = $2; }
	;

if
	: IF '(' expr ')' stmt %prec LOW_PREC							{ $$ = insert_if($3, $5, NULL); }
	| IF '(' expr ')' stmt ELSE stmt								{ $$ = insert_if($3, $5, $7); }
	;

incr_op
	: INC_OP var													{ $$ = insert_incr_op(t_incr_op_inc, true, $2); }
	| var INC_OP 													{ $$ = insert_incr_op(t_incr_op_inc, false, $1); }
	| DEC_OP var 													{ $$ = insert_incr_op(t_incr_op_dec, true, $2); }
	| var DEC_OP 	 												{ $$ = insert_incr_op(t_incr_op_dec, false, $1); }
	;

loop_stmt
	: for															{ $$ = insert_loop_stmt_for($1); }
	| while															{ $$ = insert_loop_stmt_while($1); }
	| do_while														{ $$ = insert_loop_stmt_do_while($1); }
	;

member_stmt
	: ';'															{ $$ = NULL; }
	| var_stmt														{ $$ = insert_member_stmt_var($1); }
	| func_def														{ $$ = insert_member_stmt_func_def($1); }
	;

new_op
	: NEW type_object dims											{ $$ = insert_new_op($2, $3); }
	;

return
	: RETURN ';'													{ $$ = insert_return(NULL); }
	| RETURN expr ';'												{ $$ = insert_return($2); }
	;

stmt
	: ';'															{ $$ = NULL; }
	| '{' '}'														{ $$ = NULL; } 
	| '{' stmt_list '}'												{ $$ = insert_stmt_stmt_list($2); }
	| var_stmt														{ $$ = insert_stmt_var_stmt($1); }
	| assign_op ';'													{ $$ = insert_stmt_assign_op($1); }
	| incr_op ';'													{ $$ = insert_stmt_incr_op($1); }
	| if															{ $$ = insert_stmt_if($1); }
	| loop_stmt														{ $$ = insert_stmt_loop_stmt($1); }
	| func_call	';'													{ $$ = insert_stmt_func_call($1); }
	| switch														{ $$ = insert_stmt_switch($1); }
	| break															{ $$ = insert_stmt_break($1); }
	| continue														{ $$ = insert_stmt_continue($1); }
	| return														{ $$ = insert_stmt_return($1); }
	;

stmt_list
	: stmt															{ $$ = insert_stmt_list($1, NULL);}
	| stmt stmt_list												{ $$ = insert_stmt_list($1, $2); }
	;

switch
	: SWITCH '(' expr ')' '{' '}'									{ $$ = insert_switch($3, NULL); }
	| SWITCH '(' expr ')' '{' switch_stmt_list '}'					{ $$ = insert_switch($3, $6); }
	;

switch_stmt
	: DEFAULT ':'													{ $$ = insert_switch_stmt_default(NULL); }
	| DEFAULT ':' stmt_list											{ $$ = insert_switch_stmt_default($3); }
	| CASE CONSTANT ':'												{ $$ = insert_switch_stmt_case($2, NULL); }
	| CASE CONSTANT ':' stmt_list									{ $$ = insert_switch_stmt_case($2, $4); }
	;

switch_stmt_list
	: switch_stmt													{ $$ = insert_switch_stmt_list($1, NULL); }
	| switch_stmt switch_stmt_list 									{ $$ = insert_switch_stmt_list($1, $2); }
	;

ternary_op
	: expr '?' expr ':' expr										{ $$ = insert_ternary_op($1, $3, $5); }
	;

type_decl
	: type_object													{ $$ = insert_type_decl_object($1); }
	| array_decl													{ $$ = insert_type_decl_array($1); }
	;

type_native
	: BOOL															{ $$ = t_type_native_bool; }
	| BYTE															{ $$ = t_type_native_byte; }
	| CHAR															{ $$ = t_type_native_char; }
	| DOUBLE														{ $$ = t_type_native_double; }
	| FLOAT															{ $$ = t_type_native_float; }
	| INT															{ $$ = t_type_native_int; }
	| LONG															{ $$ = t_type_native_long; }
	| SHORT															{ $$ = t_type_native_short; }
	| VOID															{ $$ = t_type_native_void; }
	;

type_object
	: type_native													{ $$ = insert_type_object($1); }
	/* | ID															{ } Object constructors */
	;

unary_op
	: incr_op														{ $$ = insert_unary_op_incr($1); }
	| '+' expr														{ $$ = insert_unary_op_operation(t_unary_op_operator_plus, $2); }
	| '-' expr														{ $$ = insert_unary_op_operation(t_unary_op_operator_minus, $2); }
	| '!' expr														{ $$ = insert_unary_op_operation(t_unary_op_operator_not, $2); }
	| '~' expr														{ $$ = insert_unary_op_operation(t_unary_op_operator_bin_not, $2); }
	;

var
	: ID %prec LOW_PREC												{ $$ = insert_var_id($1); }
	| '(' var ')' 													{ $$ = $2; } 
	| '(' new_op ')'												{ $$ = insert_var_new_op($2); } 
	| var dims_sized												{ $$ = insert_var_var_subscript($1, $2); } 
	| func_call dims_sized											{ $$ = insert_var_func_subscript($1, $2); }
	;

var_def
	: ID															{ $$ = insert_var_def($1, 0, NULL); }
	| ID dims														{ $$ = insert_var_def($1, $2, NULL); }
	| ID '=' var_initializer										{ $$ = insert_var_def($1, 0, $3); }
	| ID dims '=' var_initializer									{ $$ = insert_var_def($1, $2, $4); }
	;

var_def_list
	: var_def														{ $$ = insert_var_def_list($1, NULL); }
	| var_def ',' var_def_list										{ $$ = insert_var_def_list($1, $3); }
	;

var_defs
	: type_decl var_def_list										{ $$ = insert_var_defs($1, $2); }
	;

var_initializer
	: '{' '}' 														{ $$ = insert_var_initializer_array(NULL); }
	| '{' var_initializer_list '}'									{ $$ = insert_var_initializer_array($2); }
	| '{' var_initializer_list ',' '}'								{ $$ = insert_var_initializer_array($2); }
	| expr															{ $$ = insert_var_initializer_expr($1); }
	;

/* this one is left recursive, can we swap it? if not attention to the constructors */
var_initializer_list
	: var_initializer												{ $$ = insert_var_initializer_list(NULL, $1); }
	| var_initializer_list ',' var_initializer						{ $$ = insert_var_initializer_list($1, $3); }
 	;

var_stmt															
	: var_defs ';'													{ $$ = $1; }
	;

while
	: WHILE '(' expr ')' stmt										{ $$ = insert_while($3, $5); }
	;

%%
int main()
{
	main_application = NULL;
	yyparse();

	if (main_application)
	{
		printf("Valid syntax!\n");
		show_application(main_application, 0);
		free_application(main_application);
	}

	return 0;
}
