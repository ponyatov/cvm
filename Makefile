all: ./vm.exe
	./vm.exe

C = vm.c
H = vm.h

./vm.exe: $(C) $(H)
	$(CC) -o $@ $(C)