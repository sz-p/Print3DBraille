#include "pch.h"
#include "stdafx.h"
#include "LoadFileData.h"
#include "RecognizeLanguage.h"
#include "WordCount.h"

LoadFileData::LoadFileData()
{
	
}


LoadFileData::~LoadFileData()
{
}

void LoadFileData::SetProgress(int i, int n)
{
	//Progress = i / n;
}

void LoadFileData::GetLine(String ^ UnknowWord)
{
	extern int  TranslateProgress;
	RecognizeLanguage  pRec;
	wstring ws = std::wstring(UnknowWord->Data());
	for (int i = 0;i < ws.size();i++)
	{
		SetProgress(i, ws.size());
		TranslateProgress = (i + 1) * 100 / ws.size();

		if (ws[i] > 10000)
		{
			pRec.RecDoubleWord(int (ws[i]));
		}
		else
		{
			pRec.RecWord(ws[i]);
		}
	}
}

