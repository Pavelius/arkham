#include "main.h"

bool hero::evade(monster& e) {
	if(!isready())
		return false;
	if(!roll(EvadeCheck, e.get(EvadeCheck))) {
		add(Stamina, e.get(Stamina));
		return false;
	}
	return true;
}

void hero::changeweapon(item_s& w1, item_s& w2) {
	for(item_s i = PistolDerringer18; i <= Whiskey; i = (item_s)(i + 1)) {
		if(!get(i))
			continue;
		if(item::is(i, PhysicalWeapon) || item::is(i, MagicalWeapon))
			logs::add(i, getstr(i));
	}
	w1 = (item_s)logs::input(true, false, "Какое оружие выберете?");
}

bool hero::combat(monster& e) {
	if(!isready())
		return false;
	logs::add("Внезапно появился %1.", e.getname());
	if(logs::yesno(true, "Хотите попроывать бежать?")) {
		if(evade(e)) {
			logs::add("Попытка побега удалась.");
			return true;
		}
	}
	if(!isready())
		return false;
	if(e.get(Sanity) && !roll(HorrorCheck, e.get(HorrorCheck), 1))
		add(Sanity, e.get(Sanity));
	if(!e.get(Stamina))
		return true;
	item_s w1 = NoItem;
	item_s w2 = NoItem;
	while(isready()) {
		changeweapon(w1, w2);
		auto bonus = e.get(Fight);
		bonus += item::get(w1, CombatCheck);
		bonus += item::get(w2, CombatCheck);
		if(roll(CombatCheck, e.get(CombatCheck), bonus)) {
			logs::add("Вы сумели победить монстра.");
			return true;
		}
		add(Stamina, e.get(Stamina));
	}
	return false;
}