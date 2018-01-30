#include "main.h"

static struct stat_i {
	const char*			id;
	const char*			name;
} stat_data[] = {{"Speed", "Скорость"},
{"Sneack", "Скрытность"},
{"Fight", "Сражение"},
{"Will", "Воля"},
{"Lore", "Знания"},
{"Luck", "Удача"},
//
{"Sanity", "Рассудок"},
{"Stamina", "Жизнь"},
{"Clue", "Улика"},
{"Money", "Деньги"},
// Special damage
{"Stamina Maximum", "Максимум жизни"},
{"Sanity Maximum", "Рассудок максимум"},
// Special checks
{"Combat Check", "Боевой бросок"},
{"Evade Check", "Бросок уклонения"},
{"Horror Check", "Бросок ужаса"},
{"Skill Check", "Бросок любого навыка"},
{"Spell Check", "Бросок заклинаний"},
// Calculated values
{"Movement", "Движение"},
{"Test One Die"},
{"Test Two Die"},
};
assert_enum(stat, TestTwoDie);
getstr_enum(stat);