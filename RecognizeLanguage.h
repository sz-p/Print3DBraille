#pragma once
#include "string"
using namespace std;
class RecognizeLanguage
{
public:
	RecognizeLanguage();
	~RecognizeLanguage();

	int RecWord(char buffer);
	int RecDoubleWord(int buffer);
};

