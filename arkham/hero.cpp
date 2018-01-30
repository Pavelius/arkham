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
	{"ashcan", "Ашхан \"Пит\"", Scrounge, RiverDocks, 4, 6, {0, 6, 2, 5, 0, 3}, {{AddMoney, One}, {AddClue, Three}, {AllyDuke}, {AddCommonItem}, {AddUniqueItem}, {AddSpell}}}
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
	case Sneak:
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
	for(auto& e : p->possessions)
		apply(e.result, e.count);
}

bool hero::is(item_s v) const {
	if(!v)
		return false;
	for(auto e : possession) {
		if(!e)
		if(e.isexhause())
			continue;
		if(e == v)
			return true;
	}
	return false;
}

bool hero::add(item_s v) {
	for(auto& e : possession) {
		if(!e) {
			e = v;
			return true;
		}
	}
	return false;
}

static char* dices(char* result, const char* source) {
	for(auto i = 0; source[i]; i++) {
		if(i)
			zcat(result, ", ");
		szprint(zend(result), "%1i", source[i]);
	}
	return result;
}

int getresult(const char* result, int success_number) {
	auto r = 0;
	for(auto i = 0; result[i] > 0; i++) {
		if(result[i] >= success_number)
			r++;
	}
	return r;
}

static void addie(char* result) {
	zcat(result, (char)(1 + (rand() % 6)));
}

char* getstr(char* result, stat_s id, int bonus) {
	if(bonus > 0)
		return szprint(result, "%1+%2i", getstr(id), bonus);
	else if(bonus < 0)
		return szprint(result, "%1-%2i", getstr(id), -bonus);
	else
		return szprint(result, "%1", getstr(id));
}

item_s getskill(stat_s id) {
	switch(id) {
	case Fight: return SkillFight;
	case Will: return SkillWill;
	case Speed: return SkillSpeed;
	case Sneak: return SkillSneak;
	case Lore: return SkillLore;
	case Luck: return SkillLuck;
	default: return NoItem;
	}
}

int hero::roll(stat_s id, int bonus, int difficult, bool interactive) {
	int i;
	char result[32]; result[0] = 0; char temp[128];
	auto skill = getskill(id);
	if(is(skill))
		bonus++;
	auto count = get(id) + bonus;
	auto success = 0;
	auto success_number = 5;
	auto ps = logs::getptr();
	for(auto i = 0; i < count; i++)
		addie(result);
	while(true) {
		if(result[0]) {
			szprint(ps, "Вы сделали бросок [%1] и выбросили: ", getstr(temp, id, bonus));
			dices(zend(ps), result);
			zcat(ps, ". ");
		} else {
			szprint(ps, "У вас недостаточно кубиков для броска.");
		}
		auto rn = getresult(result, success_number);
		if(success >= difficult)
			logs::add(1, "Принять результат с [%1i] успехами.", rn);
		else
			logs::add(1, "Принять провал.");
		if(get(Clue))
			logs::add(2, "Потратить улику, чтобы добавить к броску 1 кубик (осталось [%1i] улик).", get(Clue));
		auto id = logs::input(interactive, false, "Что будете делать?");
		switch(id) {
		case 1:
			return success - difficult;
		case 2:
			addie(result);
			if(is(skill))
				addie(result);
			add(Clue, -1);
			break;
		case 3:
			i = zlen(result); result[0] = 0;
			while(i-->0)
				addie(result);
			break;
		}
	}
}