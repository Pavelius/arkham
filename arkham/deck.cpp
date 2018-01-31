#include "main.h"

static deck common_items;
static deck unique_items;
static deck spell_items;
static deck skill_items;

void deck::add(item_s id) {
	if(id)
		adat::add(id);
}

item_s deck::draw() {
	if(!count)
		return NoItem;
	auto i = data[0];
	if(count)
		memmove(data, data + 1, count - 1);
	count--;
	return i;
}

item_s deck::drawb() {
	if(!count)
		return NoItem;
	count--;
	return data[count];
}

void deck::draw(deck& source, int count) {
	for(auto i = 0; i < count; i++)
		add(source.draw());
}

void deck::drawb(deck& source, int count) {
	for(auto i = 0; i < count; i++)
		add(source.drawb());
}

deck& deck::getdeck(stat_s id) {
	switch(id) {
	case UniqueItem: return unique_items;
	case CommonItem: return common_items;
	case Spell: return spell_items;
	case Skill: return skill_items;
	default: assert(0); return common_items;
	}
}

void deck::discard(item_s id) {
	getdeck(getgroup(id)).add(id);
}

void deck::initialize() {
	getdeck(CommonItem).create(CommonItem);
	getdeck(UniqueItem).create(UniqueItem);
	getdeck(Skill).create(Skill);
}