#include "command.h"

command* command_app_initialize;

command::command(command** first, void(*proc)()) : next(0), proc(proc)
{
	if(!(*first))
		*first = this;
	else
	{
		auto p = *first;
		while(p->next)
			p = p->next;
		p->next = this;
	}
}

void command::execute()
{
	for(auto p = this; p; p = p->next)
		p->proc();
}
