#pragma once
#include "string"
using namespace std;
 class TranslateChinese 
{
public:
	TranslateChinese();
	void Translate(int buffer);
	int ChangeChineseToCode(int buffer);
	string ChangeCodeToPY(int nCode);
	void ExplainPY(string &PY);
	int IdentifyZM(string &ZM, string &ZM2);
	void SetDataToSTL(string buffer);

	bool One[6] = { 1,0,0,0,0,0 };
	bool Two[6] = { 0,1,0,0,0,0 };
	bool Three[6] = { 0,0,1,0,0,0 };
	bool Four[6] = { 0,1,1,0,0,0 };
	bool Five[6] = { 0,0,0,0,0,0 };

 };

