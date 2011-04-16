%{
#include<stdio.h>
%}

/* TOKENS */
%token CONSTANT

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

%token ID

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

%nonassoc REDUCE

/* PRIORITY */
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

%%

/*
	TODO: dims
		dims_empty_list can follow dims_sized (e.g: new int[2][]) but makes a shift/reduce conflict
*/

application
	: class_def END													{ return 0; }
	;

array_decl
	: type_decl '[' ']'												{ }
	;

array_initializer
	: '{' '}'														{ }
	| '{' expr_list '}'												{ }
/*	| '{' expr_list ',' '}'											{ } */
	; 

assign_op
	: var '=' expr													{ }
	| var SHIFT_R_ASSIGN expr										{ }
	| var SHIFT_L_ASSIGN expr										{ }
	| var ADD_ASSIGN expr											{ }
	| var SUB_ASSIGN expr											{ }
	| var MUL_ASSIGN expr											{ }
	| var DIV_ASSIGN expr											{ }
	| var MOD_ASSIGN expr											{ }
	| var AND_ASSIGN expr											{ }
	| var XOR_ASSIGN expr											{ }
	| var OR_ASSIGN expr											{ }
	;

binary_op
	: expr '+' expr													{ }
	| expr '-' expr													{ }
	| expr '*' expr													{ }
	| expr '/' expr													{ }
	| expr '%' expr													{ }

	| expr '&' expr													{ }
	| expr '|' expr													{ }
	| expr '^' expr													{ }
	| expr SHIFT_R expr												{ }
	| expr SHIFT_L expr												{ }
	
	| expr AND_OP expr												{ }
	| expr OR_OP expr												{ }

	| expr EQ_OP expr												{ }
	| expr NE_OP expr												{ }
	| expr '<' expr													{ }
	| expr '>' expr													{ }
	| expr LE_OP expr												{ }
	| expr GE_OP expr												{ }
	| expr EQ3_OP expr												{ }
	| expr NE3_OP expr												{ }
	| assign_op														{ }
	;

break
	: BREAK ';'														{ }
	| BREAK ID ';'													{ } /* TODO labeled loops */
	;

class_decl_list
	: class_stmt													{ }
	| class_stmt class_decl_list									{ }
	;

class_def
	: CLASS ID '{' '}'												{ } 
	| CLASS ID '{' class_decl_list '}'								{ }
	;

class_stmt
	: member_stmt													{ }
	| class_stmt_privacy member_stmt								{ }
	| class_stmt_scope member_stmt									{ }
	| class_stmt_privacy class_stmt_scope member_stmt				{ }
	;

class_stmt_privacy
	: PUBLIC														{ }
	| PRIVATE														{ }
	;

class_stmt_scope
	: FINAL															{ }
	| STATIC														{ }
	| STATIC FINAL													{ }
	| FINAL STATIC													{ }
	;

compound_stmt
	: stmt															{ }
	| '{' '}'														{ }
	| '{' compound_stmt_list '}'									{ }
	;

compound_stmt_list
	: compound_stmt													{ }
	| compound_stmt compound_stmt_list								{ }
	;

continue
	: CONTINUE ';'													{ }
	| CONTINUE ID ';'												{ } /* TODO labeled loops */
	;

dims:
	| dims_sized_list dims_empty_list								{ } 
	;

dims_empty_list
	: /* empty */													{ }
	| dims_empty_list '[' ']'										{ }
	;

dims_sized
	: '[' expr ']'													{ }
	;

dims_sized_list 
	: dims_sized													{ }
	| dims_sized dims_sized_list									{ }
	; 

do_while
	: DO compound_stmt WHILE '(' expr ')' ';'						{ }
	;

expr
	: var 															{ }
	| array_initializer												{ }
	| expr_paren													{ }
	;

expr_list
	: expr															{ }
	| expr ',' expr_list											{ }
	;

expr_op
	: unary_op														{ }
	| binary_op														{ }
	| ternary_op													{ }
	;

