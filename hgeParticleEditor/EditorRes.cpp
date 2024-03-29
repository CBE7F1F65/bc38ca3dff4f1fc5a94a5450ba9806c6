#include "EditorRes.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/Export.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/BResource.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/Data.h"

EditorRes eres;

EditorRes::EditorRes()
{
	bg = NULL;
	panel = NULL;
	button = NULL;

	for(int i=0; i<UIITEMMAX; i++)
	{
		iteminfo[i].state = 0;
		iteminfo[i].inputtype = 0;
	}

	font = NULL;

	for(int i=0; i<TEXMAX; i++)
	{
		tex[i] = NULL;
	}

	for(int i=0; i<EFFECTSYSTYPEMAX; i++)
	{
		eff[i] = NULL;
	}
	bgtex = -1;
}

EditorRes::~EditorRes()
{
}

bool EditorRes::Load()
{
	Release();

	if(Export::GetResourceFile())
	{
		MessageBox(hge->System_GetState(HGE_HWND), "Error in Loading Resource File!", "Error", MB_OK);
		return false;
	}
	data.GetIni();
	Export::clientAdjustWindow();
	res.Fill();
	res.LoadPackage();
//	res.SetDataFile();

	for(int i=0; i<TEXMAX; i++)
	{
		if(strlen(res.resdata.texfilename[i]))
		{
			tex[i] = hge->Texture_Load(res.resdata.texfilename[i]);
			if(!tex[i])
				return false;
		}
	}

	bg = new hgeSprite(tex[TEX_WHITE], 0, 0, 1, 1);
	bg->SetColor(0x60ffffff);
	panel = new hgeSprite(tex[TEX_WHITE], 0, 0, 1, 1);
	panel->SetColor(0xeeeeeeee);
	button = new hgeSprite(tex[TEX_WHITE], 0, 0, 1, 1);
	button->SetColor(0x0000000);
	font = new hgeFont(res.resdata.normalfontfilename);
	font->SetColor(0xffffffff);

	for(int i=0; i<EFFECTSYSTYPEMAX; i++)
	{
		char buffer[M_STRMAX];
		if(strlen(res.resdata.effectsysfilename[i]))
		{
			eff[i] = new hgeEffectSystem;
			strcpy(buffer, res.resdata.effectsysfoldername);
			strcat(buffer, res.resdata.effectsysfilename[i]);
			texnum[i] = Export::effLoad(buffer, eff[i], tex);
			if(texnum[i] < 0)
			{
				HGELOG("Error in loading Effect System File %s!", buffer);
				data.SetEffectSystemResourceName(i, "");
				delete eff[i];
				eff[i] = NULL;
			}
		}
	}

	return true;
}

char * EditorRes::GetAffectorName(char type)
{
	switch(type)
	{
	case HGEEFFECT_AFFECTORTYPE_NONE:
		strcpy(affectorname, "None");
		break;
	case HGEEFFECT_AFFECTORTYPE_SPIN:
		strcpy(affectorname, "Spin");
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEEDRADIAL:
		strcpy(affectorname, "Raditial");
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEEDTANGENTIAL:
		strcpy(affectorname, "Tagential");
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEED_X:
		strcpy(affectorname, "SpeedX");
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEED_Y:
		strcpy(affectorname, "SpeedY");
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEED_Z:
		strcpy(affectorname, "SpeedZ");
		break;
	case HGEEFFECT_AFFECTORTYPE_SCALE:
		strcpy(affectorname, "Scale");
		break;
	case HGEEFFECT_AFFECTORTYPE_SCALE_X:
		strcpy(affectorname, "ScaleX");
		break;
	case HGEEFFECT_AFFECTORTYPE_SCALE_Y:
		strcpy(affectorname, "ScaleY");
		break;
	case HGEEFFECT_AFFECTORTYPE_ZSTRETCH:
		strcpy(affectorname, "ZStretch");
		break;
	case HGEEFFECT_AFFECTORTYPE_COLOR:
		strcpy(affectorname, "Color");
		break;
	default:
		strcpy(affectorname, "");
		break;
	}
	return affectorname;
}

char * EditorRes::GetFilename(int effi)
{
	data.GetEffectSystemResourceName(effi, filename);
	return filename;
}

char * EditorRes::GetFullFilename(int effi)
{
	strcpy(fullfilename, res.resdata.effectsysfoldername);
	strcat(fullfilename, GetFilename(effi));
	return fullfilename;
}

