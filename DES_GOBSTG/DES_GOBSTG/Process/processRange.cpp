#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/Selector.h"
#include "../Header/SE.h"

int Process::processRange()
{
	time++;
	if(time == 1)
	{
		Selector::Clear();
	}
	scr.controlExecute(STATE_RANGE, time);

	if(hge->Input_GetDIKey(KS_BOMB, DIKEY_DOWN))
	{
		SE::push(SE_SYSTEM_CANCEL);
		time = 0;
		state = STATE_TITLE;
		return PTURN;
	}

	return PGO;
}