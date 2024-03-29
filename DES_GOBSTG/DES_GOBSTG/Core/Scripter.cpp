#include "../Header/Scripter.h"
#include "../Header/BResource.h"
#include "../Header/Data.h"
#include "../Header/Main.h"

Scripter scr;

bool Scripter::stopEdefScript = false;

Scripter::Scripter()
{
	file = NULL;
	bincontent = NULL;
	for(int i=0;i<SCR_MAXDESC;i++)
	{
		d[i].bfloat = false;
		d[i].value = &idesc[i];
	}
	binmode = false;
	strdescIndex = 0;
}

Scripter::~Scripter()
{
	if(file)
		fclose(file);
}

void Scripter::FillCustomConstDesc()
{	
	if(binmode)
		return;
	DWORD name = data.nLinkType(RESDATAN_TYPE);
	for(int i=0; i<SCR_CUSTOMCONSTMAX; i++)
	{
		strcpy(customconstName[i], data.sRead(DATA_CUSTOMCONSTFILE, data.sLinkType(DATAS_CUSTOMCONST), data.nLinkNum(name, i+1), ""));
	}
}

bool Scripter::Resize()
{
#ifdef __COUNT_SCRIPTSIZE
	DWORD __size = 0;
	__size += _controlsize;
	__size += _stagesize;
	__size += _scenesize;
	__size += _edefsize;
	__size += _functionsize;

	if (!control.empty())
	{
		for (vector<File>::iterator i=control.begin(); i!=control.end(); i++)
		{
			if (!(i->file.empty()))
			{
				__size += i->_size;
				for (vector<Block>::iterator j=i->file.begin(); j!=i->file.end(); j++)
				{
					if (!j->block.empty())
					{
						__size += j->_size;
					}
				}
			}
		}
	}
	if (!stage.empty())
	{
		for (vector<File>::iterator i=stage.begin(); i!=stage.end(); i++)
		{
			if (!(i->file.empty()))
			{
				__size += i->_size;
				for (vector<Block>::iterator j=i->file.begin(); j!=i->file.end(); j++)
				{
					if (!j->block.empty())
					{
						__size += j->_size;
					}
				}
			}
		}
	}
	if (!scene.empty())
	{
		for (vector<File>::iterator i=scene.begin(); i!=scene.end(); i++)
		{
			if (!(i->file.empty()))
			{
				__size += i->_size;
				for (vector<Block>::iterator j=i->file.begin(); j!=i->file.end(); j++)
				{
					if (!j->block.empty())
					{
						__size += j->_size;
					}
				}
			}
		}
	}
	if (!edef.empty())
	{
		for (vector<File>::iterator i=edef.begin(); i!=edef.end(); i++)
		{
			if (!(i->file.empty()))
			{
				__size += i->_size;
				for (vector<Block>::iterator j=i->file.begin(); j!=i->file.end(); j++)
				{
					if (!j->block.empty())
					{
						__size += j->_size;
					}
				}
			}
		}
	}
	if (!function.empty())
	{
		for (vector<File>::iterator i=function.begin(); i!=function.end(); i++)
		{
			if (!(i->file.empty()))
			{
				__size += i->_size;
				for (vector<Block>::iterator j=i->file.begin(); j!=i->file.end(); j++)
				{
					if (!j->block.empty())
					{
						__size += j->_size;
					}
				}
			}
		}
	}

	HGELOG("Script count as %u.", __size);
#endif

	return true;
}

