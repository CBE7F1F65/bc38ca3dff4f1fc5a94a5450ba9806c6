#include "../Header/keytable.h"
#include "../Header/Scripter.h"
#include "../Header/Bullet.h"
#include "../Header/InfoSelect.h"
#include "../Header/SE.h"
#include "../Header/Process.h"
#include "../Header/BGLayer.h"
#include "../Header/Data.h"

scrKeyWord scrKeyTable[] =
{
	{"DES_GOBSTG_SCRIPTFILE",	SCR_SCRIPTTAG},

	{"CONTROLFILE",				SCR_CONTROL},
	{"STAGEFILE",				SCR_STAGE},
	{"EDEFFILE",				SCR_EDEF},
	{"SCENEFILE",				SCR_SCENE},
	{"FUNCTIONFILE",			SCR_FUNCTION},

	{"#",						SCR_FILENAME},
	{"@",						SCR_BLOCKCON},

	/************************************************************************/
	/* Action                                                               */
	/************************************************************************/
	{"SD",						SCR_SD},
	{"SDf",						SCR_SDF},
	{"SDu",						SCR_SDU},
	{"ST",						SCR_ST},
	{"CALL",					SCR_CALL},
	{"EXECUTE",					SCR_EXECUTE},

	{"RETURN",					SCR_RETURN},
	{"SETSTATE",				SCR_SETSTATE},
	{"SETTIME",					SCR_SETTIME},
	{"SETDIFFI",				SCR_SETDIFFI},
	{"SETCHARA",				SCR_SETCHARA},
	{"SETSCENE",				SCR_SETSCENE},
	{"SETMODE",					SCR_SETMODE},
	{"SETKEY",					SCR_SETKEY},
	{"DISABLEALLKEY",			SCR_DISABLEALLKEY},

	{"MUSICCHANGE",				SCR_MUSICCHANGE},
	{"MUSICSLIDE",				SCR_MUSICSLIDE},
	{"SE",						SCR_SE},
	{"SEOFF",					SCR_SEOFF},
	{"EFFSETUP",				SCR_EFFSETUP},
	{"EFFSETUPEX",				SCR_EFFSETUPEX},
	{"EFFSETUPCHASE",			SCR_EFFSETUPCHASE},
	{"EFFSTOP",					SCR_EFFSTOP},
	{"EFFOFF",					SCR_EFFOFF},
	{"EFFSET",					SCR_EFFSET},
	{"EFFMOVETO",				SCR_EFFMOVETO},
	{"BOSSSTORE",				SCR_BOSSSTORE},
	{"BOSSATTACK",				SCR_BOSSATTACK},

	/************************************************************************/
	/* Basic                                                                */
	/************************************************************************/
	{"B",						SCR_BUBUILD},
	{"A",						SCR_BUACTIONSET},
	{"BC",						SCR_BUBUILDCIRCLE},
	{"BUDECANCEL",				SCR_BUDECANCEL},
	{"BEB",						SCR_BEBUILD},
	{"BEVECTOR",				SCR_BEVECTOR},
	{"BEHOLD",					SCR_BEHOLD},
	{"BEPIN",					SCR_BEPIN},

	{"GB",						SCR_GHBUILD},
	{"GHSAIM",					SCR_GHSAIM},
	{"GHSET",					SCR_GHSET},
	{"GHCHASE",					SCR_GHCHASE},

	{"ENTEXASSIGN",				SCR_ENTEXASSIGN},
	{"EB",						SCR_ENBUILD},
	{"EA",						SCR_ENACTIONSET},
	{"ENSAIM",					SCR_ENSAIM},
	{"ENCHASE",					SCR_ENCHASE},

	{"RAMA",					SCR_RAMA},
	{"DIST",					SCR_DIST},

	{"BOSSUP",					SCR_BOSSUP},
	{"RANGEUP",					SCR_RANGEUP},
	{"ACONTROL",				SCR_ACONTROL},
	{"BCONTROL",				SCR_BCONTROL},
	{"COLLISION_CIRCLE",		SCR_COLLISION_CIRCLE},
	{"COLLISION_SQUARE",		SCR_COLLISION_SQUARE},

	{"SETPPOS",					SCR_SETPPOS},
	{"SETPLIFE",				SCR_SETPLIFE},
	{"SETPBOMB",				SCR_SETPBOMB},
	{"SETPPOWER",				SCR_SETPPOWER},
	{"SETPALIVENESS",			SCR_SETPALIVENESS},
	{"SETPPOINT",				SCR_SETPPOINT},
	{"SETPBCIRCLE",				SCR_SETPBCIRCLE},
	{"SETPBSLOW",				SCR_SETPBSLOW},
	{"SETPBINFI",				SCR_SETPBINFI},
	{"SETPSPEED",				SCR_SETPSPEED},
	{"SETPSLOWSPEED",			SCR_SETPSLOWSPEED},
	{"COLLAPSE",				SCR_COLLAPSE},

	{"BGVALUE",					SCR_BGVALUE},
	{"BGVALEX",					SCR_BGVALEX},
	{"BGTEXRECT",				SCR_BGTEXRECT},
	{"BGRECT",					SCR_BGRECT},
	{"BGZ",						SCR_BGZ},
	{"BGSCALE",					SCR_BGSCALE},
	{"BGCOLOR",					SCR_BGCOLOR},
	{"BGMOVE",					SCR_BGMOVE},
	{"BGFLAG",					SCR_BGFLAG},
	{"BGPARAL",					SCR_BGPARAL},
	{"BG4V",					SCR_BG4V},
	{"BGOFF",					SCR_BGOFF},
	{"BGSETUP",					SCR_BGSETUP},

	{"SELBUILD",				SCR_SELBUILD},
	{"SELCLEAR",				SCR_SELCLEAR},
	{"SELCONFIRM",				SCR_SELCONFIRM},
	{"SELSET",					SCR_SELSET},
	{"ISELBUILD",				SCR_ISELBUILD},
	{"ISELCLEAR",				SCR_ISELCLEAR},
	{"ISELSET",					SCR_ISELSET},

	/************************************************************************/
	/* Control                                                              */
	/************************************************************************/
	{"IF",						SCR_IF},
	{"ELSE",					SCR_ELSE},
	{"ELSEIF",					SCR_ELSEIF},
	{"{",						SCR_THEN},
	{"}",						SCR_END},
	{"LOOP",					SCR_LOOP},

	{"CHATON",					SCR_CHATON},
	{"CHATOFF",					SCR_CHATOFF},

	/************************************************************************/
	/* Data                                                                 */
	/************************************************************************/
	{"DATAGET",					SCR_DATAGET},
	{"DATAGETf",				SCR_DATAGETf},
	{"DATASET",					SCR_DATASET},
	{"DATASETf",				SCR_DATASETf},
	{"TRYSTAGE",				SCR_TRYSTAGE},
	{"DEBUG_BREAKPOINT",		SCR_DEBUG_BREAKPOINT},

	/************************************************************************/
	/* Expression                                                           */
	/************************************************************************/
	{"+",						SCR_ADD_INT},
	{"-",						SCR_SUB_INT},
	{"*",						SCR_MUL_INT},
	{"/",						SCR_DIV_INT},
	{"+f",						SCR_ADD_FLOAT},
	{"-f",						SCR_SUB_FLOAT},
	{"*f",						SCR_MUL_FLOAT},
	{"/f",						SCR_DIV_FLOAT},
	{"+u",						SCR_ADD_UINT},
	{"-u",						SCR_SUB_UINT},
	{"*u",						SCR_MUL_UINT},
	{"/u",						SCR_DIV_UINT},
	{"%",						SCR_MOD},
	{"%u",						SCR_MOD_UINT},

	{"~",						SCR_INVERSE},
	{"!",						SCR_NOT},
	{">",						SCR_GREAT_INT},
	{"<",						SCR_LESS_INT},
	{">f",						SCR_GREAT_FLOAT},
	{"<f",						SCR_LESS_FLOAT},
	{">u",						SCR_GREAT_UINT},
	{"<u",						SCR_LESS_UINT},

	/************************************************************************/
	/* Function                                                             */
	/************************************************************************/
	{"BUI",						SCR_BUI},
	{"BUANGLE",					SCR_BUANGLE},
	{"BUSPEED",					SCR_BUSPEED},
	{"BUX",						SCR_BUX},
	{"BUY",						SCR_BUY},
	{"BU@",						SCR_BUTIMER},
	{"BEI",						SCR_BEI},
	{"BEANGLE",					SCR_BEANGLE},
	{"BESPEED",					SCR_BESPEED},
	{"BEX",						SCR_BEX},
	{"BEY",						SCR_BEY},
	{"BE@",						SCR_BETIMER},
	{"BEHOLDTAR",				SCR_BEHOLDTAR},
	{"BEPINTAR",				SCR_BEPINTAR},

	{"GHX",						SCR_GHX},
	{"GHY",						SCR_GHY},
	{"GH@",						SCR_GHTIMER},
	{"GHI",						SCR_GHI},
	{"GHANGLE",					SCR_GHANGLE},
	{"GHSPEED",					SCR_GHSPEED},
	{"GHAMAP",					SCR_GHAMAP},
	{"GHRMAP",					SCR_GHRMAP},
	{"GHAIMX",					SCR_GHAIMX},
	{"GHAIMY",					SCR_GHAIMY},
	{"GHAC",					SCR_GHAC},

	{"ENX",						SCR_ENX},
	{"ENY",						SCR_ENY},
	{"EN@",						SCR_ENTIMER},
	{"ENI",						SCR_ENI},
	{"ENANGLE",					SCR_ENANGLE},
	{"ENSPEED",					SCR_ENSPEED},
	{"ENAMAP",					SCR_ENAMAP},
	{"ENRMAP",					SCR_ENRMAP},
	{"ENAIMX",					SCR_ENAIMX},
	{"ENAIMY",					SCR_ENAIMY},

	{"RAND",					SCR_RAND},
	{"RANDA",					SCR_RANDA},
	{"RANDR",					SCR_RANDR},
	{"SEED",					SCR_SEED},
	{"SINA",					SCR_SINA},
	{"COSA",					SCR_COSA},
	{"TANA",					SCR_TANA},
	{"ATAN2",					SCR_ATAN2},
	{"SQRT",					SCR_SQRT},
	{"SIGN",					SCR_SIGN},
	{"ROLL",					SCR_ROLL},

	{"D",						SCR_D},
	{"Du",						SCR_DU},
	{"TX",						SCR_TX},
	{"TY",						SCR_TY},
	{"TIME",					SCR_TIME},
	{"NOW#",					SCR_NOWNAME},
	{"NOW@",					SCR_NOWCON},
	{"DIFFI",					SCR_DIFFI},
	{"CHARA",					SCR_CHARA},
	{"GETSCENE",				SCR_GETSCENE},
	{"MODE",					SCR_MODE},
	{"REPLAYMODE",				SCR_REPLAYMODE},

	{"CHATI",					SCR_CHATI},
	{"BOSSFAILED",				SCR_BOSSFAILED},
	{"BOSSFLAG",				SCR_BOSSFLAG},
	{"CHECKKEY",				SCR_CHECKKEY},

	{"BGS@",					SCR_BGSTIMER},

	{"SELCOMPLETE",				SCR_SELCOMPLETE},
	{"SEL",						SCR_SEL},
	{"ISELCOMPLETE",			SCR_ISELCOMPLETE},
	{"ISEL",					SCR_ISEL},

	{"PX",						SCR_PX},
	{"PY",						SCR_PY},
	{"PLIFE",					SCR_PLIFE},
	{"PBOMB",					SCR_PBOMB},
	{"PPOWER",					SCR_PPOWER},
	{"PALIVENESS",				SCR_PALIVENESS},
	{"PPOINT",					SCR_PPOINT},
	{"PBCIRCLE",				SCR_PBCIRCLE},
	{"PBSLOW",					SCR_PBSLOW},
	{"PBINFI",					SCR_PBINFI},
	{"PSPEED",					SCR_PSPEED},
	{"PSLOWSPEED",				SCR_PSLOWSPEED},


	{SCR_CONST_STR,				SCR_CONST},

	{"true",					true},
	{"false",					false},

	{"STATE_START",				STATE_START},
	{"STATE_PAUSE",				STATE_PAUSE},
	{"STATE_CONTINUE",			STATE_CONTINUE},
	{"STATE_CLEAR",				STATE_CLEAR},
	{"STATE_ENDING",			STATE_ENDING},
	{"STATE_TITLE",				STATE_TITLE},
	{"STATE_PLAYER_SELECT",		STATE_PLAYER_SELECT},
	{"STATE_DIFFICULT_SELECT",	STATE_DIFFICULT_SELECT},
	{"STATE_OVER",				STATE_OVER},
	{"STATE_RANGE",				STATE_RANGE},
	{"STATE_REPLAY",			STATE_REPLAY},
	{"STATE_RESAULT",			STATE_RESAULT},
	{"STATE_MUSIC",				STATE_MUSIC},
	{"STATE_OPTION",			STATE_OPTION},
	{"STATE_INIT",				STATE_INIT},

	{"PQUIT",					PQUIT},
	{"PGO",						PGO},
	{"POK",						POK},
	{"PBACK",					PBACK},
	{"PTURN",					PTURN},
	{"PSKIP",					PSKIP},

	{"THEN",					THEN},
	{"SECTIONEND",				SECTIONEND},
	{"EVERY",					EVERY},
	{"EVERYMOD",				EVERYMOD},
	{"TIMERGREAT",				TIMERGREAT},
	{"TIMEREQUAL",				TIMEREQUAL},
	{"TIMERLESS",				TIMERLESS},
	{"TIMERRANGE",				TIMERRANGE},
	{"TYPEEQUAL",				TYPEEQUAL},
	{"COLOREQUAL",				COLOREQUAL},
	{"ANGLEGREAT",				ANGLEGREAT},
	{"ANGLEEQUAL",				ANGLEEQUAL},
	{"ANGLELESS",				ANGLELESS},
	{"ANGLERANGE",				ANGLERANGE},
	{"XGREAT",					XGREAT},
	{"XLESS",					XLESS},
	{"XRANGE",					XRANGE},
	{"YGREAT",					YGREAT},
	{"YLESS",					YLESS},
	{"YRANGE",					YRANGE},
	{"VALGREAT",				VALGREAT},
	{"VALEQUAL",				VALEQUAL},
	{"VALLESS",					VALLESS},
	{"VALRANGE",				VALRANGE},
	{"SPEEDGREAT",				SPEEDGREAT},
	{"SPEEDEQUAL",				SPEEDEQUAL},
	{"SPEEDLESS",				SPEEDLESS},
	{"SPEEDRANGE",				SPEEDRANGE},
	{"TYPESET",					TYPESET},
	{"COLORSET",				COLORSET},
	{"ANGLESET",				ANGLESET},
	{"ANGLESETADD",				ANGLESETADD},
	{"ANGLEADJUST",				ANGLEADJUST},
	{"HEADANGLESET",			HEADANGLESET},
	{"HEADANGLESETADD",			HEADANGLESETADD},
	{"ANGLESETRMA",				ANGLESETRMA},
	{"ANGLESETRMAP",			ANGLESETRMAP},
	{"ANGLESETRMAT",			ANGLESETRMAT},
	{"ANGLESETAMA",				ANGLESETAMA},
	{"ANGLESETAMAP",			ANGLESETAMAP},
	{"ANGLESETAMAT",			ANGLESETAMAT},
	{"XSET",					XSET},
	{"YSET",					YSET},
	{"XSETADD",					XSETADD},
	{"YSETADD",					YSETADD},
	{"XSETACCADD",				XSETACCADD},
	{"YSETACCADD",				YSETACCADD},
	{"VALSET",					VALSET},
	{"VALSETADD",				VALSETADD},
	{"SPEEDSET",				SPEEDSET},
	{"SPEEDSETADD",				SPEEDSETADD},
	{"CALLSCRIPT",				CALLSCRIPT},
	{"CHASE",					CHASE},
	{"AND",						AND},
	{"OR",						OR},
	{"NOT",						NOT},
	{"ANDSET",					ANDSET},
	{"REMAIN",					REMAIN},
	{"FADEOUT",					FADEOUT},
	{"ITEMLIZE",				ITEMLIZE},
	{"POINTLIZE",				POINTLIZE},
	{"BOUNCE",					BOUNCE},

	{"INFO_GREEN",				INFO_GREEN},
	{"INFO_YELLOW",				INFO_YELLOW},
	{"INFO_GRAY",				INFO_GRAY},
	{"INFO_RED",				INFO_RED},
	{"INFO_BLUE",				INFO_BLUE},

	{"BG_NONE",					BG_NONE},
	{"BG_WHITEFLASH",			BG_WHITEFLASH},
	{"BG_REDFLASH",				BG_REDFLASH},
	{"BG_YELLOWFLASH",			BG_YELLOWFLASH},
	{"BG_WHITEOUT",				BG_WHITEOUT},
	{"BG_REDOUT",				BG_REDOUT},
	{"BG_FADEOUT",				BG_FADEOUT},
	{"BG_LIGHTUP",				BG_LIGHTUP},
	{"BG_LIGHTRED",				BG_LIGHTRED},
	{"BG_PAUSEIN",				FG_PAUSEIN},
	{"BG_PAUSEOUT",				FG_PAUSEOUT},

	{"SE_DEFAULT",				SE_DEFAULT},
	{"SE_PLAYER_SHOOT_1",		SE_PLAYER_SHOOT_1},
	{"SE_PLAYER_SHOOT_2",		SE_PLAYER_SHOOT_2},
	{"SE_PLAYER_SHOOT_3",		SE_PLAYER_SHOOT_3},
	{"SE_PLAYER_SHOOT_4",		SE_PLAYER_SHOOT_4},
	{"SE_PLAYER_SHOOT_5",		SE_PLAYER_SHOOT_5},
	{"SE_PLAYER_SHOOT_6",		SE_PLAYER_SHOOT_6},
	{"SE_PLAYER_SHOOT_7",		SE_PLAYER_SHOOT_7},
	{"SE_PLAYER_SHOOT_8",		SE_PLAYER_SHOOT_8},
	{"SE_PLAYER_BOMB_1",		SE_PLAYER_BOMB_1},
	{"SE_PLAYER_BOMB_2",		SE_PLAYER_BOMB_2},
	{"SE_PLAYER_BOMB_3",		SE_PLAYER_BOMB_3},
	{"SE_PLAYER_BOMB_4",		SE_PLAYER_BOMB_4},
	{"SE_PLAYER_GRAZE",			SE_PLAYER_GRAZE},
	{"SE_PLAYER_SHOT",			SE_PLAYER_SHOT},
	{"SE_PLAYER_DEAD",			SE_PLAYER_DEAD},
	{"SE_PLAYER_SLOWON",		SE_PLAYER_SLOWON},
	{"SE_PLAYER_SLOWOFF",		SE_PLAYER_SLOWOFF},
	{"SE_PLAYER_CIRCLEON",		SE_PLAYER_CIRCLEON},
	{"SE_PLAYER_CIRCLEOFF",		SE_PLAYER_CIRCLEOFF},
	{"SE_BULLET_1",				SE_BULLET_1},
	{"SE_BULLET_2",				SE_BULLET_2},
	{"SE_BULLET_3",				SE_BULLET_3},
	{"SE_BULLET_4",				SE_BULLET_4},
	{"SE_BULLET_CHANGE_1",		SE_BULLET_CHANGE_1},
	{"SE_BULLET_CHANGE_2",		SE_BULLET_CHANGE_2},
	{"SE_BULLET_BOUND",			SE_BULLET_BOUND},
	{"SE_BULLET_FADEOUT",		SE_BULLET_FADEOUT},
	{"SE_BEAM_1",				SE_BEAM_1},
	{"SE_BEAM_2",				SE_BEAM_2},
	{"SE_BEAM_REFLECT",			SE_BEAM_REFLECT},
	{"SE_BEAM_FADEOUT",			SE_BEAM_FADEOUT},
	{"SE_BOSS_UP",				SE_BOSS_UP},
	{"SE_BOSS_DEAD",			SE_BOSS_DEAD},
	{"SE_BOSS_TIMEOUT",			SE_BOSS_TIMEOUT},
	{"SE_BOSS_TIMEUP",			SE_BOSS_TIMEUP},
	{"SE_BOSS_KIRA",			SE_BOSS_KIRA},
	{"SE_BOSS_POWER_1",			SE_BOSS_POWER_1},
	{"SE_BOSS_POWER_2",			SE_BOSS_POWER_2},
	{"SE_BOSS_BONUS_1",			SE_BOSS_BONUS_1},
	{"SE_BOSS_BONUS_2",			SE_BOSS_BONUS_2},
	{"SE_ENEMY_DAMAGE_1",		SE_ENEMY_DAMAGE_1},
	{"SE_ENEMY_DAMAGE_2",		SE_ENEMY_DAMAGE_2},
	{"SE_ENEMY_DEAD",			SE_ENEMY_DEAD},
	{"SE_GHOST_DEAD",			SE_GHOST_DEAD},
	{"SE_GHOST_MERGE",			SE_GHOST_MERGE},
	{"SE_GHOST_HALF",			SE_GHOST_HALF},
	{"SE_ITEM_GET",				SE_ITEM_GET},
	{"SE_ITEM_EXTEND",			SE_ITEM_EXTEND},
	{"SE_ITEM_POWERUP",			SE_ITEM_POWERUP},
	{"SE_SYSTEM_OK",			SE_SYSTEM_OK},
	{"SE_SYSTEM_CANCEL",		SE_SYSTEM_CANCEL},
	{"SE_SYSTEM_SELECT",		SE_SYSTEM_SELECT},
	{"SE_SYSTEM_PAUSE",			SE_SYSTEM_PAUSE},

	{"MAXDESC",					SCR_MAXDESC},
	{"VARBEGIN",				SCR_VARBEGIN},
	{"FREEBEGIN",				SCR_FREEBEGIN},
	{"RESERVEBEGIN",			SCR_RESERVEBEGIN},

	{"BTYPE_BULLET",			BTYPE_BULLET},
	{"BTYPE_BEAM",				BTYPE_BEAM},
	{"BTYPE_ENEMY",				BTYPE_ENEMY},
	{"BTYPE_GHOST",				BTYPE_GHOST},

	{"CT_CONTROL",				SCR_CTCONTROL},
	{"CT_STAGE",				SCR_CTSTAGE},
	{"CT_EDEF",					SCR_CTEDEF},
	{"CT_SCENE",				SCR_CTSCENE},
	{"CT_FUNCTION",				SCR_CTFUNCTION},

	{"KEY_PRESSED",				DIKEY_PRESSED},
	{"KEY_DOWN",				DIKEY_DOWN},
	{"KEY_UP",					DIKEY_UP},

	{SCR_KEYSTATE_STR,			SCR_KEYSTATE},

	{"KS_UP",					(DWORD)&(mp.keyUp)},
	{"KS_DOWN",					(DWORD)&(mp.keyDown)},
	{"KS_LEFT",					(DWORD)&(mp.keyLeft)},
	{"KS_RIGHT",				(DWORD)&(mp.keyRight)},
	{"KS_FIRE",					(DWORD)&(mp.keyFire)},
	{"KS_BOMB",					(DWORD)&(mp.keyBomb)},
	{"KS_SLOW",					(DWORD)&(mp.keySlow)},
	{"KS_CIRCLE",				(DWORD)&(mp.keyCircle)},
	{"KS_PAUSE",				(DWORD)&(mp.keyPause)},
	{"KS_SKIP",					(DWORD)&(mp.keySkip)},
	{"KS_ENTER",				(DWORD)&(mp.keyEnter)},
	{"KS_ESCAPE",				(DWORD)&(mp.keyEscape)},
	{"KS_CAPTURE",				(DWORD)&(mp.keyCapture)},

	{SCR_NULL_STR,				SCR_NULL},
};