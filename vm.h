/// @file
/// @brief Configuration here

#ifndef _H_CVM
#define _H_CVM

/// @defgroup config Configuration
/// @{

#ifndef Msz
/// main memory size, default 64K
#define Msz 0x10000
#endif

#ifndef Dsz
/// data stack size, default 4K
#define Dsz 0x1000
#endif

/// @}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

/// @defgroup vm Virtual Machine
/// @{

/// main memory image (byte-level addressed)
extern uint8_t M[Msz];
/// instruction pointer
extern uint32_t Ip;
/// stack pointer
extern uint32_t Sp;
/// stack frame pointer
extern uint32_t Fp;

/// @brief store 32-bit cell to memory (litle endian)
/// @param[in] addr address
/// @param[in] data cell to be stored
extern void M32set(uint32_t addr, uint32_t data);

/// byte-code interpreter
extern void bc_interpret();

/// @brief emulator entry point
/// @param[in] argc numbers of arguments 1+
/// @param[in] argv program arguments
/// - `argv[0]` full path of program executable file
extern int main(int argc, char *argv[]);

/// @}

/// @defgroup compiler Compiler
/// @{

/// compilation pointer
extern uint32_t Cp;

/// @brief compile byte
/// @param[in] opcode
extern void C8(uint8_t opcode);
/// @brief compile 32-bit cell
/// @param[in] cell
extern void C32(uint32_t cell);

/// @}

/// @defgroup debug Debugger
/// @{

/// @brief dump memory
/// @param[in] addr start sddress
/// @param[in] len region size, bytes
extern void dump(uint32_t addr, uint32_t len);

/// @}

/// @defgroup opcode Command set opcodes
/// @{

/// `NOP/0` do nothing
#define NOP		0x00
/// `NOP/0` do nothing
extern void nop();

/// `HALT/0` stop system
#define HALT	0xFF
/// `HALT/0` stop system
extern void halt();

/// @defgroup cflow Control Flow
/// @{

/// `JMP/1` unconditional jump
#define JMP		0x01

/// `?JMP/1` conditional jmp if false
#define qJMP	0x02

/// `CALL/1` nested call
#define CALL	0x03

/// `RET/0` return from nested call
#define RET		0x04

/// @}

/// @}

/// @defgroup compiler Compiler
/// @{

/// @defgroup sym Symbol table
/// @{

/// symbol table element
typedef struct {
	/// linked list pointer
	struct Sym* next;
	/// stored id
	char *name;
	/// allocated addr/-1
	uint32_t addr;
} SYM;

/// symbol table
extern SYM *symtable;

/// @brief dump symbol table
extern void sym_dump();

/// @brief get addr from symbol table
/// @param[in] name label
/// @returns address in target memory or -1
extern uint32_t symget(char* name);

/// @brief set address in symbol table
/// @param[in] name label
/// @param[in] addr binded
extern void symset(char* name, uint32_t addr);

/// @}

/// @defgroup parser lexer/parser interface
/// @details flex/bison powered
/// @{

/// @brief lexer: fetch next token
/// @returns next token from source code:
/// `int` token code and extra data in `yylval` structure
extern int yylex();

/// @brief current line number for syntax reports
extern int yylineno;

/// @brief last **lexeme** was parsed by lexer
extern char* yytext;

/// @brief syntax parser
extern int yyparse();

/// @brief syntax error callback
/// @param[in] msg message to be displayed in error report
extern void yyerror(char* msg);

#include "parser.tab.h"
/// @}

/// @}

#endif // _H_CVM
