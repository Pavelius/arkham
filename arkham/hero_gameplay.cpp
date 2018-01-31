#include "main.h"

static short unsigned	day;

int hero::whatdo() {
	return logs::input(true, true, "��� ������ ������?");
}

void hero::focusing() {
	static const stat_s statinfo[][2] = {
		{Speed, Sneak},
		{Fight, Will},
		{Lore, Luck},
	};
	for(auto& e : statinfo) {
		auto i = &e - statinfo;
		if(focus[i]>0)
			logs::add(i * 2, "������� %1 %2i, �� %3 %4i", getstr(e[0]), get(e[0]) + 1, getstr(e[1]), get(e[1]) - 1);
		if(focus[i]<3)
			logs::add(i * 2 + 1, "������� %1 %2i, �� %3 %4i", getstr(e[0]), get(e[0]) - 1, getstr(e[1]), get(e[1]) + 1);
	}
	auto i = logs::input(true, false, "��� �� ������ �������� ��������������?");
	auto& e = focus[i / 2];
	if(i % 2)
		e++;
	else
		e--;
}

void hero::upkeep() {
	memset(exhause, 0, sizeof(exhause));
	bool focus_count = focus;
	while(true) {
		if(day)
			logs::add("������� ����� ����.");
		logs::add("�� ����� ���� ���������� ����.");
		logs::add("�������� ������ �� ������ ������ �����������.");
		logs::add(1, "�������� ���� ����������, ��� ���������� �� ����� ���������������.");
		switch(whatdo()) {
		case 1:
			focusing();
			break;
		}
	}
}