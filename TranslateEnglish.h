#pragma once
class TranslateEnglish 
{
public:
	TranslateEnglish();
	void Translate(char buffer);
	bool EngPrefix[6] = { 0,0,0,0,0,1 };
};
