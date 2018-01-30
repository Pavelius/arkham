#include "main.h"

static stat_s getstat(tid id) {
	if(id.type == Actions) {
		switch(id.value) {
		case AddClue: return Clue;
		case AddMoney: return Money;
		}
	}
	return Speed;
}

char hero::getcount(stat_s id, number_s value) const {
	switch(value) {
	case Half: return get(id) / 2;
	case All: return get(id);
	case OneDice: return 1 + rand() % 6;
	case TwoDice: return 2 + rand() % 6 + rand() % 6;
	default: return 1 + (value - One);
	}
}

void hero::apply(tid id, number_s count) {
	stat_s stat;
	char value;
	if(!id)
		return;
	switch(id.type) {
	case Actions:
		switch(id.value) {
		case AddClue:
		case AddMoney:
			stat = getstat(id);
			value = getcount(stat, count);
			set(stat, get(stat) + value);
			break;
		case LoseClue:
		case LoseSanity:
		case LoseStamina:
			stat = getstat(id);
			value = getcount(stat, count);
			set(stat, get(stat) - value);
			break;
		}
		break;
	case Items: add((item_s)id.value); break;
	}
}