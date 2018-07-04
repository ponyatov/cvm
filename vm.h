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

/// main memory image
extern uint8_t M[Msz];
/// instruction pointer
extern uint32_t Ip;
/// stack pointer
extern uint32_t Sp;
/// stack frame pointer
extern uint32_t Fp;

/// byte-code interpreter
extern void bc_interpret();

/// @defgroup opcode Command set opcodes
/// @{

/// `NOP` do nothing
#define NOP		0x00
/// `HALT` stop system
#define HALT	0xFF

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
/// @}

#endif // _H_CVM
