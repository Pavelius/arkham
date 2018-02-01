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

bool hero::combat(monster& e) {
	if(!isready())
		return false;
	logs::add("�������� �������� %1.", e.getname());
	if(logs::yesno(true, "������ ���������� ������?")) {
		if(evade(e)) {
			logs::add("������� ������ �������.");
			return true;
		}
	}
	if(!isready())
		return false;
	if(e.get(Sanity) && !roll(HorrorCheck, e.get(HorrorCheck), 1))
		add(Sanity, e.get(Sanity));
	if(!e.get(Stamina))
		return true;
	while(isready()) {
		if(roll(CombatCheck, e.get(CombatCheck), e.get(Fight))) {
			logs::add("�� ������ �������� �������.");
			return true;
		}
		add(Stamina, e.get(Stamina));
	}
	return false;
}