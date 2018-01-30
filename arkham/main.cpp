#include "main.h"

void test_main() {
	player.create("ashcan");
	player.roll(Sneack);
}

int main() {
	//srand(clock());
	srand(100);
	logs::open("Arkham horror");
	test_main();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}