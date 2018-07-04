%{
#include "vm.h"
														// return tokens
#define C0(OP) { yylval.op = OP; return CMD0; }
#define C1(OP) { yylval.op = OP; return CMD1; }
%}

%option noyywrap yylineno

id	[a-zA-Z_][a-zA-Z0-9_]*
num	[0-9]+

%%
#[^\n]*		{}											// line comment

nop			C0(NOP)										// \ commands
halt		C0(HALT)

jmp			C1(JMP)
\?jmp		C1(qJMP)
call		C1(CALL)
ret			C1(RET)
														/* .directives */
".dump"		{ dump(0,Cp); sym_dump(); }					// dump memory & symbols
".go"		{ bc_interpret(); }							// go VM

{id}\:		{ return LABEL; }
{id}		{ return ID;    } 

[ \t\r\n]+	{}											// drop spaces
.			{ yyerror("lexer error: undefined char"); } // unlexed char
%%
