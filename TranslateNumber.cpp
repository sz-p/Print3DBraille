#include "pch.h"
#include "stdafx.h"
#include "TranslateNumber.h"
#include "ToSTL.h"
#include "WordCount.h"
#include "STRUCT.h"

TranslateNumber::TranslateNumber()
{

}


TranslateNumber::~TranslateNumber()
{
}


void TranslateNumber::Translate(char buffer)
{
	extern vector <DataBase> m_NumLib;
	WordCount Wc;
	ToSTL  stl;
	

	stl.GetData(NumPrefix);
	Wc.AddWordNumber();
	
	for (int i = 0;i < m_NumLib.size();i++)
	{
		if (buffer == m_NumLib[i].Ch[0])
		{
			stl.GetData(m_NumLib[i].Value);
			Wc.AddWordNumber();
			break;
		}
	}
}
