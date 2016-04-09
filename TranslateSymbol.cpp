#include "pch.h"
#include "TranslateSymbol.h"
#include "ToSTL.h"
#include "WordCount.h"
#include "STRUCT.h"

TranslateSymbol::TranslateSymbol()
{

}
void TranslateSymbol::Translate(char buffer)
{
	extern vector <DataBase> m_SymbolLib;
	WordCount Wc;
	ToSTL  stl;
	switch (buffer)
	{
	case ' ': stl.GetData(KONG);Wc.AddWordNumber();break;
	
	case '+': stl.GetData(JIA);Wc.AddWordNumber();break;
	case '-': stl.GetData(JIAN);Wc.AddWordNumber();break;
	case '*': stl.GetData(CHENG);Wc.AddWordNumber();break;
	case '/': stl.GetData(CHU);Wc.AddWordNumber();break;
	case '=': stl.GetData(DENG);Wc.AddWordNumber();break;

	case '(': stl.GetData(ZUOXIAOKUOHAO);Wc.AddWordNumber();break;
	case ')': stl.GetData(YUOXIAOKUOHAO);Wc.AddWordNumber();break;
	case '<': stl.GetData(XIAOYU);Wc.AddWordNumber();break;
	case '>': stl.GetData(DAYU);Wc.AddWordNumber();break;
	case '{': stl.GetData(ZUODA);Wc.AddWordNumber();break;
	case '}': stl.GetData(YOUDA);Wc.AddWordNumber();break;
	case '[': stl.GetData(ZUOZHONG);Wc.AddWordNumber();break;
	case ']': stl.GetData(YOUZHONG);Wc.AddWordNumber();break;
	
	case ',': stl.GetData(DOUHAO);Wc.AddWordNumber();break;
	case '.': stl.GetData(JVHAO);Wc.AddWordNumber();break;
	case '?': stl.GetData(WENHAO);Wc.AddWordNumber();break;
	case '!': stl.GetData(TANHAO);Wc.AddWordNumber();break;


	case '`': stl.GetData(SHANGDIAN);Wc.AddWordNumber();break;
	case '#': stl.GetData(JINGHAO);Wc.AddWordNumber();break;
	case '_': stl.GetData(XIAHUAXIAN);Wc.AddWordNumber();break;

	default:
		break;
	}
}