bool Scripter::LoadAll()
{
	control.clear();
	stage.clear();
	scene.clear();
	edef.clear();
	function.clear();
#ifdef __COUNT_SCRIPTSIZE
	_controlsize = 0;
	_stagesize = 0;
	_scenesize = 0;
	_edefsize = 0;
	_functionsize = 0;
#endif // __COUNT_SCRIPTSIZE

	binoffset = 0;

	strdescIndex = 0;

	FillCustomConstDesc();

	if(!binmode)
	{
		for(int i=0; i<STRINGDESCMAX; i++)
		{
			strcpy(strdesc[i], "");
		}

		bincontent = (BYTE *)malloc(SCRIPT_DATAMAX);
		if(!binmode)
		{
			data.Init(DATA_SCRIPTFILE);
		}

		BYTE * _content;
		DWORD _size;
		hge->Resource_AttachPack(data.scriptfilename, data.password);
		_content = hge->Resource_Load(data.scrbinname, &_size);

		if(_content)
		{
			if(data.CheckMemHeader(_content, _size, DATA_SCRIPTFILE))
			{
				memcpy(bincontent, _content, _size);
				binoffset = _size;
			}
		}
		else
		{
			BYTE * _header = data.CreateMemHeader(DATA_SCRIPTFILE);
			memcpy(bincontent, _header, M_BINHEADER_OFFSET);
			binoffset = M_BINHEADER_OFFSET;
			free(_header);
		}
		hge->Resource_Free(_content);

		int foldernum = BResource::SplitString(res.resdata.scriptfoldername);
		for (int i=0; i<foldernum; i++)
		{
			if (strlen(BResource::scriptfolder[i]))
			{
				SetCurrentDirectory(hge->Resource_MakePath(BResource::scriptfolder[i]));
				char enumfile[M_PATHMAX];
				strcpy(enumfile, BResource::scriptfolder[i]);
				strcat(enumfile, "*.");
				strcat(enumfile, res.resdata.scriptextensionname7);

				char * buffer;
				buffer = hge->Resource_EnumFiles(enumfile);
				while(buffer != NULL)
				{
					if(!LoadScript(buffer))
					{
#ifdef __DEBUG
						HGELOG("%s\nFailed loading Script File %s.\n", HGELOG_ERRSTR, buffer);
#endif
						free(bincontent);
						bincontent = NULL;
						return false;
					}
#ifdef __DEBUG
					HGELOG("Script file %s loaded.", buffer);
#endif
					if(!hge->Resource_EnumFiles())
						break;
				}
			}
		}

		hgeMemoryFile memfile;
		memfile.data = bincontent;
		memfile.filename = data.scrbinname;
		memfile.size = binoffset;

		hge->Resource_CreatePack(data.scriptfilename, data.password, &memfile, NULL);

		free(bincontent);
		bincontent = NULL;
		
	}

	if(binmode)
	{
		binoffset = M_BINHEADER_OFFSET;
		
		hge->Resource_AttachPack(data.scriptfilename, data.password);
		bincontent = hge->Resource_Load(data.scrbinname, &binsize);
		if(bincontent)
		{
			if(!data.CheckMemHeader(bincontent, binsize, DATA_SCRIPTFILE))
			{
				data.Init(DATA_SCRIPTFILE);
				hge->Resource_AttachPack(data.scriptfilename, data.password);
				bincontent = hge->Resource_Load(data.scrbinname, &binsize);
			}
		}

		if(!LoadScript(data.scriptfilename))
		{
#ifdef __DEBUG
			HGELOG("%s\nFailed loading Script Bin File.\n", HGELOG_ERRSTR);
#endif
			hge->Resource_Free(bincontent);
			bincontent = NULL;
			return false;
		}
		hge->Resource_Free(bincontent);
	}
#ifdef __DEBUG
	HGELOG("\nAll Script File loaded.\n");
#endif
	
	SetCurrentDirectory(hge->Resource_MakePath(""));

	bincontent = NULL;

	return Resize();
}

