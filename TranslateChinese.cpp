#include "pch.h"
#include "TranslateChinese.h"
#include"STRUCT.h"
#include "ToSTL.h"
#include "WordCount.h"

TranslateChinese::TranslateChinese()
{
}


void TranslateChinese::Translate(int buffer)
{
	int nCode = ChangeChineseToCode(buffer);
	string PY = ChangeCodeToPY(nCode-1);
	ExplainPY(PY);
}


int TranslateChinese::ChangeChineseToCode(int buffer)
{
	extern vector <ChineseToCodeData> m_Chinese2CodeLib;
	for (int i = 0;i < m_Chinese2CodeLib.size();i++)
	{
		if (m_Chinese2CodeLib[i].ChineseCode == buffer)
		{
			return m_Chinese2CodeLib[i].value;
			break;
		}
		if (i == m_Chinese2CodeLib.size())
			return 0;
	}
	
}


string TranslateChinese::ChangeCodeToPY(int nCode)
{
	extern vector <string> m_Code2PYLib;
	if(nCode!=-1)
	return m_Code2PYLib[nCode];
}


void TranslateChinese::ExplainPY(string & PY)
{
	char ShengDiao;
	ShengDiao = PY[PY.size()-1];
	PY.erase(PY.size()-1);

	WordCount Wc;
	ToSTL  stl;
	
	string buffer;
	string buffer1;
	
	extern vector <PYData> m_PinYinLib;
	for (int i = 0;i < PY.size();i++)
	{

		buffer.push_back(PY[i]);
		buffer1 = buffer;
		buffer1.push_back(PY[i + 1]);
		if (IdentifyZM(buffer, buffer1))
		{
			SetDataToSTL(buffer);
			buffer.clear();
			buffer1.clear();
		}
	}
	
	switch (ShengDiao)
	{

	case '1':stl.GetData(One);break;
	case '2':stl.GetData(Two);break;
	case '3':stl.GetData(Three);break;
	case '4':stl.GetData(Four);break;
	case '5':stl.GetData(Five);break;
	
	default:
		break;
	}
	
	Wc.AddWordNumber();


}


int TranslateChinese::IdentifyZM(string &ZM,string &ZM2)
{
	extern vector <PYData> m_PinYinLib;
	int key = 0;
	int key1 = 0;
	int key2 = 1;

	for (int i = 0;i < m_PinYinLib.size();i++)
	{
		if (m_PinYinLib[i].ShengMuYunMU == ZM)
		{
			key1 = 1;
			break;
		}
	}
	for (int i = 0;i < m_PinYinLib.size();i++)
	{
		if (m_PinYinLib[i].ShengMuYunMU == ZM2)
		{
			key2 = 0;
			break;
		}
	}
	key = key1*key2;
	return key;
}


void TranslateChinese::SetDataToSTL(string buffer)
{
	extern vector <PYData> m_PinYinLib;
	
	WordCount Wc;
	ToSTL  stl;

	for (int i = 0;i < m_PinYinLib.size();i++)
	{
		if (buffer == m_PinYinLib[i].ShengMuYunMU)
		{
			bool Data[6] = {0,0,0,0,0,0};
			for (int j = 0;j < m_PinYinLib[i].ShengMuYunMUData.size();j++)
			{
				switch (m_PinYinLib[i].ShengMuYunMUData[j])
				{
				
				case '1': Data[0] = 1;break;
				case '2': Data[1] = 1;break;
				case '3': Data[2] = 1;break;
				case '4': Data[3] = 1;break;
				case '5': Data[4] = 1;break;
				case '6': Data[5] = 1;break;

				default:
					break;
				}
			}
			stl.GetData(Data);
			Wc.AddWordNumber();
			break;
		}
	}
}
