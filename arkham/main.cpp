#include "main.h"

void test_main() {
	deck::initialize();
	player.create("joe");
	player.roll(Sneak);
}

int main() {
	//srand(clock());
	srand(120);
	logs::open("Arkham horror");
	test_main();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}