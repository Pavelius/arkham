#include "adat.h"
#include "aref.h"
#include "crt.h"
#include "grammar.h"
#include "initializer_list.h"
#include "logs.h"
#include "stringcreator.h"

#pragma once

#define assert_enum(e, last) static_assert(sizeof(e##_data) / sizeof(e##_data[0]) == last + 1, "Invalid count of " #e " elements")
#define getstr_enum(e) template<> const char* getstr<e##_s>(e##_s value) { return e##_data[value].name; }
#define maptbl(t, id) (t[imax((unsigned)0, imin((unsigned)id, (sizeof(t)/sizeof(t[0])-1)))])
#define maprnd(t) t[rand()%(sizeof(t)/sizeof(t[0]))]
#define lenghtof(t) (sizeof(t)/sizeof(t[0]))

enum stat_s : unsigned char {
	Speed, Sneak, Fight, Will, Lore, Luck,
	Sanity, Stamina,
	Clue, Money,
	// Special damage
	StaminaMaximum, SanityMaximum,
	// Special checks
	CombatCheck, EvadeCheck, HorrorCheck, SkillCheck, SpellCheck,
	// Calculated values
	Movement, TestOneDie, TestTwoDie,
	// Item groups
	CommonItem, UniqueItem, Spell, Skill,
};
enum gender_s : unsigned char {
	Male, Female,
};
enum action_s : unsigned char {
	NoAction,
	Add1Clue, Add2Clue, Add3Clue, Add4Clue, Add5Clue,
	Lose1Clue, Lose2Clue, Lose3Clue, Lose4Clue, Lose5Clue,
	Add1Money, Add2Money, Add3Money, Add4Money, Add5Money,
	Lose1Money, Lose2Money, Lose3Money, Lose4Money, Lose5Money,
	Add1Sanity, Add2Sanity, Add3Sanity,
	Lose1Sanity, Lose2Sanity, Lose3Sanity,
	Add1Stamina, Add2Stamina, Add3Stamina,
	Lose1Stamina, Lose2Stamina, Lose3Stamina,
	AddCommonItem,
	AddUniqueItem,
	AddSkill,
	AddSpell,
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
	SkillBarvery, SkillExpertOccultist, SkillMarksman,
	SkillSpeed, SkillSneak, SkillFight, SkillWill, SkillLore, SkillLuck,
	//
	AllyDuke,
};
enum tid_s : unsigned char {
	Actions, Stats, Items,
};
enum special_s : unsigned char {
	Hunches, Scrounge,
};
template<typename T> struct cflags {
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
	void			clear();
	bool			isexhause() const { return exhause != 0; }
	static stat_s	getgroup(item_s id);
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
	struct action {
		operator bool() const { return text != 0; }
		const char*	text;
		action_s	results[4];
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
struct deck : adat<item_s, 128> {
	deck() { initialize(); }
	void			add(item_s id);
	void			create(stat_s	group);
	static void		discard(item_s id);
	item_s			draw();
	item_s			drawb();
	void			draw(deck& source, int count);
	void			drawb(deck& source, int count);
	static deck&	getdeck(stat_s id);
};
struct hero {
	operator bool() const { return name != 0; }
	void			act(const char* format, ...) const;
	bool			add(item_s e);
	void			add(stat_s id, int value) { set(id, get(id) + value); }
	void			apply(action_s id);
	void			clear();
	void			choose(stat_s id, int count);
	void			choose(stat_s id, int count, int draw_count, int draw_bottom);
	void			create(const char* id);
	gender_s		getgender() const { return gender; }
	const char*		getname() const { return name; }
	char			get(stat_s id) const;
	char			getcount(stat_s id, number_s value) const;
	location_s		getlocation() const { return location; }
	bool			is(item_s e) const;
	bool			is(special_s v) const { return special == v; }
	bool			remove(item_s e);
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
extern hero			player;