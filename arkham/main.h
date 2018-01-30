#pragma once

enum stat_s : unsigned char { Fight, Will, Speed, Stealth, Lore, Luck };
enum tid_s : unsigned char {
	Actions, Stats, Skills, Spells,
};
enum action_s : unsigned char {
	NoAction,
	AddCommonItem, AddUniqueItem, AddSpell, AddSkill, AddClue,
	LoseClue, LoseHealth, LoseSanity, LoseItem,
	PayCommonItem, PayUniqueItem
};
enum number_s : unsigned char {
	All = 32, Half,
};
enum location_s : unsigned char {
	AdministrationBuilding, ArkhamAsylum, TrainStation, Woods
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
struct tid {
	tid_s			type;
	unsigned char	value;
	constexpr tid() : type(Actions), value(NoAction) {}
	constexpr tid(stat_s v) : type(Stats), value(v) {}
	constexpr tid(spell_s v) : type(Spells), value(v) {}
	constexpr tid(tid_s type, unsigned char v) : type(type), value(v) {}
	constexpr tid(int v) : type(tid_s(v >> 8)), value(v & 0xFF) {}
	constexpr operator unsigned short() const { return ((type << 8) | (value)); }
};
struct quest {
	struct outcome {
		tid			result;
		short		value;
	};
	struct action {
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
};
struct hero {
	operator bool() const { return name != 0; }
	const char*		getname() const { return name; }
	char			get(stat_s id) const;
	void			run(quest& e);
	void			set(stat_s id, int v) { stats[id] = v; }
private:
	const char*		name;
	char			stats[Luck + 1];
	char			focus[(sizeof(hero::stats)/ sizeof(hero::stats[0]))/2];
};
extern hero			players[4];