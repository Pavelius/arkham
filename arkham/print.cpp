#include "main.h"

int logs::getwidth(int panel) {
	return 300;
}

const char* logs::getpanel(int panel) {
	return 0;
}

static void msg(gender_s gender, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
	if(gender == Female) {
		if(text_female)
			zcpy(result, text_female);
	} else {
		if(text_male)
			zcpy(result, text_male);
	}
}

void logs::driver::parseidentifier(char* result, const char* result_max, const char* identifier) {
	if(strcmp(identifier, "герой") == 0)
		zcpy(result, name);
	else if(strcmp(identifier, "героя") == 0)
		grammar::of(result, name);
	else if(strcmp(identifier, "оппонент") == 0)
		zcpy(result, opponent_name);
	else if(strcmp(identifier, "оппонента") == 0)
		grammar::of(result, opponent_name);
	else if(strcmp(identifier, "ась") == 0)
		msg(gender, result, "ся", identifier, "ись");
	else if(strcmp(identifier, "а") == 0)
		msg(gender, result, "", identifier, "и");
	else if(strcmp(identifier, "А") == 0)
		msg(opponent_gender, result, "", "а", "и");
	else if(strcmp(identifier, "ла") == 0)
		msg(gender, result, "", identifier, "ли");
	else if(strcmp(identifier, "ЛА") == 0)
		msg(opponent_gender, result, "", "ла", "ли");
	else if(strcmp(identifier, "она") == 0)
		msg(gender, result, "он", identifier, "они");
	else if(strcmp(identifier, "ОНА") == 0)
		msg(opponent_gender, result, "он", "она", "они");
	else if(strcmp(identifier, "ее") == 0)
		msg(gender, result, "его", identifier, "их");
	else if(strcmp(identifier, "ЕЕ") == 0)
		msg(opponent_gender, result, "его", "ее", "их");
	else if(strcmp(identifier, "ей") == 0)
		msg(gender, result, "ему", identifier, "им");
	else if(strcmp(identifier, "нее") == 0)
		msg(gender, result, "него", identifier, "них");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}

void hero::act(const char* format, ...) const {
	logs::driver driver;
	driver.name = getname();
	driver.gender = getgender();
	driver.opponent_name = 0;
	driver.opponent_gender = Male;
	logs::addv(driver, format, xva_start(format));
}