#pragma once
class TranslateSymbol 
{
public:
	TranslateSymbol();
	void Translate(char buffer);
	bool KONG[6] = { 0,0,0,0,0,0 };
	
	
	
	bool CHENG[6] = { 0,1,1,0,0,1 };
	bool CHU[6] = { 0,1,0,0,1,1 };
	bool JIA[6] = { 0,1,1,0,1,0 };
	bool JIAN[6] = {0,0,1,0,0,1};
	bool DENG[6] = { 0,1,1,0,1,1 };

	bool XIAOYU[6] = {0,1,0,1,0,1};
	bool DAYU[6] = {1,0,1,0,1,0};
	bool ZUOXIAOKUOHAO[6] = { 1,1,0,0,0,1 };
	bool YUOXIAOKUOHAO[6] = { 0,0,1,1,1,0 };
	bool ZUOZHONG[6] = {1,1,1,0,1,1};
	bool YOUZHONG[6] = {1,1,1,1,0,1};
	bool ZUODA[6] = {0,1,0,1,0,1};
	bool YOUDA[6] = {1,0,1,0,1,0};

	bool DOUHAO[6] = {0,1,0,0,0,0};
	bool JVHAO[6] = {0,1,0,0,1,1};
	bool WENHAO[6] = {0,1,1,0,0,1};
	bool TANHAO[6] = {0,1,1,0,1,0};
	
	bool JINGHAO[6] = { 0,0,1,1,1,1 };
	bool XIAHUAXIAN[6] = { 0,0,1,0,0,1 };
	bool SHANGDIAN[6] = { 0,0,1,0,0,0 };

};

