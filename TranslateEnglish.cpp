#include "pch.h"
#include "TranslateEnglish.h"
#include "ToSTL.h"
#include "WordCount.h"
#include "STRUCT.h"


TranslateEnglish::TranslateEnglish()
{
}

void TranslateEnglish::Translate(char buffer)
{
	extern vector <DataBase> m_EnglishLib;
	WordCount Wc;
	ToSTL  stl;
	
	if ('A' <= buffer&&buffer <= 'Z')
	{
		stl.GetData(EngPrefix);
		Wc.AddWordNumber();
		buffer = buffer + 32;
	}

	for (int i = 0;i < m_EnglishLib.size();i++)
	{
		if (buffer == m_EnglishLib[i].Ch[0])
		{
			stl.GetData(m_EnglishLib[i].Value);
			Wc.AddWordNumber();
			break;
		}
	}
}