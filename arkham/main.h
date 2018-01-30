#include "adat.h"
#include "aref.h"
#include "crt.h"
#include "grammar.h"
#include "initializer_list.h"
#include "logs.h"
#include "stringcreator.h"

#pragma once

enum stat_s : unsigned char {
	Speed, Sneack, Fight, Will, Lore, Luck,
	Sanity, Stamina,
	Clue, Money,
	// Special damage
	StaminaMaximum, SanityMaximum,
	// Special checks
	CombatCheck, EvadeCheck, HorrorCheck, SkillCheck, SpellCheck,
	// Calculated values
	Movement, TestOneDie, TestTwoDie,
};
enum gender_s : unsigned char {
	Male, Female,
};
enum item_group_s : unsigned char {
	CommonItem, UniqueItem, Spell,
};
enum action_s : unsigned char {
	NoAction,
	AddClue, AddCommonItem, AddMoney, AddSanity, AddSkill, AddSpell, AddStamina, AddUniqueItem,
	LoseClue, LoseItem, LoseSanity, LoseStamina,
	PayCommonItem, PayUniqueItem,
	Discard
};
enum number_s : unsigned char {
	One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
	All, Half, OneDice, TwoDice,
};
enum location_s : unsigned char {
	AnyLocation,
	AdministrationBuilding, ArkhamAsylum, RiverDocks, TrainStation, Woods
};
enum tag_s : unsigned char {
	Tome, PhysicalWeapon, MagicalWeapon,
	CantStealOrLoose, CombatBonusTwoHand, ExhaustToRerollDie, ExhaustToEffect,
	CombatBonusVsUndead, DiscardAfterUse, SixDoubleSuccess, MarkTokenToDiscard
};
enum item_s : unsigned char {
	NoItem,
	// Common items
	PistolDerringer18, PistolRevolver38, PistolAutomatic45,
	AncientTome, Axe, Bullwhip, CavalrySaber, Cross, DarkCloak, Dynamite, Food, Knife,
	Lantern, LuckyCigaretteCase, MapOfArkham, Motorcycle, OldJournal, ResearchMaterials, Rifle,
	Shotgun, TommyGun, Whiskey,
	// Unique items
	AlienStatue, AncientTablet, AstralMirror, BlueWatcherOfThePyramid, CamillasRuby,
	CarcosanPage, CryptozoologyCollection, CrystalOfTheElderThings, DragonsEye,
	ElderSign, EnchantedBlade, EnchantedJewelry, EnchantedKnife, FluteOfTheOuterGods,
	GateBox, HealingStone, HolyWater, LampOfAlhazred, NamelessCults,
	Necronomicon, ObsidianStatue, PallidMask, PowderOfIbnGhazi, RubyOfRlyeh,
	SilverKey, SwordOfGlory, TheKingInYellow, WardingStatue,
	// Spells
	BindMonster, DreadCurseOfAzathoth, EnchantWeapon, FindGate,
	FleshWard, Heal, MistOfReleh, RedSignOfShuddleMell,
	Shrivelling, VoiceOfRa, Wither,
	// Skills
	SkillBarvery, SkillExpertOccultist,
	SkillFight, SkillLore, SkillLuck, SkillMarksman,
	SkillSneak, SkillSpeed, SkillStealth, SkillWill,
	//
	AllyDuke,
};
enum tid_s : unsigned char {
	Actions, Stats, Items,
};
enum special_s : unsigned char {
	Scrounge,
};
template<typename T>
struct cflags {
	constexpr cflags() : data() {}
	constexpr cflags(const std::initializer_list<T> list) : data(gen(0, list.begin(), list.end())) {}
	bool		is(T id) const { return (data & (1 << id)) != 0; }
	void		remove(T id) { data &= ~(1 << id); }
	void		set(T id) { data |= (1 << id); }
private:
	unsigned	data;
	static constexpr unsigned gen(unsigned r, const T* ps, const T* pe) {
		return (ps < pe) ? gen(r | (1 << (*ps)), ps + 1, pe) : r;
	}
};
struct item {
	item() = default;
	constexpr item(item_s type) : type(type), exhause(0), magic(0), marker(0) {}
	bool operator==(item_s v) const { return type == v; }
	operator bool() const { return type!=0; }
private:
	item_s			type;
	unsigned char	exhause : 1;
	unsigned char	magic : 1;
	unsigned char	marker : 3;
};
struct tid {
	tid_s			type;
	unsigned char	value;
	constexpr tid() : type(Actions), value(NoAction) {}
	constexpr tid(item_s v) : type(Items), value(v) {}
	constexpr tid(stat_s v) : type(Stats), value(v) {}
	constexpr tid(tid_s type, unsigned char v) : type(type), value(v) {}
	constexpr tid(int v) : type(tid_s(v >> 8)), value(v & 0xFF) {}
	constexpr operator unsigned short() const { return ((type << 8) | (value)); }
};
struct quest {
	struct outcome {
		operator bool() const { return result != 0; }
		tid			result;
		number_s	count;
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
	bool			add(item_s e);
	void			apply(tid id, number_s value);
	void			clear();
	void			create(const char* id);
	gender_s		getgender() const { return gender; }
	const char*		getname() const { return name; }
	char			get(stat_s id) const;
	char			getcount(stat_s id, number_s value) const;
	location_s		getlocation() const { return location; }
	special_s		getspecial() const { return special; }
	bool			is(item_s e) const;
	void			remove(item_s e);
	int				roll(stat_s id, int bonus = 0, int difficult = 0, bool interactive = true);
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
	char			stats[Money + 1];
	char			focus[3];
	item			weapon[2], possession[24];
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