#include "main.h"

enum myth_type_s : unsigned char {
	EnvironmentMystic, EnvironmentUrban, EnvironmentWeather,
	Headline, Rumor,
};

struct myth_i {
	const char*		id;
	const char*		name;
	myth_type_s		type;
	location_s		position;
} myth_data[] = {{"A Strange Plague", "", EnvironmentMystic, IndependenceSquare},
{"Alien Technology", "", EnvironmentUrban, UnvisitedIsle},
{"All Quiet in Arkham!", "", Headline, Woods},
{"An Evil Fog", "", EnvironmentWeather, Graveyard},
};