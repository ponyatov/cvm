all: ./cvm.exe
	./cvm.exe < demo.script

C = vm.c parser.tab.c lex.yy.c
H = vm.h parser.tab.h

./cvm.exe: $(C) $(H)
	$(CC) -o $@ $(C)
	
lex.yy.c: lexer.lex
	flex $<
parser.tab.c: parser.yacc
	bison -o $@ $<	
		
doxy:
	rm -rf docs ; doxygen doxy.gen 1>/dev/null
