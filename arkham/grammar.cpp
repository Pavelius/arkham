#include "crt.h"
#include "grammar.h"

static unsigned constexpr celen(const char* str) {
	return *str ? 1 + celen(str + 1) : 0;
}

struct grammar_map {
	const char*		name;
	const char*		change;
	unsigned		name_len;
	unsigned		change_len;
	constexpr grammar_map() : name(), change(), name_len(), change_len() {}
	constexpr grammar_map(const char* name, const char* change) : name(name), change(change), name_len(celen(name)), change_len(celen(name)) {}
	operator bool() const { return name != 0; }
};

static void change(char* r, const char* s, const grammar_map* source, const char* def) {
	auto ps = s;
	auto pe = zend(s);
	auto s1 = (unsigned)(pe - ps);
	for(auto p = source; *p; p++) {
		auto s2 = p->name_len;
		if(s2 > s1)
			continue;
		if(memcmp(pe - s2, p->name, s2) == 0) {
			auto s3 = p->change_len;
			memcpy(r, s, s1 - s2);
			memcpy(r + (s1-s2), p->change, s3);
			r[s1 - s2 + s3] = 0;
			return;
		}
	}
	if(def) {
		zcpy(r, s);
		zcat(r, def);
	}
}

//static char* adv_by(char* r, const char* s) {
//	static grammar_map map[] = {
//		{"��", "��"},
//		{"��", "��"},
//		{}
//	};
//	change(r, s, map, "��");
//	return r;
//}

char* grammar::of(char* r, const char* s) {
	constexpr static grammar_map map[] = {
		{"��", "��"},
		{"��", "�"},
		{"��", "���"},
		{"��", "�"},
		{"�", "�"},
		{"�", "�"},
		{"�", "�"},
		{"�", "�"},
		{}
	};
	change(r, s, map, "�");
	return r;
}

char* grammar::by(char* r, const char* s) {
	static grammar_map map[] = {
		{"��", "��"},
		{"��", "���"},
		{"�", "��"}, {"�", "��"}, {"�", "��"},
		{"�", "��"},
		{"�", "���"},
		{}
	};
	change(r, s, map, "��");
	return r;
}

char* grammar::to(char* r, const char* s) {
	static grammar_map map[] = {
		{"�", "�"},
		{"�", "�"},
		{"�", "��"},
		{}
	};
	change(r, s, map, "�");
	return r;
}

char* grammar::pluar::of(char* r, const char* s) {
	static grammar_map map[] = {
		{"��", "�"},
		{"�", ""},
		{"�", ""},
		{"�", "�"},
		{"�", "���"},
		{"�", "���"},
		{}
	};
	change(r, s, map, "��");
	return r;
}

char* grammar::get(char* result, const char* word, int count) {
	if(count <= 1) {
		zcpy(result, word);
	} else {
		szprint(result, "%1i ", count);
		auto p = zend(result);
		if(count <= 4)
			of(p, word);
		else
			pluar::of(p, word);
	}
	return result;
}
