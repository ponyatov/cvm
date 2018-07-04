%{
#include "vm.h"
%}

%defines %union { uint8_t op; char* id; }

%token <op> CMD0 CMD1
%token <id> ID LABEL

%%
REPL :
	| REPL CMD0		{ C8($2); }
	| REPL CMD1 ID	{ C8($2); C32(symget($3)); }
	| REPL LABEL	{ symset($2,Cp); }
;
%%
