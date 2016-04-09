#pragma once
#include "string"

using namespace std;
using namespace Platform;

class LoadFileData
{
public:
	LoadFileData();
	~LoadFileData();
	void GetLine(String ^ UnknowWord);
	void GetOneWord(char Word);
	void SetProgress(int i, int n);
	void AddWordNumber();
};

