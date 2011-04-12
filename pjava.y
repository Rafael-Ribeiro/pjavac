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

/* PRIORITY */
%right SHIFT_R_ASSIGN SHIFT_L_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%right '='
%left '?' ':' /* Solves shift-reduces conflict, is this valid? */
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

application:
	class_def END													{ return 0; }
	;

assign_op:
	ID SHIFT_R_ASSIGN expr
	| SHIFT_L_ASSIGN expr
	| ADD_ASSIGN expr
	| SUB_ASSIGN expr
	| MUL_ASSIGN expr
	| DIV_ASSIGN expr
	| MOD_ASSIGN expr
	| AND_ASSIGN expr
	| XOR_ASSIGN expr
	| OR_ASSIGN expr
	;

binary_op:
	expr '+' expr													{ }
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
	| assign_op													{ }
	;

class_decl_list:
	class_stmt														{ }
	| class_stmt class_decl_list									{ }
	;

class_def:
	CLASS ID '{' class_decl_list '}'								{ }
	;

class_stmt:
	member_stmt														{ }
	| class_stmt_privacy member_stmt								{ }
	| class_stmt_scope member_stmt									{ }
	| class_stmt_privacy class_stmt_scope member_stmt				{ }
	;

class_stmt_privacy:
	PUBLIC															{ }
	| PRIVATE														{ }
	;

class_stmt_scope:
	FINAL															{ }
	| STATIC														{ }
	| STATIC FINAL													{ }
	| FINAL STATIC													{ }
	;

compound_stmt:
	';'
	| stmt															{ }
	| '{' stmt_list '}'												{ }
	;

expr:
	'(' expr ')' 													{ }
	| ID 															{ }
	| CONSTANT														{ }
	| unary_op														{ }
	| binary_op														{ }
	| ternary_op													{ }
	;

expr_list:
	expr															{ }
	| expr ',' expr_list											{ }
	;

for:
	FOR '(' expr_list ';' expr ';' expr_list ')' compound_stmt		{ }
	;

func_call_arg_list:
	'(' ')'															{ }
	| '(' expr_list ')'												{ }
	;

func_def:
	type_decl ID func_def_args_list '{' stmt_list '}'				{ }
	;

func_def_args_list:
	var_decl														{ }
	| var_decl ',' func_def_args_list								{ }
	;

func_def_args:
	'(' ')'															{ }
	| '(' func_def_args_list ')'									{ }
	;

member_stmt:
	var_stmt														{ }
	| func_def														{ }
	;

stmt:
	var_stmt														{ }
	| var_assign													{ }
/*
	| if															{ }
	| for															{ }
	| while															{ }
	| do_while														{ }
	| switch														{ }
	| break															{ }
	| continue														{ }
	| return														{ }
*/
	;

stmt_list:
	stmt															{ }
	| stmt stmt_list	 											{ }
	;

ternary_op:
	expr '?' expr ':' expr											{ }
	;

type_decl:
	BOOL															{ }
	| BYTE															{ }
	| CHAR															{ }
	| DOUBLE														{ }
	| FLOAT															{ }
	| INT															{ }
	| LONG															{ }
	| SHORT															{ }
	| VOID															{ }
	;

unary_op:
	INC_OP ID														{ }
	| ID INC_OP														{ }
	| DEC_OP ID														{ }
	| ID DEC_OP														{ }
	| '!' ID														{ }
	| '~' ID														{ }
	;

var_assign:
	ID '=' expr ';'													{ }
/* 
	TODO's
	<<=
	etc..
*/
	;

var_decl:
	type_decl ID													{ }
	;

var_def:
	type_decl ID '=' expr											{ }
	;
	
var_stmt:
	var_decl ';'													{ }
	| var_def ';'													{ }
	;

while:
	WHILE '(' expr ')' compound_stmt
	;

%%
int main()
{
	yyparse();
}
