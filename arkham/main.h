#include "adat.h"
#include "aref.h"
#include "crt.h"
#include "grammar.h"
#include "logs.h"
#include "stringcreator.h"

#pragma once

enum stat_s : unsigned char {
	Speed, Sneack, Fight, Will, Lore, Luck,
	Sanity, Stamina,
	Clue, Money,
	LastStat = Money,
};
enum tid_s : unsigned char {
	Actions, Allies, Stats, Skills, Spells, Items,
};
enum gender_s : unsigned char {
	Male, Female,
};
enum action_s : unsigned char {
	NoAction,
	AddClue, AddCommonItem, AddMoney, AddSanity, AddSkill, AddSpell, AddStamina, AddUniqueItem,
	LoseClue, LoseItem, LoseSanity, LoseStamina,
	PayCommonItem, PayUniqueItem
};
enum number_s : unsigned char {
	All = 32, Half, OneDice, TwoDice,
};
enum location_s : unsigned char {
	AdministrationBuilding, ArkhamAsylum, RiverDocks, TrainStation, Woods
};
enum ally_s : unsigned char {
	AllyDuke,
};
enum item_s : unsigned char {
	NoItem,
	PistolDerringer18, PistolRevolver38, PistolAutomatic45,
	AncientTome, Axe, Bullwhip, CavalrySaber, Cross, DarkCloak, Dynamite, Food, Knife,
	Lantern, LuckyCigaretteCase, MapOfArkham, Motorcycle, OldJournal, ResearchMaterials, Rifle,
	Shotgun, TommyGun, Whiskey
};
enum skill_s : unsigned char {
	SkillBarvery, SkillExpertOccultist,
	SkillFight, SkillLore, SkillLuck, SkillMarksman,
	SkillSneak, SkillSpeed, SkillStealth, SkillWill
};
enum spell_s : unsigned char {
	BindMonster, DreadCurseOfAzathoth, EnchantWeapon, FindGate,
	FleshWard, Heal, MistOfReleh, RedSignOfShuddleMell,
	Shrivelling, VoiceOfRa, Wither,
};
enum special_s : unsigned char {
	Scrounge,
};
struct item {
	constexpr item() : type(NoItem), marker(0) {}
	constexpr item(item_s type) : type(type), marker(0) {}
	item_s			type;
	char			marker;
};
struct tid {
	tid_s			type;
	unsigned char	value;
	constexpr tid() : type(Actions), value(NoAction) {}
	constexpr tid(ally_s v) : type(Allies), value(v) {}
	constexpr tid(item_s v) : type(Items), value(v) {}
	constexpr tid(stat_s v) : type(Stats), value(v) {}
	constexpr tid(spell_s v) : type(Spells), value(v) {}
	constexpr tid(tid_s type, unsigned char v) : type(type), value(v) {}
	constexpr tid(int v) : type(tid_s(v >> 8)), value(v & 0xFF) {}
	constexpr operator unsigned short() const { return ((type << 8) | (value)); }
};
struct quest {
	struct outcome {
		operator bool() const { return result != 0; }
		tid			result;
		short		value;
	};
	struct action {
		operator bool() const { return text != 0; }
		const char*	text;
		outcome		results[4];
	};
	struct roll_i {
		tid			action;
		char		bonus;
		char		difficult;
		bool		optional;
	};
	location_s		type;
	const char*		text;
	roll_i			roll;
	action			results[4];
	operator bool() const { return text != 0; }
};
struct hero {
	operator bool() const { return name != 0; }
	void			act(const char* format, ...) const;
	void			add(item_s e);
	void			apply(tid id, int value);
	void			clear();
	void			create(const char* id);
	gender_s		getgender() const { return gender; }
	const char*		getname() const { return name; }
	char			get(stat_s id) const;
	char			getcount(stat_s id, int value) const;
	location_s		getlocation() const { return location; }
	special_s		getspecial() const { return special; }
	void			remove(item_s e);
	void			run(quest& e);
	void			set(location_s v) { location = v; }
	void			set(special_s id) { special = id; }
	void			set(stat_s id, int v) { stats[id] = v; }
	void			setname(const char* v) { name = v; }
private:
	const char*		name;
	gender_s		gender;
	location_s		location;
	special_s		special;
	char			stats[LastStat + 1];
	char			focus[3];
	item			possession[16];
};
namespace logs {
struct driver : stringcreator {
	gender_s		gender;
	const char*		name;
	const char*		opponent_name;
	gender_s		opponent_gender;
	constexpr driver() : gender(), name(), opponent_name(), opponent_gender() {}
	void			parseidentifier(char* result, const char* result_max, const char* identifier) override;
};
}
extern hero					player;
extern adat<item_s, 128>	common_items;
extern adat<item_s, 128>	unique_items;