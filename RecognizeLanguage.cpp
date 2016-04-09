#include "pch.h"
#include "stdafx.h"
#include "RecognizeLanguage.h"
#include "TranslateNumber.h"
#include "TranslateEnglish.h"
#include "TranslateSymbol.h"
#include "TranslateChinese.h"

RecognizeLanguage::RecognizeLanguage()
{
}


RecognizeLanguage::~RecognizeLanguage()
{
}




int RecognizeLanguage::RecWord(char buffer)
{
	if ('0' <= buffer&&buffer <= '9')
	{
		TranslateNumber TNum;
		TNum.Translate(buffer);
		return 1;
	}
	else if ('a' <= buffer&&buffer <= 'z'|| 'A' <= buffer&&buffer <= 'Z')
	{
		TranslateEnglish TEng;
		TEng.Translate(buffer);
		return 1;
	}
	else if (32 <= buffer&&buffer <= 47 || 58 <= buffer&&buffer <= 64)
	{
		TranslateSymbol TSym;
		TSym.Translate(buffer);
		return 1;
	}
	else
		return 0;
}

int RecognizeLanguage::RecDoubleWord(int buffer)
{
	TranslateChinese TChinese;
	TChinese.Translate(buffer);
	return 1;
}