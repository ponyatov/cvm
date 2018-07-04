%{
#include "vm.h"
%}

%option noyywrap yylineno

%%
#[^\n]*		{}												// line comment
[ \t\r\n]+	{}												// drop spaces
.			{ yyerror("lexer error: undefined char"); }		// unlexed char
%%
