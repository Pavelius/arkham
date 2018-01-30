#include "main.h"

static struct stat_i {
	const char*			id;
	const char*			name;
} stat_data[] = {{"Speed", "��������"},
{"Sneack", "����������"},
{"Fight", "��������"},
{"Will", "����"},
{"Lore", "������"},
{"Luck", "�����"},
//
{"Sanity", "��������"},
{"Stamina", "�����"},
{"Clue", "�����"},
{"Money", "������"},
// Special damage
{"Stamina Maximum", "�������� �����"},
{"Sanity Maximum", "�������� ��������"},
// Special checks
{"Combat Check", "������ ������"},
{"Evade Check", "������ ���������"},
{"Horror Check", "������ �����"},
{"Skill Check", "������ ������ ������"},
{"Spell Check", "������ ����������"},
// Calculated values
{"Movement", "��������"},
{"Test One Die"},
{"Test Two Die"},
};
assert_enum(stat, TestTwoDie);
getstr_enum(stat);