#include "main.h"

hero					player;

static struct hero_i {
	const char*			id;
	const char*			name;
	special_s			special;
	location_s			location;
	char				sanity, stamina;
	char				stats[Luck + 1];
	quest::outcome		possessions[8];
} hero_data[] = {
	{"ashcan", "Àøõàí \"Ïèò\"", Scrounge, RiverDocks, 4, 6, {0, 6, 2, 5, 0, 3}, {{AddMoney, 1}, {AddClue, 3}, {AllyDuke}, {AddCommonItem}, {AddUniqueItem}, {AddSpell}}}
};

static hero_i* find(const char* id) {
	for(auto& e : hero_data) {
		if(strcmp(e.id, id) == 0)
			return &e;
	}
	return 0;
}

char hero::get(stat_s id) const {
	switch(id) {
	case Speed:
	case Fight:
	case Lore:
		return stats[id] + focus[id / 2];
	case Sneack:
	case Will:
	case Luck:
		return stats[id] - focus[id / 2];
	default:
		return stats[id];
	}
}

void hero::clear() {
	memset(this, 0, sizeof(*this));
}

void hero::create(const char* id) {
	clear();
	auto p = find(id);
	if(!p)
		return;
	set(p->special);
	set(p->location);
	setname(p->name);
	for(auto i = Speed; i <= Luck; i = (stat_s)(i + 1))
		set(i, p->stats[i]);
}