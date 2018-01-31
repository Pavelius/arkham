#include "main.h"

void item::clear() {
	memset(this, 0, sizeof(*this));
}