bool Scripter::LoadScript(const char * filename)
{
	if(!binmode)
	{
		if(file)
			fclose(file);
		file = fopen(filename, "r");
		if(!file)
			return false;
	}
addtype:
	Token _tktag = GetToken();
	if(_tktag.type & SCR_TOKEN_EOF)
		return true;
	Token _tkver = GetToken();
	if(_tkver.type & SCR_TOKEN_EOF)
		return true;
	if(_tktag.value != SCR_SCRIPTTAG || (_tkver.value>>GAMEVERSION_ALGORITHM) != (GAME_VERSION>>GAMEVERSION_ALGORITHM))
	{
		if(binmode && binoffset >= binsize)
		{
			return true;
		}
		else
		{
			fclose(file);
			file = NULL;
		}
		return false;
	}

	vector<File> * ptype;

	DWORD typeflag = GetToken().value;
	Token tk = GetToken();

	switch(typeflag)
	{
	case SCR_CONTROL:
		ptype = &control;
		break;
	case SCR_STAGE:
		ptype = &stage;
		break;
	case SCR_EDEF:
		ptype = &edef;
		break;
	case SCR_SCENE:
		ptype = &scene;
		break;
	case SCR_FUNCTION:
		ptype = &function;
		break;
	}

	if(tk.type & SCR_TOKEN_TYPE)
	{
addfile:
		tk = GetToken();
		File _f;
#ifdef __COUNT_SCRIPTSIZE
		_f._size = 0;
#endif // __COUNT_SCRIPTSIZE
		_f.name = tk.value;
		File * i;
		bool bInsertFile = false;
		for(vector<File>::iterator it=ptype->begin(); it!=ptype->end(); it++)
		{
			if(it->name == _f.name)
			{
				i = &(*it);
				bInsertFile = true;
			}
		}
		if(!bInsertFile)
		{
#ifdef __COUNT_SCRIPTSIZE
			switch(typeflag)
			{
			case SCR_CONTROL:
				_controlsize++;
				break;
			case SCR_STAGE:
				_stagesize++;
				break;
			case SCR_EDEF:
				_edefsize++;
				break;
			case SCR_SCENE:
				_scenesize++;
				break;
			case SCR_FUNCTION:
				_functionsize++;
				break;
			}
#endif // __COUNT_SCRIPTSIZE
			ptype->push_back(_f);
			i = &ptype->back();
		}

		tk = GetToken();
		if(tk.type & SCR_TOKEN_TYPE)
		{
addblock:
			tk = GetToken();
			Block _b;
#ifdef __COUNT_SCRIPTSIZE
			_b._size = 0;
			i->_size++;
#endif // __COUNT_SCRIPTSIZE
			_b.con = tk.value;
			i->file.push_back(_b);

			varIndex = SCR_VARBEGIN;
			for(int k=0;k<SCR_FREEBEGIN-SCR_VARBEGIN;k++)
			{
				strcpy(varName[k], "");
			}

			if(tk.value > SCR_TIMECONTROL)
			{
				int k = 0;
				while (tk.value & (SCRKT_TEST_OPERATOR << (k*SCRKT_SIZE_OPERATOR)))
				{
					Token _tk = GetToken();
#ifdef __COUNT_SCRIPTSIZE
					_b._size = 0;
					i->_size++;
#endif // __COUNT_SCRIPTSIZE
					_b.con = _tk.value;
					i->file.push_back(_b);
					k++;
				}
			}
			Block * j = &(i->file.back());

			pnow = &(j->block);
			//push
			while(true)
			{
				tk = GetToken();
				if(tk.type & SCR_TOKEN_TYPE)
					break;
				else if(tk.type || tk.value)
				{
					if(tk.type == SCR_TOKEN_ERROR)
					{
#ifdef __DEBUG
						HGELOG("%s\nError in loading token at Block %d in File %d with Error-Code %d.", HGELOG_ERRSTR, j->con, i->name, tk.value);

						if(!binmode && file)
						{
							char tbuff[M_STRITOAMAX];
							ltoa(ftell(file), tbuff, 16);
							HGELOG("Point to 0x%s", tbuff);
						}
#endif
						return false;
					}
					else if(tk.type == SCR_TOKEN_NULL)
					{
						continue;
					}
#ifdef __COUNT_SCRIPTSIZE
					j->_size++;
#endif // __COUNT_SCRIPTSIZE
					pnow->push_back(tk);
				}
				if(tk.type & SCR_TOKEN_EOF)
				{
					if(binmode && binoffset < binsize)
					{
						goto addtype;
					}
					return true;
				}
			}

			if(tk.type & SCR_TOKEN_TYPE)
			{
				if(tk.value == SCR_BLOCKCON)
					goto addblock;
				if(tk.value == SCR_FILENAME)
					goto addfile;
			}
		}
	}
	return false;
}


