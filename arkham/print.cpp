#include "main.h"

int logs::getwidth(int panel) {
	return 0;
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
	if(strcmp(identifier, "�����") == 0)
		zcpy(result, name);
	else if(strcmp(identifier, "�����") == 0)
		grammar::of(result, name);
	else if(strcmp(identifier, "��������") == 0)
		zcpy(result, opponent_name);
	else if(strcmp(identifier, "���������") == 0)
		grammar::of(result, opponent_name);
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "��", identifier, "���");
	else if(strcmp(identifier, "�") == 0)
		msg(gender, result, "", identifier, "�");
	else if(strcmp(identifier, "�") == 0)
		msg(opponent_gender, result, "", "�", "�");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "", identifier, "��");
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, result, "", "��", "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "��", identifier, "���");
	else if(strcmp(identifier, "���") == 0)
		msg(opponent_gender, result, "��", "���", "���");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "���", identifier, "��");
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, result, "���", "��", "��");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "���", identifier, "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "����", identifier, "���");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}

void actor::act(const char* format, ...) const {
	logs::driver driver;
	driver.name = thing::getname();
	driver.gender = getgender();
	driver.opponent_name = 0;
	driver.opponent_gender = Male;
	logs::addv(driver, format, xva_start(format));
}

void actor::act(actor& enemy, const char* format, ...) const {
	logs::driver driver;
	driver.name = thing::getname();
	driver.gender = getgender();
	driver.opponent_name = enemy.getname();
	driver.opponent_gender = enemy.getgender();
	logs::addv(driver, format, xva_start(format));
}

int	actor::addbonus(state_s id) {
	if(is(id)) {
		remove(id);
		return 1;
	}
	return 0;
}