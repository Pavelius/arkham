#include "main.h"

static quest ancient_tome = {AnyLocation, "����������� ������� ������� ���.", {Lore, -1}, {
	{"������ ������ ��� ���� �� �� ����������."},
	{"�� ������� ������� ��������� ������.", {AddSpell, Discard}},
}};
static quest old_journal = {AnyLocation, "������� ���������� ������� �������.", {Lore, -1}, {
	{"������ ������ ��� ���� �� �� ����������."},
	{"� ������ ������� ����������� ������ � �������� ������ � ������� ������ � �������.", {Add3Clue, Discard}},
}};
static constexpr const struct item_i {
	struct effect_i {
		stat_s		id;
		char		count;
	};
	struct tome_i {
		char		movement; // Lose this count of movement to do this
		char		sanity; // Lose this count of sanity to do this
		quest*		script;
		char		usable; // This is maximum use count
	};
	const char*		id;
	const char*		name;
	stat_s			type;
	char			deck_count;
	char			cost;
	char			hands;
	effect_i		bonus;
	tome_i			tome;
	cflags<tag_s>	tags;
} item_data[] = {
	{"", ""},
	// Common items
	{".18 Derringer", ".18 ���������", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon, CantStealOrLoose}},
	{".38 Revolver", ".38 ���������", CommonItem, 2, 4, 1, {CombatCheck, 3}, {}, {PhysicalWeapon}},
	{".45 Automatic", ".45 �����", CommonItem, 2, 4, 1, {CombatCheck, 4}, {}, {PhysicalWeapon}},
	{"Ancient Tome", "������� �����", CommonItem, 2, 4, 0, {}, {2, 0, &ancient_tome}, {ExhaustToEffect, Tome}},
	{"Axe", "�����", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon, CombatBonusTwoHand}},
	{"Bullwhip", "����", CommonItem, 2, 2, 1, {CombatCheck, 1}, {}, {PhysicalWeapon, ExhaustToRerollDie}},
	{"Cavalry Saber", "������������ �����", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon}},
	{"Cross", "�����", CommonItem, 2, 3, 1, {HorrorCheck, 1}, {}, {MagicalWeapon, CombatBonusVsUndead}},
	{"Dark Cloak", "������ ����", CommonItem, 2, 2, 0, {EvadeCheck, 1}},
	{"Dynamite", "�������", CommonItem, 2, 2, 2, {CombatCheck, 8}, {}, {PhysicalWeapon, DiscardAfterUse}},
	{"Food", "���", CommonItem, 2, 1, 0, {Stamina, 1}, {}, {DiscardAfterUse}},
	{"Knife", "���", CommonItem, 2, 2, 1, {CombatCheck, 3}, {}, {PhysicalWeapon}},
	{"Lantern", "������", CommonItem, 2, 2, 0, {Luck}, {}, {ExhaustToRerollDie}},
	{"Lucky Cigarette Case", "��������� ���������", CommonItem, 2, 2, 0, {SkillCheck}, {}, {ExhaustToRerollDie, DiscardAfterUse}},
	{"Map of Arkham", "����� �������", CommonItem, 2, 2, 0, {Movement, 1}, {}, {ExhaustToEffect}},
	{"Motorcycle", "��������", CommonItem, 2, 4, 0, {Movement, 2}, {}, {ExhaustToEffect}},
	{"Old Journal", "������ ������", CommonItem, 2, 1, 0, {}, {1, 0, &old_journal}, {ExhaustToEffect, Tome}},
	{"Research Materials", "����������������� ���������", CommonItem, 2, 1, 0, {Clue, 1}, {}, {DiscardAfterUse}},
	{"Rifle", "�����", CommonItem, 2, 6, 2, {CombatCheck, 5}, {}, {PhysicalWeapon}},
	{"Shotgun", "��������", CommonItem, 2, 6, 2, {CombatCheck, 4}, {}, {PhysicalWeapon, SixDoubleSuccess}},
	{"Tommy Gun", "�������", CommonItem, 2, 7, 2, {CombatCheck, 6}, {}, {PhysicalWeapon}},
	{"Whiskey", "�����", CommonItem, 2, 1, 0, {Sanity, 1}, {}, {DiscardAfterUse}},
};
assert_enum(item, Whiskey);
getstr_enum(item);

void deck::create(stat_s group) {
	clear();
	for(auto& e : item_data) {
		if(e.type != group)
			continue;
		auto id = item_s(&e - item_data);
		for(auto i = 0; i < e.deck_count; i++)
			add(id);
	}
	zshuffle(data, count);
}

stat_s item::getgroup(item_s id) {
	return item_data[id].type;
}

void item::clear() {
	memset(this, 0, sizeof(*this));
}