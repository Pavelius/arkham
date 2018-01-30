#include "main.h"

char hero::get(stat_s id) const {
	return stats[id] + focus[id / 2];
}