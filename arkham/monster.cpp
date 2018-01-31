#include "main.h"

struct monster_i {
	const char*		id;
	const char*		name;
	char			count;
	char			awareness;
	char			horror[2];
	char			toughness;
	char			combat[2];
	cflags<mflag_s>	flags;
	const char*		text;
} monster_data[] = {{"Byakhee", "Бьякхи"},
{"Chthonian", "Чхониан"},
{"Zombie", "Зобми", 2, 1, {-2, 2}, 3, {-3, 3}},
};
assert_enum(monster, Zombie);
getstr_enum(monster);