bool EditorRes::Save(int savei)
{
	if(!eff[savei] || texnum[savei] < 0 ||!tex[texnum[savei]])
	{
		MessageBox(NULL, "Cannot Save Effectsystem!\nNo EffectSystem exists or Texture Error!", "Error", MB_OK);
		return false;
	}
	char buffer[M_STRMAX];
	strcpy(buffer, "Save EffectSystem As ");
	strcat(buffer, GetFullFilename(savei));
	strcat(buffer, " ?");
	if(MessageBox(NULL, buffer, "", MB_OKCANCEL) == IDCANCEL)
		return false;

	return Export::effSave(fullfilename, eff[savei], texnum[savei]);
}

void EditorRes::Release()
{
	if(bg)
		delete bg;
	bg = NULL;
	bgtex = -1;

	if(panel)
		delete panel;
	panel = NULL;

	if(button)
		delete button;
	button = NULL;

	if(font)
		delete font;
	font = NULL;

	for(int i=0; i<TEXMAX; i++)
	{
		if(tex[i])
			hge->Texture_Free(tex[i]);
		tex[i] = NULL;
	}

	for(int i=0; i<EFFECTSYSTYPEMAX; i++)
	{
		if(eff[i])
			delete eff[i];
		eff[i] = NULL;
		texnum[i] = -1;
	}
}

