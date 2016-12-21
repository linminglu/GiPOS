/* -------------------------------------------------------------------------
//	FileName    :   GenFirstPYLetter.cpp
//	Creator     :	debehe
//	Date		:   2009/9/28 17:40:31
//	Brief		:	需要用MultiByte才能正确转换
//					Unicode转成MultiByte时不要用W2A
//
//	$Id: $
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "GenFirstPYLetter.h"
#include <Windows.h>

// -------------------------------------------------------------------------

/********************************************************************************************
/* Syntax
/*        void FirstLetter(int nCode, CString& strLetter)
/* Remarks:
/*        Get the first letter of pinyin according to specified Chinese character code.
/* Parameters:
/*        nCode         - the code of the chinese character.
/*        strLetter      - a CString object that is to receive the string of the first letter.
/* Return Values:
/*        None.
/* Author:
/*        lixiaosan
/* Create Date:
/*        05-26-2006
/********************************************************************************************/
void FirstLetter(int nCode, CStringA& strLetter)
{
	if(nCode >= 1601 && nCode < 1637) strLetter = "A";
	if(nCode >= 1637 && nCode < 1833) strLetter = "B";
	if(nCode >= 1833 && nCode < 2078) strLetter = "C";
	if(nCode >= 2078 && nCode < 2274) strLetter = "D";
	if(nCode >= 2274 && nCode < 2302) strLetter = "E";
	if(nCode >= 2302 && nCode < 2433) strLetter = "F";
	if(nCode >= 2433 && nCode < 2594) strLetter = "G";
	if(nCode >= 2594 && nCode < 2787) strLetter = "H";
	if(nCode >= 2787 && nCode < 3106) strLetter = "J";
	if(nCode >= 3106 && nCode < 3212) strLetter = "K";
	if(nCode >= 3212 && nCode < 3472) strLetter = "L";
	if(nCode >= 3472 && nCode < 3635) strLetter = "M";
	if(nCode >= 3635 && nCode < 3722) strLetter = "N";
	if(nCode >= 3722 && nCode < 3730) strLetter = "O";
	if(nCode >= 3730 && nCode < 3858) strLetter = "P";
	if(nCode >= 3858 && nCode < 4027) strLetter = "Q";
	if(nCode >= 4027 && nCode < 4086) strLetter = "R";
	if(nCode >= 4086 && nCode < 4390) strLetter = "S";
	if(nCode >= 4390 && nCode < 4558) strLetter = "T";
	if(nCode >= 4558 && nCode < 4684) strLetter = "W";
	if(nCode >= 4684 && nCode < 4925) strLetter = "X";
	if(nCode >= 4925 && nCode < 5249) strLetter = "Y";
	if(nCode >= 5249 && nCode < 5590) strLetter = "Z";
}

BOOL GenFirstPYLetter(CStringA strName, CStringA& strResult )
{
	BOOL bStartByLetter = FALSE;

	unsigned char ucHigh, ucLow;
	int  nCode;
	CStringA strRet;

	strResult.Empty();

	if (strName.IsEmpty())
		return FALSE;

	if ((unsigned char)strName[0] < 0x80 )
		bStartByLetter = TRUE;

	for (int i=0; i < strName.GetLength(); i++)
	{
		if ( (unsigned char)strName[i] < 0x80 )
		{
			strResult += strName[i];
			continue;
		}

		ucHigh = (unsigned char)strName[i];
		ucLow  = (unsigned char)strName[i+1];
		if ( ucHigh < 0xa1 || ucLow < 0xa1)
			continue;
		else
			// Treat code by section-position as an int type parameter,
			// so make following change to nCode.
			nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;

		FirstLetter(nCode, strRet);
		strResult += strRet;
		i++;
	}

	return bStartByLetter;
}

BOOL GenFirstPYLetter(CStringW strName, CStringW&strResult)
{
	CStringA strSource;
	CStringA strOutput;
	
	// Unicode转换成MultiByte
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,strName,-1,NULL,0,NULL,FALSE);
	char *psText;
	psText = new char[dwNum];
	if(!psText)
	{
		delete []psText;
		return FALSE;
	}
	else
	{
		WideCharToMultiByte (CP_OEMCP,NULL,strName,-1,psText,dwNum,NULL,FALSE);
		strSource = psText;
		delete []psText;
	}
		
	// 转调
	BOOL bRet = GenFirstPYLetter(strSource, strOutput);

	// MultiByte转换成Unicode
	dwNum = MultiByteToWideChar (CP_ACP, 0, strOutput, -1, NULL, 0);

	wchar_t *pwText;
	pwText = new wchar_t[dwNum];
	if(!pwText)
	{
		delete []pwText;
		return FALSE;
	}
	else
	{
		MultiByteToWideChar (CP_ACP, 0, strOutput, -1, pwText, dwNum);
		strResult = pwText;
		delete [] pwText;
	}

	return bRet;
}

// -------------------------------------------------------------------------
// $Log: $
