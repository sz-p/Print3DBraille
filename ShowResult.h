#pragma once
#include "string"
using namespace std;
using namespace Platform;
class ShowResult 
{
public:
	ShowResult();
	void ShowBuffer(int **buffer);
	void WriteBuffer();
	int MaxLineSize;
	int MaxLineNumber;
	
};

