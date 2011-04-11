%{
#include "y.tab.h"
%}

N8					[0-7]
N10					[0-9]
N16					[0-9a-fA-F]
INT_SPEC			(u|U|l|L)
FLOAT_SPEC			(f|F|l|L)
EXP					(e|E)[+-]?{N10}+
ALPHA				[a-zA-Z0-9_]

STRING_LITERAL		\"(\\\\|\\\"|\\(ALPHA)|[^\"\\\n])*\"
JAVA_COMMENT		(\/\/[^\n]*\n))|(\/\*([^\\]|\\[^\*])*\*\/)

%%

{JAVA_COMMENT}		{ }

%{/* LITERALS */}%

[+-]?{N8}+{INT_SPEC}*					{ return CONSTANT; }
[+-]?{N10}+{EXP}?{INT_SPEC}*			{ return CONSTANT; }
0(x|X){N16}+{INT_SPEC}*					{ return CONSTANT; }

[+-]?{N10}*"."{N10}+{EXP}?{FLOAT_SPEC}*	{ return CONSTANT; }


%{/* KEYWORDS */}%
		
"boolean"				{ return BOOL; }
"break"					{ return BREAK; }
"byte"					{ return BYTE; }
"case"					{ return CASE; }
%{/*catch*/}%
"char"					{ return CHAR; }
"class"					{ return CLASS; }
"continue"				{ return CONTINUE; }
"default"				{ return DEFAULT; }
"do"					{ return DO; }
"double"				{ return DOUBLE; }
"else"					{ return ELSE; }
"enum"					{ return ENUM; }
"final"					{ return FINAL; }
%{/*finally*/}%
"float"					{ return FLOAT; }
"for"					{ return FOR; }
"if"					{ return IF; }
%{/*import*/}%
"int"					{ return INT; }
"long"					{ return LONG; }
"new"					{ return NEW; }
"private"				{ return PRIVATE; }
%{/*protected*/}%
"public"				{ return PUBLIC; }
"return"				{ return RETURN; }
"short"					{ return SHORT; }
"static"				{ return STATIC; }
"switch"				{ return SWITCH; }
%{/*throw*/}%
%{/*throws*/}%
%{/*try*/}%
"void"					{ return VOID; }
"while"					{ return WHILE; }

%{/* OPERATORS */}%

%{/*"..."			{ return ELLIPSIS; }*/ %}
">>="			{ return SHIFT_R_ASSIGN; }
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
"=="			{ return EQ_OP; }
"!="			{ return NE_OP; }
"==="			{ return EQ3_OP; }

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

[ \t\v\n\f\r]|.	{ /* remove whitespace */}

%%
int main()
{
	yylex();
	return 0;
}

int yywrap()
{
	return 1;
}
