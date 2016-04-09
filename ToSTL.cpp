#include "pch.h"
#include "stdafx.h"
#include "ToSTL.h"
#include "WordCount.h"
#include "SavaSTL.h"
#include "fstream"
using namespace std;

#include "STRUCT.h"


ToSTL::ToSTL()
{
}


ToSTL::~ToSTL()
{
}


void ToSTL::GetData(bool BraiMatrix[])
{
	WordCount Wc;
	AddWordToPage(BraiMatrix,Wc.Number);
	//CreateWordSTL(BraiMatrix);
}



void ToSTL::AddWordToPage(bool BraiMatrix[], int WordNumber)
{
	extern vector<PrintData> V_PrintData;
	PrintData Pd;
	Pd.Page = WordNumber / (MaxX*MaxY);
	Pd.PageY = WordNumber % (MaxX*MaxY) / MaxX;
	Pd.PageX = WordNumber % (MaxX*MaxY) % MaxX;
	for (int i = 0; i < 6; i++)
	{
		Pd.WordData[i] = BraiMatrix[i];
	}

	V_PrintData.push_back(Pd);
}

