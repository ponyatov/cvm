all: ./vm.exe
	./vm.exe < demo.script

C = vm.c
H = vm.h

./vm.exe: $(C) $(H)
	$(CC) -o $@ $(C)
	
doxy:
	rm -rf docs ; doxygen doxy.gen
