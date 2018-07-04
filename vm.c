/// @file

#include "vm.h"

uint8_t  M[Msz];
uint32_t Ip =0;
uint32_t Sp =0;
uint32_t Fp =0;

int main(int argc, char *argv[]) {
	printf("argv: ", argv[0]);
	for (int i = 0; i < argc; i++) printf("%s ", argv[i]);
	printf("\n\n");
	return yyparse();
}

void yyerror(char* msg) {
	fprintf(stderr,"\n\n%i: %s [%s]\n\n",yylineno,msg,yytext);
	abort();
}

void bc_interpret() { for (;;) {		// infinitive byte-code interpreter loop

	// fetch
	uint8_t opcode = M[Ip++]; assert(Ip < Msz);

	// decode/execute
	switch (opcode) {
		case NOP:
			break;
		case HALT:
			exit(0);
		default:
			fprintf(stderr,"\n\nunknown command %.8X:%.2X\n\n",Ip-1,opcode);
			abort();
	}

}}
