#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/Selector.h"
#include "../Header/SE.h"

int Process::processTitle()
{
	time++;
	if(time == 1)
	{
		reload();
		Selector::select = titleselect;
	}
	retvalue = PGO;
	scr.controlExecute(STATE_TITLE, time);
	if(Selector::complete)
	{
		titleselect = Selector::select;
		Selector::Clear();
	}
	if(hge->Input_GetDIKey(KS_BOMB, DIKEY_DOWN))
	{
		SE::push(SE_SYSTEM_CANCEL);
		if(Selector::select == Selector::nselect - 1)
			return PQUIT;
		Selector::select = Selector::nselect - 1;
	}
	return retvalue;
}