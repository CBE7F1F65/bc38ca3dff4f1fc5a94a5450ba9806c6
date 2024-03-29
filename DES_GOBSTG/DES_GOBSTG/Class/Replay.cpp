#include "../Header/Replay.h"
#include "../Header/Process.h"
#include "../Header/Player.h"
#include "../Header/Data.h"
#include "../Header/BResource.h"

Replay rpy;

Replay::Replay()
{
	ZeroMemory(&rpyinfo, sizeof(replayInfo));
}

Replay::~Replay()
{
}

void Replay::Fill()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);

	rpyinfo.modeflag = (mp.rangemode?RPYMODE_RANGE:0)|(mp.practicemode?RPYMODE_PRACTICE:0);

	rpyinfo.usingchara = mp.luchara;
	rpyinfo.maxplayer = mp.maxplayer;

	rpyinfo.startscene = mp.startscene;
	rpyinfo.endscene = mp.endscene;

	rpyinfo.alltime = mp.alltime;
	rpyinfo.year = systime.wYear;
	rpyinfo.month = systime.wMonth;
	rpyinfo.day = systime.wDay;
	rpyinfo.hour = systime.wHour;
	rpyinfo.minute = systime.wMinute;

	rpyinfo.score = Player::p.nScore;
	rpyinfo.miss = Player::p.ncMiss;
	rpyinfo.bomb = Player::p.ncBomb;
	rpyinfo.cont = Player::p.ncCont;
	rpyinfo.get = Player::p.ncGet;
	rpyinfo.pause = Player::p.ncPause;
	rpyinfo.point = Player::p.nPoint;
	rpyinfo.aliveness = Player::p.nAliveness;
	strcpy(rpyinfo.username, mp.username);

	rpyinfo.lost = Player::p.lostStack / mp.framecounter;
	rpyinfo.circlerate = (float)Player::p.circleCounter / mp.alltime;
	rpyinfo.fastrate = (float)Player::p.fastCounter / mp.alltime;

	rpyinfo.difflv = mp.nowdifflv;
	if(rpyinfo.endscene == S1)
		rpyinfo.laststage = 0xff;
	else
		rpyinfo.laststage = rpyinfo.endscene / M_STAGENSCENE;

	for (int i=0; i<M_GETRANGEMAX; i++)
	{
		rpyinfo.getrange[i] = Player::p.getrange[i];
	}
}

void Replay::partFill(BYTE part)
{
	if (part < RPYPARTMAX)
	{
		partinfo[part].offset = replayIndex + 1;
		partinfo[part].scene = mp.scene;
		partinfo[part].seed = mp.seed;
		partinfo[part].nowplayer = Player::p.nLife;
		partinfo[part].nowbomb = Player::p.nBomb;
		partinfo[part].nowpower = Player::p.nPower;
	}
	else
		part = 0;
	partinfo[part].nowaliveness = Player::p.nAliveness;
	partinfo[part].nowpoint = Player::p.nPoint;
	partinfo[part].nowgraze = Player::p.nGraze;
	partinfo[part].nowscore = Player::p.nScore;
}

bool Replay::Check(char * filename)
{
	BYTE * content;
	bool ret = false;

	char treplayfilename[M_PATHMAX];
	strcpy(treplayfilename, res.resdata.replayfoldername);
	strcat(treplayfilename, filename);
	hge->Resource_AttachPack(treplayfilename, data.password ^ REPLAYPASSWORD_XORMAGICNUM);

	content = hge->Resource_Load(hge->Resource_GetPackFirstFileName(treplayfilename));
	if(content)
	{
		if(strcmp((char *)(content + RPYOFFSET_SIGNATURE), res.resdata.replaysignature11))
			goto exit;
		if(*(DWORD *)(content + RPYOFFSET_VERSION) != GAME_VERSION)
			goto exit;
		if(strcmp((char *)(content + RPYOFFSET_COMPLETESIGN), res.resdata.replaycompletesign3))
			goto exit;
		ret = true;
	}
exit:
	hge->Resource_Free(content);
	return ret;
}

bool Replay::Load(char * filename, bool getInput)
{
	bool ret = false;
	if(Check(filename))
	{
        char treplayfilename[M_PATHMAX];
		strcpy(treplayfilename, res.resdata.replayfoldername);
		strcat(treplayfilename, filename);
		ret = Export::rpyLoad(treplayfilename, &rpyinfo, partinfo, getInput ? replayframe : NULL);
		if (getInput)
		{
			replayIndex = 0;
		}
	}
	return ret;
}

void Replay::Save(char * filename)
{
	if(!filename)
		return;

	char buffer[M_STRITOAMAX];

	DWORD _size = RPYOFFSET_INPUTDATA + (replayIndex + 1) * RPYSIZE_FRAME;
	BYTE * _rpydata = (BYTE *)malloc(_size);
	DWORD tdw;
	memcpy(_rpydata + RPYOFFSET_SIGNATURE, res.resdata.replaysignature11, RPYSIZE_SIGNATURE);
	tdw = GAME_VERSION;
	memcpy(_rpydata + RPYOFFSET_VERSION, &tdw, RPYSIZE_VERSION);
	memcpy(_rpydata + RPYOFFSET_COMPLETESIGN, res.resdata.replaycompletesign3, RPYSIZE_COMPLETESIGN);
	memcpy(_rpydata + RPYOFFSET_TAG, res.resdata.replaytag3, RPYSIZE_TAG);
	tdw = RPYOFFSET_PARTINFO;
	memcpy(_rpydata + RPYOFFSET_INFOOFFSET, &tdw, RPYSIZE_INFOOFFSET);
	strcpy(buffer, "");
	memcpy(_rpydata + RPYOFFSET_APPEND, buffer, RPYSIZE_APPEND);
	memcpy(_rpydata + RPYOFFSET_RPYINFO, &rpyinfo, RPYSIZE_RPYINFO);
	memcpy(_rpydata + RPYOFFSET_PARTINFO, partinfo, RPYSIZE_PARTINFO * RPYPARTMAX);
	memcpy(_rpydata + RPYOFFSET_INPUTDATA, replayframe, replayIndex * RPYSIZE_FRAME);

	replayFrame buff;
	buff.bias = 0;
	buff.input = 0xff;
	memcpy(_rpydata + _size-sizeof(replayFrame), &buff, sizeof(replayFrame));

	char treplayfilename[M_PATHMAX];
	strcpy(treplayfilename, res.resdata.replayfoldername);
	strcat(treplayfilename, filename);

	char crcfilename[M_PATHMAX];
	strcpy(crcfilename, filename);
	strcat(crcfilename, itoa(hge->Resource_GetCRC(_rpydata, _size), buffer, 10));
	hgeMemoryFile memfile;
	memfile.filename = crcfilename;
	memfile.data = _rpydata;
	memfile.size = _size;

	hge->Resource_CreatePack(treplayfilename, data.password ^ REPLAYPASSWORD_XORMAGICNUM, &memfile, NULL);

	free(_rpydata);
}