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

char hero::getcount(stat_s id, int value) const {
	switch(value) {
	case Half: return get(id) / 2;
	case All: return get(id);
	case OneDice: return 1 + rand() % 6;
	case TwoDice: return 2 + rand() % 6 + rand() % 6;
	case 0: return 1;
	default: return value;
	}
}

void hero::apply(tid id, int value) {
	stat_s stat;
	char count;
	if(!id)
		return;
	switch(id.type) {
	case Actions:
		switch(id.value) {
		case AddClue:
		case AddMoney:
			stat = getstat(id);
			count = getcount(stat, value);
			set(stat, get(stat) + count);
			break;
		case LoseClue:
		case LoseSanity:
		case LoseStamina:
			stat = getstat(id);
			count = -getcount(stat, value);
			set(stat, get(stat) + count);
			break;
		}
		break;
	}
}