%{
#include <stdlib.h>
#include <stdbool.h>

#include "inc/structures.h"
#include "inc/insert.h"
#include "y.tab.h"
%}

N8					[0-7]
N10					[0-9]
N16					[0-9a-fA-F]
INT_SPEC			(u|U|l|L)
FLOAT_SPEC			(f|F|l|L)
EXP					(e|E)[+-]?{N10}+
ALPHA				[a-zA-Z\_]
		
WS					[ \t\v\n\f\r]
CHAR 				(\\(b|t|n|r|\"|\'|\\|u{N16}{4}|{N8}{1,3})|[^\\\"\n])
STRING_LITERAL		\"{CHAR}*\"
JAVA_COMMENT		(\/\/[^\n]*\n)|(\/\*([^\/]|[^\*]\/)*\*\/)

%%

{JAVA_COMMENT}		{ }

{N8}+{INT_SPEC}*						{ yylval.val_constant = insert_constant_long(atoll(yytext)); return CONSTANT; } /* LITERALS */
{N10}+{EXP}?{INT_SPEC}*					{ yylval.val_constant = insert_constant_long(atoll(yytext)); return CONSTANT; }
0(x|X){N16}+{INT_SPEC}*					{ yylval.val_constant = insert_constant_long(atoll(yytext)); return CONSTANT; }

{N10}*"."{N10}+{EXP}?{FLOAT_SPEC}*		{ yylval.val_constant = insert_constant_double(strtod(yytext, NULL)); return CONSTANT; }

\'{CHAR}\'								{ yylval.val_constant = insert_constant_char(yytext[0]); return CONSTANT; }
{STRING_LITERAL}						{ yylval.val_constant = insert_constant_string(yytext); return CONSTANT; }

"true"									{ yylval.val_constant = insert_constant_bool(true); return CONSTANT; }
"false"									{ yylval.val_constant = insert_constant_bool(false); return CONSTANT; }

"boolean"				{ return BOOL; } /* KEYWORDS */
"break"					{ return BREAK; } /* WHAT-TO-DO-ABOUT: catch, enum, finally, import, protected, throw, throws, try */
"byte"					{ return BYTE; }
"case"					{ return CASE; }
"char"					{ return CHAR; }
"class"					{ return CLASS; }
"continue"				{ return CONTINUE; }
"default"				{ return DEFAULT; }
"do"					{ return DO; }
"double"				{ return DOUBLE; }
"else"					{ return ELSE; }
"final"					{ return FINAL; }
"float"					{ return FLOAT; }
"for"					{ return FOR; }
"if"					{ return IF; }
"int"					{ return INT; }
"long"					{ return LONG; }
"new"					{ return NEW; }
"private"				{ return PRIVATE; }
"public"				{ return PUBLIC; }
"return"				{ return RETURN; }
"short"					{ return SHORT; }
"static"				{ return STATIC; }
"switch"				{ return SWITCH; }
"void"					{ return VOID; }
"while"					{ return WHILE; }

{ALPHA}({ALPHA}|{N10})* { yylval.val_id = insert_id(yytext); return ID; } /* IDENTIFIERS */

"System"{WS}*"."{WS}*"out"{WS}*"."{WS}*"println" { return SYSOUT; }

">>="			{ return SHIFT_R_ASSIGN;} /* OPERATORS */
"<<="			{ return SHIFT_L_ASSIGN; }
"+="			{ return ADD_ASSIGN; }
"-="			{ return SUB_ASSIGN; }
"*="			{ return MUL_ASSIGN; }
"/="			{ return DIV_ASSIGN; }
"%="			{ return MOD_ASSIGN; }
"&="			{ return AND_ASSIGN; }
"^="			{ return XOR_ASSIGN; }
"|="			{ return OR_ASSIGN; }
">>"			{ return SHIFT_R; }
"<<"			{ return SHIFT_L; }
"++"			{ return INC_OP; }
"--"			{ return DEC_OP; }
"&&"			{ return AND_OP; }
"||"			{ return OR_OP; }
"<="			{ return LE_OP; }
">="			{ return GE_OP; }
"==="			{ return EQ3_OP; }
"!=="			{ return NE3_OP; }
"=="			{ return EQ_OP; }
"!="			{ return NE_OP; }


";"				{ return ';'; }
"{"				{ return '{'; }
"}"				{ return '}'; }
","				{ return ','; }
":"				{ return ':'; }
"="				{ return '='; }
"("				{ return '('; }
")"				{ return ')'; }
"["				{ return '['; }
"]"				{ return ']'; }
"."				{ return '.'; }
"&"				{ return '&'; }
"!"				{ return '!'; }
"~"				{ return '~'; }
"-"				{ return '-'; }
"+"				{ return '+'; }
"*"				{ return '*'; }
"/"				{ return '/'; }
"%"				{ return '%'; }
"<"				{ return '<'; }
">"				{ return '>'; }
"^"				{ return '^'; }
"|"				{ return '|'; }
"?"				{ return '?'; }

<<EOF>>			{ return END; }
 
{WS}			{ /* remove whitespace */}
.				{ return yytext[0]; } /* bad chars */

%%
int yywrap()
{
	return 1;
}
