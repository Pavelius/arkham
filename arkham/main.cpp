#include "main.h"

void test_main() {
	deck::getdeck(CommonItem).create(CommonItem);
	deck::getdeck(UniqueItem).create(UniqueItem);
	player.create("ashcan");
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