/// @file

#include "vm.h"

uint8_t  M[Msz];
uint32_t Ip =0;
uint32_t Sp =0;
uint32_t Fp =0;
uint32_t Cp =0;

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
		case NOP:	nop(); break;
		case HALT:	halt(); break;
		default:
			dump(0,Cp); fflush(stdout);
			fprintf(stderr,"\n\nunknown command %.8X:%.2X\n\n",Ip-1,opcode);
			abort();
	}

}}

void nop()	{}
void halt()	{ exit(0); }

void M32set(uint32_t addr, uint32_t data) {
	M[addr+0] = data >>  0;
	M[addr+1] = data >>  8;
	M[addr+2] = data >> 16;
	M[addr+3] = data >> 24;
}

uint32_t symget(char* name) { return -1; }

void symset(char* name, uint32_t addr) { }

void C8(uint8_t opcode) { M[Cp++] = opcode; assert(Cp < Msz); }
void C32(uint32_t cell) { M32set(Cp,cell); Cp += sizeof(cell); assert(Cp < Msz); }

void dump(uint32_t addr, uint32_t len) {
	for (uint i=addr ; i<addr+len ; i++) {
		if (i%0x10 == 0) printf("\n%.8X:\t",i);
		printf("%.2X ",M[i]);
	}
}

SYM *symtable = NULL;

void sym_dump() {
	printf("\n\nsymbol table:\n\n");
	printf("\n");
}