expr_paren
	: '(' expr_paren ')'											{ }
	| CONSTANT														{ }
	| new_op														{ }
	| func_call														{ }
	| expr_op														{ }
	;

for
	: FOR '(' for_init ';' for_cond ';' for_inc ')' compound_stmt	{ }
	;

for_cond
	: /* empty */													{ }
	| expr															{ }
	;

for_inc /* TODO: Same as for init; for_inc cannot be an expr_list for the same reason */
	: /* empty */													{ }
	| expr_list														{ }
	;

for_init
	: /* empty */
	| for_init_list
	| var_defs														{ }
	;

for_init_list /* Cannot be expr_list; e.g.: for(i;;) is invalid */
	: assign_op
	| incr_op
	| func_call
	;

func_call
	: ID func_call_arg_list
	;

func_call_arg_list
	: '(' ')'														{ }
	| '(' expr_list ')'												{ }
	;

func_def
	: type_decl ID func_def_args '{' '}'							{ } 
	| type_decl ID func_def_args '{' compound_stmt_list '}'			{ }
	;

func_def_arg
	: type_decl var													{ }
	;

func_def_arg_list
	: func_def_arg													{ }
	| func_def_arg ',' func_def_arg_list							{ }
	;

func_def_args
	: '(' ')'														{ }
	| '(' func_def_arg_list ')'										{ }
	;

if
	: IF '(' expr ')' compound_stmt	%prec REDUCE					{ }
	| IF '(' expr ')' compound_stmt	ELSE compound_stmt				{ }
	;

incr_op
	: INC_OP var													{ }
	| var INC_OP													{ }
	| DEC_OP var													{ }
	| var DEC_OP													{ }
	;

loop_stmt
	: for															{ }
	| while															{ }
	| do_while														{ }
	;

member_stmt
	: var_stmt														{ }
	| func_def														{ }
	;

new_op
	: NEW type_object dims											{ }
	;

return
	: RETURN ';'													{ }
	| RETURN expr ';'												{ }
	;

stmt
	: ';'															{ }
	| var_stmt														{ }
	| assign_op ';'													{ }
	| incr_op ';'													{ }
	| if															{ }
	| loop_stmt
	| switch														{ }
	| break															{ }
	| continue														{ }
	| return														{ }
	;

switch
	: SWITCH '(' expr ')' '{' '}'									{ }
	| SWITCH '(' expr ')' '{' switch_stmt_list '}'					{ }
	;

switch_stmt
	: DEFAULT ':'													{ }
	| DEFAULT ':' compound_stmt_list								{ }
	| CASE CONSTANT ':'												{ }
	| CASE CONSTANT ':' compound_stmt_list							{ }
	;

switch_stmt_list
	: switch_stmt													{ }
	| switch_stmt switch_stmt_list 									{ }
	;

ternary_op
	: expr '?' expr ':' expr										{ }
	;

type_decl
	: type_object													{ }
	| array_decl													{ }
	;

type_native
	: BOOL															{ }
	| BYTE															{ }
	| CHAR															{ }
	| DOUBLE														{ }
	| FLOAT															{ }
	| INT															{ }
	| LONG															{ }
	| SHORT															{ }
	| VOID															{ }
	;

type_object
	: type_native													{ }
	/* | ID															{ } Object constructors */
	;

unary_op
	: incr_op														{ }
	| '+' expr														{ }
	| '-' expr														{ }
	| '!' expr														{ }
	| '~' expr														{ }
	;

var
	: ID															{ }
	| '(' var ')' 													{ }
	| var '[' expr ']'												{ }
	| func_call '[' expr ']'										{ }
	;

var_def
	: ID															{ }
	| ID dims_empty_list '=' expr									{ }
	;

var_def_list
	: var_def														{ }
	| var_def ',' var_def_list										{ }
	;

var_defs
	: type_decl var_def_list										{ }
	;

var_stmt															
	: var_defs ';'													{ }
	;

while
	: WHILE '(' expr ')' compound_stmt								{ }
	;

%%
int main()
{
	yyparse();
}
