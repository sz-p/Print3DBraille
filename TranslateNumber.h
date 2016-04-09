#pragma once
class TranslateNumber
{
public:
	TranslateNumber();
	~TranslateNumber();
	
	void Translate(char buffer);
	bool NumPrefix[6] = { 0,0,1,1,1,1 };
};

