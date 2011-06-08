%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "inc/structures.h"
#include "inc/insert.h"
#include "inc/show.h"
#include "inc/free.h"

#include "y.tab.h"

extern int yyline;
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

{JAVA_COMMENT}		{ int i=0; while (yytext[i]) if (yytext[i++] == '\n') yyline++; }

0{N8}+{INT_SPEC}*						{ if (yytext[strlen(yytext)-1] == 'l' || yytext[strlen(yytext)-1] == 'L') { yylval.val_constant = insert_constant_long(strtoll(yytext, NULL, 8)); } else { yylval.val_constant = insert_constant_int(strtol(yytext, NULL, 8)); } return CONSTANT; } /* LITERALS */
{N10}+{EXP}?{INT_SPEC}*					{ if (yytext[strlen(yytext)-1] == 'l' || yytext[strlen(yytext)-1] == 'L') { yylval.val_constant = insert_constant_long(strtoll(yytext, NULL, 10)); } else { yylval.val_constant = insert_constant_int(strtol(yytext, NULL, 10)); } return CONSTANT;  }
0(x|X){N16}+{INT_SPEC}*					{ if (yytext[strlen(yytext)-1] == 'l' || yytext[strlen(yytext)-1] == 'L') { yylval.val_constant = insert_constant_long(strtoll(yytext, NULL, 16)); } else { yylval.val_constant = insert_constant_int(strtol(yytext, NULL, 16)); } return CONSTANT;  }

{N10}*"."{N10}+{EXP}?{FLOAT_SPEC}*		{ if (yytext[strlen(yytext)-1] == 'f' || yytext[strlen(yytext)-1] == 'F') { yylval.val_constant = insert_constant_float(strtof(yytext, NULL)); } else { yylval.val_constant = insert_constant_double(strtold(yytext, NULL)); } return CONSTANT; }

\'{CHAR}\'								{ yylval.val_constant = insert_constant_char(yytext); return CONSTANT; }
{STRING_LITERAL}						{ yylval.val_constant = insert_constant_string(yytext); return CONSTANT; }

"true"									{ yylval.val_constant = insert_constant_bool(true); return CONSTANT; }
"false"									{ yylval.val_constant = insert_constant_bool(false); return CONSTANT; }

"boolean"				{ return BOOL; } /* KEYWORDS */
"break"					{ return BREAK; } /* WHAT-TO-DO-ABOUT: catch, enum, finally, import, protected, throw, throws, try? */
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
"String"				{ return STRING; }
"switch"				{ return SWITCH; }
"void"					{ return VOID; }
"while"					{ return WHILE; }

{ALPHA}({ALPHA}|{N10})* { yylval.val_id = insert_id(yytext); return ID; } /* IDENTIFIERS */

"System"{WS}*"."{WS}*"out"{WS}*"."{WS}*"println" { yylval.val_id = insert_id("System.out.println"); return ID; } /* TODO: add other bultins (Math.cos) here if wanted */
"System"{WS}*"."{WS}*"in"{WS}*"."{WS}*"nextInt" { yylval.val_id = insert_id("System.in.nextInt"); return ID; } /* TODO: add other bultins (Math.cos) here if wanted */

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

\n				{ yyline++; }
{WS}			{ /* remove whitespace */}
.				{ return yytext[0]; } /* bad chars */

%%
int yywrap()
{
	return 1;
}
