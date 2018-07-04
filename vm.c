#include "vm.h"

int main(int argc, char *argv[]) {
	printf("argv: ", argv[0]);
	for (int i = 0; i < argc; i++) printf("%s ", argv[i]);
	printf("\n\n");
}
