%{
#include "vm.h"
%}

%defines %union { uint8_t op; }

%token <op> CMD0

%%
REPL : | REPL CMD0 ;
%%