Token Scripter::GetToken()
{
	char buffer[M_STRMAX];
	Token ret;
	ret.type = 0;
	ret.value = 0;

	if(binmode)
	{
		goto exit;
	}

	if(!file || feof(file))
	{
		ret.type = SCR_TOKEN_EOF;
		goto exit;
	}

	int i = 0;
	while(true)
	{
		if(!fread(&buffer[i], 1, 1, file))
			buffer[i] = 0;
		if(feof(file) || iswspace(buffer[i]) || buffer[i] == ',' || buffer[i] == ';')
		{
			if(i == 0 && !feof(file))
			{
				continue;
			}
			if(buffer[0] == '/')
			{
				if(buffer[1] == '/')
				{
					if(buffer[i] != '\n' && buffer[i] != '\r')
					{
						while(!feof(file))
						{
							fread(&buffer[0], 1, 1, file);
							if(buffer[0] == '\n' || buffer[0] == '\r')
								break;
						}
					}
					i = 0;
					if(feof(file))
					{
						ret.value = 0;
						ret.type = 0;
						break;
					}
					continue;
				}
				else if(buffer[1] == '*')
				{
					fseek(file, -i, SEEK_CUR);
					while(!feof(file))
					{
						fread(&buffer[0], 1, 1, file);
						if(buffer[0] == '*')
						{
							fread(&buffer[1], 1, 1, file);
							if(buffer[1] == '/')
								break;
						}
					}
					i = 0;
					if(feof(file))
					{
						ret.value = 0;
						ret.type = 0;
						break;
					}
					continue;
				}
			}
			if(buffer[0] == '+' || buffer[0] == '-' && !iswdigit(buffer[1]) || buffer[0] == '*' || buffer[0] == '/' || buffer[0] == '%' || buffer[0] == '~' || buffer[0] == '!' || buffer[0] == '>' || buffer[0] == '<')
			{
				ret.type |= SCR_TOKEN_OPERATOR;
			}

			if(feof(file))
			{
				ret.type |= SCR_TOKEN_EOF;
				fclose(file);
				file = NULL;
			}

			buffer[i] = 0;
			break;
		}
		else
			i++;
	}

	if(buffer[0] == 0)
	{
		ret.type = SCR_TOKEN_NULL;
		goto exit;
	}
	//number
	if(iswdigit(buffer[0]) || buffer[0] == '-' && iswdigit(buffer[1]))
	{
		ret.type |= SCR_TOKEN_VALUE;
		if(buffer[0] == '0' && buffer[1] == 'x')
		{
			if(strlen(buffer) == 10)
			{
				char tbuf[2][5];
				strncpy(tbuf[0], &buffer[2], 4);
				tbuf[0][4] = 0;
				strncpy(tbuf[1], &buffer[6], 4);
				tbuf[1][4] = 0;
				ret.value = (strtol(tbuf[0], NULL, 16) << 16) + (strtol(tbuf[1], NULL, 16));
			}
			else
				ret.value = strtol(&buffer[2], NULL, 16);
		}
		else
		{
			for(int i=0;i<(int)strlen(buffer);i++)
			{
				if(buffer[i] == '.')
				{
					float tf = (float)atof(buffer);
					void * tp = &tf;
					DWORD * tpint = (DWORD *)tp;
					ret.type |= SCR_TOKEN_FLOAT;
					ret.value = *tpint;
					break;
				}
			}
			if(!(ret.type & SCR_TOKEN_FLOAT))
			{
				ret.value |= atoi(buffer);
			}
		}
		goto exit;
	}

	//quoted
	else if(buffer[0] == '"')
	{
		if(strlen(buffer) >= sizeof(buffer))
		{
			ret.type = SCR_TOKEN_ERROR;
			ret.value = SCR_ERROR_STRINGTOOLONG;
			goto exit;
		}
		buffer[strlen(buffer)-1] = 0;
//		string _str(&buffer[1]);
		strcpy(strdesc[strdescIndex], (char *)(&buffer[1]));
		ret.type |= SCR_TOKEN_HANDLE;
		ret.value = strdescIndex;
		strdescIndex++;
		if(strdescIndex > STRINGDESCMAX)
		{
			ret.type = SCR_TOKEN_ERROR;
			ret.value = SCR_ERROR_STRINGTOOMUCH;
		}
//		ret.value = (DWORD)(&strdesc.back());
		goto exit;
	}

	//customconst
	else if(buffer[0] == '$')
	{
		ret.type |= SCR_TOKEN_VALUE;
		ret.value = 0;
		for(int j=0; j<SCR_CUSTOMCONSTMAX; j++)
		{
			if(!strcmp(&buffer[1], customconstName[j]))
			{
				ret.value = j;
				break;
			}
		}
		goto exit;
	}

	else
	{
		ret.type |= SCR_TOKEN_KEYWORD;
	}

	//variable
	bool bIsAddress = false;
	if(buffer[0] == '[' && buffer[strlen(buffer)-1] == ']')
	{
		bIsAddress = true;
		int i=0;
		for(i=0; i<(int)strlen(buffer)-2; i++)
		{
			buffer[i] = buffer[i+1];
		}
		buffer[i] = 0;
	}
	if((buffer[0] == '_' && (iswdigit(buffer[1]) || iswlower(buffer[1])) || iswlower(buffer[0])) && strcmp(buffer, "false") && strcmp(buffer, "true"))
	{
		if(buffer[0] == '_' && iswdigit(buffer[1]))
		{
			int toffset = atoi(&buffer[1]);
			if(toffset >= SCR_RESERVEBEGIN - SCR_FREEBEGIN)
			{
				ret.type = SCR_TOKEN_ERROR;
				ret.value = SCR_ERROR_FREEVAROVER;
				goto exit;
			}
			ret.value |= toffset + SCR_FREEBEGIN;
			if(bIsAddress)
				ret.type |= SCR_TOKEN_VALUE;
			else
				ret.type |= SCR_TOKEN_VARIABLE;
			goto exit;
		}

		for(i=0; i<SCR_FREEBEGIN-SCR_VARBEGIN; i++)
		{
			if(!strcmp(buffer, varName[i]))
			{
				ret.value |= i + SCR_VARBEGIN;
				if(bIsAddress)
					ret.type |= SCR_TOKEN_VALUE;
				else
					ret.type |= SCR_TOKEN_VARIABLE;
				goto exit;
			}
		}

		if(varIndex == SCR_FREEBEGIN)
		{
			ret.type = SCR_TOKEN_ERROR;
			ret.value = SCR_ERROR_VAROVER;
			goto exit;
		}
		ret.value |= varIndex;
		strcpy(varName[varIndex-SCR_VARBEGIN], buffer);
		if(bIsAddress)
			ret.type |= SCR_TOKEN_VALUE;
		else
			ret.type |= SCR_TOKEN_VARIABLE;
		varIndex++;
		goto exit;
	}

	//keyword
	bool bFound = false;
	//timefunc
	if (!strncmp(buffer, SCRKT_STR_TIMEFUNC, sizeof(char)*SCRKT_SIZE_TIMEFUNC))
	{
		int i = SCRKT_SIZE_TIMEFUNC;
		BYTE lastop;
		while (buffer[i] && i < SCRKT_SIZE_TIMEFUNC + SCRKT_SIZE_OPERATORNUM)
		{
			lastop = 0;
			BYTE rollbits = (i-SCRKT_SIZE_TIMEFUNC)*SCRKT_SIZE_OPERATOR;
			switch (buffer[i])
			{
			case SCRKT_CHAR_MOD:
				ret.value |= SCR_TIMEFUNC_MOD << rollbits;
				lastop = SCR_TIMEFUNC_MOD;
				break;
			case SCRKT_CHAR_PLUS:
				ret.value |= SCR_TIMEFUNC_PLUS << rollbits;
				lastop = SCR_TIMEFUNC_PLUS;
				break;
			case SCRKT_CHAR_LESS:
				ret.value |= SCR_TIMEFUNC_LESS << rollbits;
				break;
			case SCRKT_CHAR_LESSEQUAL:
				ret.value |= SCR_TIMEFUNC_LESSEQUAL << rollbits;
				break;
			case SCRKT_CHAR_EQUAL:
				ret.value |= SCR_TIMEFUNC_EQUAL << rollbits;
				break;
			case SCRKT_CHAR_GREAT:
				ret.value |= SCR_TIMEFUNC_GREAT << rollbits;
				break;
			case SCRKT_CHAR_GREATEQUAL:
				ret.value |= SCR_TIMEFUNC_GREATEQUAL << rollbits;
				break;
			default:
				ret.type = SCR_TOKEN_ERROR;
				ret.value = SCR_ERROR_INVALIDSTRING;
				return ret;
			}
			i++;
		}
		if (lastop)
		{
			ret.value |= SCR_TIMECONTROL_TEST0;
		}
		ret.value |= SCR_TIMECONTROL;
		ret.type = SCR_TOKEN_KEYWORD;
		bFound = true;
	}
	//keyword
	int kti = 0;
	if (!bFound)
	{
		for(; scrKeyTable[kti].code != SCR_CONST || strcmp(scrKeyTable[kti].word, SCR_CONST_STR); kti++)
		{
			if(!strcmp(buffer, scrKeyTable[kti].word))
			{
				ret.value |= scrKeyTable[kti].code;
				if(ret.value > SCR_TYPEBEGIN && ret.value < SCR_NULL)
					ret.type |= SCR_TOKEN_TYPE;
				else
					ret.type |= SCR_TOKEN_COMMAND;
				bFound = true;
				break;
			}
		}
	}
	//const
	if(!bFound)
	{
		for(; scrKeyTable[kti].code != SCR_KEYSTATE || strcmp(scrKeyTable[kti].word, SCR_KEYSTATE_STR); kti++)
		{
			if(!strcmp(buffer, scrKeyTable[kti].word))
			{
				ret.value |= scrKeyTable[kti].code;
				ret.type |= SCR_TOKEN_VALUE;
				bFound = true;
				break;
			}
		}
	}
	//keystate
	if (!bFound)
	{
		for (; scrKeyTable[kti].code != SCR_NULL || strcmp(scrKeyTable[kti].word, SCR_NULL_STR); kti++)
		{
			if (!strcmp(buffer, scrKeyTable[kti].word))
			{
				ret.value |= *(DWORD *)scrKeyTable[kti].code;
				ret.type |= SCR_TOKEN_VALUE;
				bFound = true;
				break;
			}
		}
	}
	//DATA
	if (!bFound)
	{
		for (int i=DATAMAPENUM_DATASTART; i<DATAMAPENUM_RESOURCESTART; i++)
		{
			if (!strcmp(buffer, dataMap[i].textname))
			{
				ret.value |= dataMap[i].binname;
				ret.type |= SCR_TOKEN_VALUE;
				bFound = true;
				break;
			}
		}
	}
	//error
	if(!bFound)
	{
		ret.type = SCR_TOKEN_ERROR;
		ret.value = SCR_ERROR_INVALIDSTRING;
	}

exit:
	if(!binmode)
	{
		memcpy(bincontent+binoffset, &ret, sizeof(Token));
		binoffset += sizeof(Token);
		if(ret.type & SCR_TOKEN_HANDLE)
		{
			strcpy(strdesc[ret.value], &buffer[1]);
		}
	}
	else
	{
		memcpy(&ret, bincontent+binoffset, sizeof(Token));
		binoffset += sizeof(Token);
		if(binoffset > binsize)
		{
			ret.type = SCR_TOKEN_EOF;
		}
	}
	return ret;
}