void EditorRes::Init()
{
	float buttonWidth = (M_CLIENT_RIGHT - M_ACTIVECLIENT_RIGHT) / 3.0f;
	float buttonHeight = UIITEM_FONT + 2 * UIITEM_EDGE;
	/*
	**----------------------------------
	**	ES		|	EE		|	EA
	**==================================
	**			TITLE		|	Add	
	**==================================
	************************************
	************************************
	**==================================
	**	Input	|	PageUp	|	PageDown
	**==================================
	**	BG		|	Save	|	Refresh
	**----------------------------------
	*/
	strcpy(iteminfo[UIITEM_EBINFO].info, "EB");
	iteminfo[UIITEM_EBINFO].x = M_ACTIVECLIENT_RIGHT;
	iteminfo[UIITEM_EBINFO].y = M_ACTIVECLIENT_TOP;
	iteminfo[UIITEM_EBINFO].w = buttonWidth;
	iteminfo[UIITEM_EBINFO].h = buttonHeight;
	iteminfo[UIITEM_EBINFO].state = true;
	strcpy(iteminfo[UIITEM_EEINFO].info, "EE");
	iteminfo[UIITEM_EEINFO].x = M_ACTIVECLIENT_RIGHT + buttonWidth;
	iteminfo[UIITEM_EEINFO].y = M_ACTIVECLIENT_TOP;
	iteminfo[UIITEM_EEINFO].w = buttonWidth;
	iteminfo[UIITEM_EEINFO].h = buttonHeight;
	iteminfo[UIITEM_EEINFO].state = true;
	strcpy(iteminfo[UIITEM_EAINFO].info, "EA");
	iteminfo[UIITEM_EAINFO].x = M_ACTIVECLIENT_RIGHT + 2 * buttonWidth;
	iteminfo[UIITEM_EAINFO].y = M_ACTIVECLIENT_TOP;
	iteminfo[UIITEM_EAINFO].w = buttonWidth;
	iteminfo[UIITEM_EAINFO].h = buttonHeight;
	iteminfo[UIITEM_EAINFO].state = true;
	
	strcpy(iteminfo[UIITEM_TITLEINFO].info, "Title");
	iteminfo[UIITEM_TITLEINFO].x = M_ACTIVECLIENT_RIGHT;
	iteminfo[UIITEM_TITLEINFO].y = M_ACTIVECLIENT_TOP + buttonHeight;
	iteminfo[UIITEM_TITLEINFO].w = buttonWidth * 2;
	iteminfo[UIITEM_TITLEINFO].h = buttonHeight;
	iteminfo[UIITEM_TITLEINFO].state = true;
	strcpy(iteminfo[UIITEM_ADDINFO].info, "Add");
	iteminfo[UIITEM_ADDINFO].x = M_ACTIVECLIENT_RIGHT + buttonWidth * 2;
	iteminfo[UIITEM_ADDINFO].y = M_ACTIVECLIENT_TOP + buttonHeight;
	iteminfo[UIITEM_ADDINFO].w = buttonWidth;
	iteminfo[UIITEM_ADDINFO].h = buttonHeight;
	iteminfo[UIITEM_ADDINFO].state = true;
	iteminfo[UIITEM_ADDINFO].inputtype = UIINPUTTYPE_INT;

	
	strcpy(iteminfo[UIITEM_INPUTINFO].info, "Input");
	iteminfo[UIITEM_INPUTINFO].x = M_ACTIVECLIENT_RIGHT;
	iteminfo[UIITEM_INPUTINFO].y = M_CLIENT_BOTTOM - 2 * buttonHeight;
	iteminfo[UIITEM_INPUTINFO].w = buttonWidth;
	iteminfo[UIITEM_INPUTINFO].h = buttonHeight;
	iteminfo[UIITEM_INPUTINFO].state = true;
	strcpy(iteminfo[UIITEM_PAGEUPINFO].info, "PageUp");
	iteminfo[UIITEM_PAGEUPINFO].x = M_ACTIVECLIENT_RIGHT + buttonWidth;
	iteminfo[UIITEM_PAGEUPINFO].y = M_CLIENT_BOTTOM - 2 * buttonHeight;
	iteminfo[UIITEM_PAGEUPINFO].w = buttonWidth;
	iteminfo[UIITEM_PAGEUPINFO].h = buttonHeight;
	iteminfo[UIITEM_PAGEUPINFO].state = true;
	strcpy(iteminfo[UIITEM_PAGEDOWNINFO].info, "PageDown");
	iteminfo[UIITEM_PAGEDOWNINFO].x = M_ACTIVECLIENT_RIGHT + 2 * buttonWidth;
	iteminfo[UIITEM_PAGEDOWNINFO].y = M_CLIENT_BOTTOM - 2 * buttonHeight;
	iteminfo[UIITEM_PAGEDOWNINFO].w = buttonWidth;
	iteminfo[UIITEM_PAGEDOWNINFO].h = buttonHeight;
	iteminfo[UIITEM_PAGEDOWNINFO].state = true;

	
	strcpy(iteminfo[UIITEM_BGINFO].info, "BG");
	iteminfo[UIITEM_BGINFO].x = M_ACTIVECLIENT_RIGHT;
	iteminfo[UIITEM_BGINFO].y = M_CLIENT_BOTTOM - buttonHeight;
	iteminfo[UIITEM_BGINFO].w = buttonWidth;
	iteminfo[UIITEM_BGINFO].h = buttonHeight;
	iteminfo[UIITEM_BGINFO].state = true;
	iteminfo[UIITEM_BGINFO].inputtype = UIINPUTTYPE_INT;
	strcpy(iteminfo[UIITEM_SAVEINFO].info, "SAVE");
	iteminfo[UIITEM_SAVEINFO].x = M_ACTIVECLIENT_RIGHT + buttonWidth;
	iteminfo[UIITEM_SAVEINFO].y = M_CLIENT_BOTTOM - buttonHeight;
	iteminfo[UIITEM_SAVEINFO].w = buttonWidth;
	iteminfo[UIITEM_SAVEINFO].h = buttonHeight;
	iteminfo[UIITEM_SAVEINFO].state = true;
	strcpy(iteminfo[UIITEM_REFRESHINFO].info, "Refresh");
	iteminfo[UIITEM_REFRESHINFO].x = M_ACTIVECLIENT_RIGHT + 2 * buttonWidth;
	iteminfo[UIITEM_REFRESHINFO].y = M_CLIENT_BOTTOM - buttonHeight;
	iteminfo[UIITEM_REFRESHINFO].w = buttonWidth;
	iteminfo[UIITEM_REFRESHINFO].h = buttonHeight;
	iteminfo[UIITEM_REFRESHINFO].state = true;

	float valxl = M_ACTIVECLIENT_RIGHT + 4 * UIITEM_EDGE;
	float valw = (M_CLIENT_RIGHT - M_ACTIVECLIENT_RIGHT) / 2 - 5 * UIITEM_EDGE;
	float valxr = valxl + valw + 2 * UIITEM_EDGE;
	float valys = M_ACTIVECLIENT_TOP + 2 * buttonHeight + 2 * UIITEM_EDGE;
	float valh = buttonHeight;
	for(int i=UIITEM_ITEMBEGIN; i<UIITEMMAX; i+=2)
	{
		iteminfo[i].x = valxl;
		iteminfo[i+1].x = valxr;
		iteminfo[i].y = iteminfo[i+1].y = valys + ((i-UIITEM_ITEMBEGIN)/2) * valh;
		iteminfo[i].w = iteminfo[i+1].w = valw;
		iteminfo[i].h = iteminfo[i+1].h = valh;
	}
}